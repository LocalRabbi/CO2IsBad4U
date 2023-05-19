#include <Arduino.h>
#include <SensirionI2CScd4x.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <string>

SensirionI2CScd4x scd4x;


const char* ssid = "esddr";
const char* password = "eagles74";


const char* serverName = "https://esdcotwo.bio/co2/recieveData";


/* return absolute humidity [mg/m^3] with approximation formula
* @param temperature [°C]
* @param humidity [%RH]
*/

int counter = 0;
float totalco2 = 0.0;

void printUint16Hex(uint16_t value) {
    Serial.print(value < 4096 ? "0" : "");
    Serial.print(value < 256 ? "0" : "");
    Serial.print(value < 16 ? "0" : "");
    Serial.print(value, HEX);
}

void printSerialNumber(uint16_t serial0, uint16_t serial1, uint16_t serial2) {
    Serial.print("Serial: 0x");
    printUint16Hex(serial0);
    printUint16Hex(serial1);
    printUint16Hex(serial2);
    Serial.println();
}

void setup() {


    Serial.begin(115200);
    while (!Serial) {
      delay(100);
    }
    WiFi.begin(ssid, password);
    Serial.println("Connecting");
    while(WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.print("OK! IP=");
    Serial.println(WiFi.localIP());
    pinMode(LED_BUILTIN, OUTPUT);

    Wire.begin();

    uint16_t error;
    char errorMessage[256];

    scd4x.begin(Wire);

    // stop potentially previously started measurement
    error = scd4x.stopPeriodicMeasurement();
    if (error) {
        Serial.print("Error trying to execute stopPeriodicMeasurement(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    }

    uint16_t serial0;
    uint16_t serial1;
    uint16_t serial2;
    error = scd4x.getSerialNumber(serial0, serial1, serial2);
    if (error) {
        Serial.print("Error trying to execute getSerialNumber(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    } else {
        printSerialNumber(serial0, serial1, serial2);
    }

    // Start Measurement
    error = scd4x.startPeriodicMeasurement();
    if (error) {
        Serial.print("Error trying to execute startPeriodicMeasurement(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    }

    Serial.println("Waiting for first measurement... (5 sec)");
}

void loop() {
  uint16_t error;
    char errorMessage[256];

    delay(100);

    // Read Measurement
    uint16_t co2 = 0;
    float temperature = 0.0f;
    float humidity = 0.0f;
    bool isDataReady = false;
    error = scd4x.getDataReadyFlag(isDataReady);
    if (error) {
        Serial.print("Error trying to execute getDataReadyFlag(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
        return;
    }
    if (!isDataReady) {
        return;
    }
    error = scd4x.readMeasurement(co2, temperature, humidity);
    if (error) {
        Serial.print("Error trying to execute readMeasurement(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    } else if (co2 == 0) {
        Serial.println("Invalid sample detected, skipping.");
    } else {
      counter++;
      Serial.print("Co2:");
      Serial.println(co2);
      totalco2 += co2;
    }
  analogWrite(LED_BUILTIN, 255);
  delay(1000);
  analogWrite(LED_BUILTIN, 250);
  if (counter % 10 == 0) {
    if(WiFi.status()== WL_CONNECTED){
      WiFiClientSecure client;
      HTTPClient http;
      client.setInsecure();
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      String httpRequestData = "api_key=co2sense!!69POG&sensor=m2SCD40&cotwo=" + String(totalco2/10.0);
      totalco2 = 0.0;
      Serial.println(httpRequestData);
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
       
      // Free resources
      http.end();
    }
    // uint16_t TVOC_base, eCO2_base;
    // if (! sgp.getIAQBaseline(&eCO2_base, &TVOC_base)) {
    //   Serial.println("Failed to get baseline readings");
    //   return;
    // }
    // Serial.print("****Baseline values: eCO2: 0x"); Serial.print(eCO2_base, HEX);
    // Serial.print(" & TVOC: 0x"); Serial.println(TVOC_base, HEX);
    if (counter == 5000) {
      counter = 0;
      Serial.println("5000 iterations, good time to reset maybe?");
    }
  }
  else {

    totalco2 += 1;
  }
}





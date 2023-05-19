#include <Wire.h>
#include "Adafruit_SGP30.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <string>


const char IRG_Root_X1 [] PROGMEM = R"CERT(
-----BEGIN CERTIFICATE-----
MIIGMTCCBRmgAwIBAgIQcc2NFdXxw2hTglU2dEnuDzANBgkqhkiG9w0BAQsFADCB
jzELMAkGA1UEBhMCR0IxGzAZBgNVBAgTEkdyZWF0ZXIgTWFuY2hlc3RlcjEQMA4G
A1UEBxMHU2FsZm9yZDEYMBYGA1UEChMPU2VjdGlnbyBMaW1pdGVkMTcwNQYDVQQD
Ey5TZWN0aWdvIFJTQSBEb21haW4gVmFsaWRhdGlvbiBTZWN1cmUgU2VydmVyIENB
MB4XDTIzMDQxODAwMDAwMFoXDTI0MDQxODIzNTk1OVowFzEVMBMGA1UEAxMMZXNk
Y290d28uYmlvMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAwtMZuiQs
40VaUtc+5lr570RuQtzkjvwgCn/su6myiSvsSjGcSkuPbiOuCLCQMhne9mSsMkmu
4rWd4Zd1C9GnqxdJgihNDKSrQLEC4O4wjxB60uO1eiaHFjJXJYU+AJ5Gim/sUka8
2UN0anx6ji7XtFn1Ilfcaw5QCY+mnlRr6Q5zV6MiddSG/UTTqJ4diMWlrmwf0fzh
lYl8p6IOmbTsCn9PTDvbqaUCj+lsQe0SZdO3Tt1Mrs8KSYla5uVMrMYLvyvlzuD8
fEmWeIYGr59B3WVt3Gn2531tKbzvpIniyMyzOUxGgFb+M+ZDCeHwA32u2D5Qi1Hh
QWUDuONTflGlWQIDAQABo4IC/jCCAvowHwYDVR0jBBgwFoAUjYxexFStiuF36Zv5
mwXhuAGNYeEwHQYDVR0OBBYEFFpqPcQTvp8f3Fjns3c5KW4t4v7/MA4GA1UdDwEB
/wQEAwIFoDAMBgNVHRMBAf8EAjAAMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggrBgEF
BQcDAjBJBgNVHSAEQjBAMDQGCysGAQQBsjEBAgIHMCUwIwYIKwYBBQUHAgEWF2h0
dHBzOi8vc2VjdGlnby5jb20vQ1BTMAgGBmeBDAECATCBhAYIKwYBBQUHAQEEeDB2
ME8GCCsGAQUFBzAChkNodHRwOi8vY3J0LnNlY3RpZ28uY29tL1NlY3RpZ29SU0FE
b21haW5WYWxpZGF0aW9uU2VjdXJlU2VydmVyQ0EuY3J0MCMGCCsGAQUFBzABhhdo
dHRwOi8vb2NzcC5zZWN0aWdvLmNvbTApBgNVHREEIjAgggxlc2Rjb3R3by5iaW+C
EHd3dy5lc2Rjb3R3by5iaW8wggF8BgorBgEEAdZ5AgQCBIIBbASCAWgBZgB1AHb/
iD8KtvuVUcJhzPWHujS0pM27KdxoQgqf5mdMWjp0AAABh5K48ugAAAQDAEYwRAIg
J782Qw4H3p5PyL0MDLXyh2vqaPfnsLJDHzDsOo2T+T0CIE0/eYYyDxrGUvOlXZHB
Ea873tehzq/20UbdghGfjVkfAHYA2ra/az+1tiKfm8K7XGvocJFxbLtRhIU0vaQ9
MEjX+6sAAAGHkrjzRAAABAMARzBFAiEA1eRU97WQWKt7jep+8BBBODrqmRhDyfEW
Famgb2b8shcCIF5A0kQ0ugWfuL10yizDo3+UBbJOWsQ4jWRzN63dDN3vAHUA7s3Q
ZNXbGs7FXLedtM0TojKHRny87N7DUUhZRnEftZsAAAGHkrjzYAAABAMARjBEAiAA
pICYT/mwnUqzrg3hBPEqkz+oP5TQBX76ywXxLI/SkQIgKJAxbAC0H5zzb20RbwHh
hiMYFoh8FuqU5nOrsIFY4AIwDQYJKoZIhvcNAQELBQADggEBAGvpKNjJvX+ZnTeb
NX8z+hj6GOMaH66EPeOjmz9m4upHbebxnbA2/s/rDbzs+BDHTG/Rm+oyqKB6wFQk
OyBJcP11a3rv5OltjiAm04JatwK8NgkBpuQ+JajQgWnr1s6xnwpvnmr5zxix7LNu
7MbOGBO8sARI+VRhdn8QbopEpO83C8gmOl5vuBGv9RQA3hPJZEQLX6cVVHmxPlgn
34I/JNgQ1Z82lWn9pBsya03y6I3R4zKWZymE1aaqM3KZtd20ZPc2OVZO3qxRTLS2
ymGW26Bmqtua2ikClxumkG+GpE4F5ytoQINB9KAYMQooZ68CDy0j2V4hu1z0lcrd
8TTT/Mg=
-----END CERTIFICATE-----
)CERT";




Adafruit_SGP30 sgp;
const char* ssid = "esddr";
const char* password = "eagles74";


const char* serverName = "https://esdcotwo.bio/co2/recieveData";


/* return absolute humidity [mg/m^3] with approximation formula
* @param temperature [°C]
* @param humidity [%RH]
*/
uint32_t getAbsoluteHumidity(float temperature, float humidity) {
    // approximation formula from Sensirion SGP30 Driver Integration chapter 3.15
    const float absoluteHumidity = 216.7f * ((humidity / 100.0f) * 6.112f * exp((17.62f * temperature) / (243.12f + temperature)) / (273.15f + temperature)); // [g/m^3]
    const uint32_t absoluteHumidityScaled = static_cast<uint32_t>(1000.0f * absoluteHumidity); // [mg/m^3]
    return absoluteHumidityScaled;
}


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("OK! IP=");
  Serial.println(WiFi.localIP());
  pinMode(LED_BUILTIN, OUTPUT);
  while (!Serial) { delay(10); } // Wait for serial console to open!


  Serial.println("SGP30 test");


  if (! sgp.begin()){
    Serial.println("Sensor not found :(");
    while (1);
  }
  Serial.print("Found SGP30 serial #");
  Serial.print(sgp.serialnumber[0], HEX);
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);


  // If you have a baseline measurement from before you can assign it to start, to 'self-calibrate'
  //sgp.setIAQBaseline(0x8E68, 0x8F41);  // Will vary for each sensor!
}


int counter = 0;
float totalco2 = 0.0;
void loop() {
  // If you have a temperature / humidity sensor, you can set the absolute humidity to enable the humditiy compensation for the air quality signals
  //float temperature = 22.1; // [°C]
  //float humidity = 45.2; // [%RH]
  //sgp.setHumidity(getAbsoluteHumidity(temperature, humidity));


  if (! sgp.IAQmeasure()) {
    Serial.println("Measurement failed");
    return;
  }
  Serial.print("eCO2 "); Serial.print(sgp.eCO2); Serial.println(" ppm");
  totalco2 += static_cast<float>(sgp.eCO2);


  if (! sgp.IAQmeasureRaw()) {
    Serial.println("Raw Measurement failed");
    return;
  }
  analogWrite(LED_BUILTIN, 255);
  delay(1000);
  analogWrite(LED_BUILTIN, 250);
  counter++;
  if (counter == 10) {
    if(WiFi.status()== WL_CONNECTED){
      WiFiClientSecure client;
      HTTPClient http;
      X509List cert(IRG_Root_X1);
      client.setInsecure();
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      String httpRequestData = "api_key=co2sense!!69POG&sensor=m1SGP30&cotwo=" + String(totalco2/10.0);
      totalco2 = 0.0;
      Serial.println(httpRequestData);
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
       
      // Free resources
      http.end();
    }
    counter = 0;
    Serial.print("5000 iterations, good time to reset maybe?");
    // uint16_t TVOC_base, eCO2_base;
    // if (! sgp.getIAQBaseline(&eCO2_base, &TVOC_base)) {
    //   Serial.println("Failed to get baseline readings");
    //   return;
    // }
    // Serial.print("****Baseline values: eCO2: 0x"); Serial.print(eCO2_base, HEX);
    // Serial.print(" & TVOC: 0x"); Serial.println(TVOC_base, HEX);
  }
  else {
    totalco2 += 1;
  }
}




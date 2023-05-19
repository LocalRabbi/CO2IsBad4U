
# CO2 Is Bad 4 U

CO2 causes a lot of mental problems, dont do it.

## Installation

1. You need Arduino Nightly IDE https://www.arduino.cc/en/software
2. Copy-paste the code into a new file.
3. Click the Board manager button on the nav bar in the IDE.
4. Install the ESP32 Package.
5. Click the Library manager button on the nav bar in the IDE.
6. Install the **SensirionI2CScd4x**, **Adafruit_SGP30**, **ESP8266WiFi**, **ESP8266HTTPClient**, and the **WiFiClientSecure** packages.
7. Make sure you have the USB-SERIAL CH340 Drivers https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all
8. Runload the code.

## Website

Thb you will probably need to change the code to interact with whatever website or local server you have set up. As well as changing the API insert to interact with whatever API you have set up. This section completely dependent on the kind of backend you have or what front end you decide to present.

## ESP8266 PINOUT

![image](https://github.com/LocalRabbi/CO2IsBad4U/assets/60053840/00b40db7-ffe8-4b52-93aa-6bb47c67e970)

## SCD VOLTAGE CURVE (LOW-HIGH)

![image](https://github.com/LocalRabbi/CO2IsBad4U/assets/60053840/82e947a7-aacf-440e-add0-ce3d79a2984a)
SGP voltage is linear, don't worry abt it.


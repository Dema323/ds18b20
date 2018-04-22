#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SPI.h>
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space

char auth[] = "xxxxx";

char ssid[] = "xxxxx";
char pass[] = "xxxxx";

/* TIMER */
//#include <SimpleTimer.h>  // NOT REQUIRED WITH BLYNK LIBRARY VERSION 0.4.8 AND BEYOND
/* DS18B20 Temperature Sensor */
#include <OneWire.h>
#include<DallasTemperature.h>
#include <SimpleTimer.h>

#define ONE_WIRE_BUS 2 // DS18B20 on arduino pin2 corresponds to D4 on physical board
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
float temp;
SimpleTimer timer;

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  DS18B20.begin();

}

void loop()
{
  timer.run(); // Initiates SimpleTimer
  Blynk.run();
  DS18B20.requestTemperatures();
  temp = DS18B20.getTempCByIndex(0);
  Serial.println(temp);
  Blynk.virtualWrite(10, temp); //virtual pin V10
}

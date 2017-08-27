// -*- mode: c -*-

#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>

// ==== "Global" parameters and variables =====================================================

#define ONE_WIRE_PIN  		      D5
#define LED_PIN                 D8
#define TEMPERATURE_PRECISION   12

const char *ssid     = "ZyXEL_3BCC";
const char *password = "9F4TAK3C4R333";
const char *host     = "192.168.1.43";

String url_template = "/cgi-bin/log_temperature.py";

uint8_t deviceCount;
String *temperatures;
String *deviceId;
  
#include "one_wire.h"
#include "wifi.h"

// ==== Main ===================================================================================

// const static long sleep = 10 * 1000 * 1000; // 10 sec -- while testing
const static unsigned long sleep = 3600UL * 1000UL * 1000UL;  // 1 hour

void setup() {

  Serial.begin(115200);
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  
  Serial.println("Sensor");
  
  Serial.print(__DATE__);
  Serial.print(" ");
  Serial.print(__TIME__);
  Serial.print(" ");
  Serial.print(__FILE__);
  Serial.print("\n");

  setup_one_wire();
  setup_wifi();

  loop_one_wire();
  loop_wifi();

  shutdown_wifi();

  Serial.println("Goodnight");
  Serial.println(millis());
  delay(10);

  ESP.deepSleep(sleep, RF_CAL);
}

long next_tick = 0;

void loop() {
  // Do nothing
}

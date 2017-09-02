// -*- mode: c -*-

#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>

// ==== "Global" parameters and variables =====================================================

#define TEST

#define ONE_WIRE_PIN  		D5
#define LED_PIN                 D8
#define TEMPERATURE_PRECISION   12

const char *ssid     = "ZyXEL_3BCC";
const char *password = "9F4TAK3C4R333";
const char *host     = "192.168.1.44";

String url_template = "/cgi-bin/log_temperature.py";

uint8_t deviceCount;
float *temperatures;
String *deviceId;
  
#include "one_wire.h"
#include "wifi.h"

// Select one

#include "main_sensor.h"

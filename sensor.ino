// -*- mode: c -*-

#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>

// ==== "Global" parameters and variables =====================================================

#define TEST

#define ONE_WIRE_PIN  		D5
#define LED_PIN                 D8
#define RELAY_PIN		D3

 #define TARGET_TEMPERATURE      78.0f
#define TEMPERATURE_TOLERANCE   0.5f
#define TEMPERATURE_PRECISION   12

#define WIFI_RETRY_DELAY        (10*60*1000) // 10 minutes
// #define WIFI_UPLOAD_INTERVAL	(60*1000)    // 1 minute
#define WIFI_UPLOAD_INTERVAL	(10*1000)    // 10 seconds (for testing)

const char *ssid     = "ZyXEL_3BCC";
const char *password = "9F4TAK3C4R333";
const char *host     = "192.168.1.44";

String url_template = "/cgi-bin/log_temperature.py";

uint8_t deviceCount;
float *temperatures;
String *deviceId;

#include "one_wire.h"
#include "wifi.h"
#include "relay.h"

// Select one

// #include "main_sensor.h"

#include "main_relay.h"

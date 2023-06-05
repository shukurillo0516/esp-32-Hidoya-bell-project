#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Preferences.h>
#include "RTClib.h"

// Main Loop config
const short MainLoopDelay = 100;

// WiFi Config
const char* ssid     = "ESP-32";
const char* password = "hello_world123!";

IPAddress local_ip(42,42,42,42);
IPAddress gateway(42,42,42,42);
IPAddress subnet(255,255,255,0);

// Web Server Config
WebServer server(80);

// Data Handler
Preferences preferences;

// RTC
RTC_DS3231 rtc;

// Pins Config
int led = 2;

const short AlarmListLen = 30;
const short ALarmActualLen = 20;
const char* alarmStorageName = "alarmStorage";

struct alarmSd {
  int hour;
  int minute;
  int len;
};

alarmSd alarmsList[AlarmListLen];
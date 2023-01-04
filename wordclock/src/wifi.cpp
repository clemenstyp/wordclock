#include <ESP8266WiFi.h>
#include <WiFiManager.h>

#include <stdio.h>
#include <time.h>

#include "httpServer.h"
#include "wifi.h"
#include <ESP8266mDNS.h>

#define USEOTA
// enable OTA
#ifdef USEOTA
#include <ArduinoOTA.h>
#include <WiFiUdp.h>
#endif

const char *modes[] = {"NULL", "STA", "AP", "STA+AP"};

unsigned long mtime = 0;

WiFiManager wifiManager;

void Wifi::saveWifiCallback(){
  Serial.println("saved Wifi restart ESP");
  ESP.restart();
}

void Wifi::setup() {

  WiFi.hostname("WordClock");
  WiFi.mode(WIFI_STA);

  wifiManager.setConfigPortalBlocking(false);
  wifiManager.setConfigPortalTimeout(120);

  wifiManager.setScanDispPerc(true);

  wifiManager.setSaveConfigCallback(Wifi::saveWifiCallback);
#ifdef USEOTA
  ArduinoOTA.begin("WordClock");
#endif

  if (wifiManager.autoConnect("WordClock","47110815")) {
    Serial.println("connected...yeey :)");
    HttpServer::setup();
  } else {
    Serial.println("Configportal running");
  }

  if (!MDNS.begin("WordClock")) {
    Serial.println("Error setting up MDNS responder!");
    
  }
}

void Wifi::reset() { 
  WiFi.disconnect(true); 
  wifiManager.resetSettings();
  }

void Wifi::loop() {
  wifiManager.process();
  MDNS.update();
#ifdef USEOTA
  ArduinoOTA.handle();
#endif
  HttpServer::loop();
}
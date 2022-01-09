#include "httpServer.h"
#include "controller.h"
#include "gui.h"
//#define FIRMWARE_VERSION  "2022-01-07_2"

//const char* fw_ver = FIRMWARE_VERSION;
ESP8266WebServer HttpServer::web(80);
AutoConnect Portal(HttpServer::web);
AutoConnectConfig Config;
String HttpServer::ip;


void HttpServer::setup() {
  Config.title = "WordClock";
  //Config.ota = AC_OTA_BUILTIN;
  //Config.otaExtraCaption = fw_ver;
  /*Config.autoReset = false;     // Not reset the module even by intentional
                                // disconnection using AutoConnect menu.
  Config.autoReconnect = true;  // Reconnect to known access points.
  Config.reconnectInterval = 6; // Reconnection attempting interval is 3[min].
  Config.autoRise = true; // It's the default, no setting is needed explicitly.
  Config.retainPortal = true; // Keep the captive portal open.*/
  Config.portalTimeout = 40000;  // It will time out in 60 seconds
  Config.retainPortal = true;
  Config.homeUri = "/";
  //Config.apid = "WordClock-" + String(ESP.getChipId(), HEX);
  Config.apid = "WordClock";
  Config.psk  = "";
  //Config.psk  = "WortUhr";

  Portal.config(Config);

  //Portal.disableMenu(AC_MENUITEM_RESET | AC_MENUITEM_HOME);

 
  HttpServer::web.on("/", Controller::index);

  HttpServer::web.on("/manifest.json", Controller::getManifest);
  HttpServer::web.on("/logo.svg", Controller::getLogoSvg);

  HttpServer::web.on("/api/color", HTTP_PUT, Controller::saveColor);
  HttpServer::web.on("/api/time", HTTP_PUT, Controller::saveTime);
  HttpServer::web.on("/api/dnd", HTTP_PUT, Controller::saveDnd);


  Portal.onNotFound([]() { Controller::index(); });

  if (Portal.begin()) {
    if (MDNS.begin("WordClock")) {
      MDNS.addService("http", "tcp", 80);
    }
    HttpServer::ip = WiFi.localIP().toString();
  }
}


void HttpServer::loop() {
  Portal.handleClient();
}


#ifndef WORDCLOCK_SERVER_H
#define WORDCLOCK_SERVER_H


#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <AutoConnect.h>

// void saveConfigCallback();
// void apCallback();

class HttpServer {
  public:
    static ESP8266WebServer web;
    static String ip;

    static void setup();
    static void loop();
    static void reset();
    static void startHttpServer();
    static void rootPage();
};
#endif

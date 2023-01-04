#ifndef WORDCLOCK_WIFI_H
#define WORDCLOCK_WIFI_H
#include <WiFiManager.h>

class Wifi {  
  public:
    static void setup();
    static void reset();
    static void loop();
    static void bindServerCallback();

    static void saveWifiCallback();
};

#endif

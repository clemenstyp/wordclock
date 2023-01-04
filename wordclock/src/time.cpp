#include <Arduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <RTClib.h>

#include "time.h"
#include "grid.h"
#include "utcOffset.h"


void Time::setup() {

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    // Serial.flush();
    // for (int i = 0; i< 1000;i++){
    //   delay(10);
    // }
  } 
  
   if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  Time:ntpClient.setUpdateInterval(600000);
  Time::ntpClient.begin();
  Time::ntpClient.update();
}

void Time::loop() {
  DateTime now = rtc.now();
  int h = now.hour();
  int m = now.minute();

  if (Time::ntpClient.update()) {
    if (! rtc.isrunning()) {
      if (!rtc.begin()) {
         Serial.println("Couldn't find RTC");
      } 
    }
    if (Time::ntpClient.isTimeSet()){
      rtc.adjust(DateTime(Time::ntpClient.getEpochTime()));
    }
  }
  if (Time::ntpClient.isTimeSet()){
    h = Time::ntpClient.getHours();
    m = Time::ntpClient.getMinutes();
  }

  if(m != Time::minute) {
    if(m == 0 && h == Time::hour) {
      h = (h + 1) % 24;
    }
    Time::hour = h;
    Time::minute = m;
    Grid::setTime(Time::hour, Time::minute);

    // char buf[15];
    // sprintf(buf, "Time: %02d:%02d", Time::hour, Time::minute);
    // Serial.println(buf);
    Serial.println(Time::ntpClient.getFormattedTime());

    if (Config::automatic_timezone) {
      UtcOffset::updateLocalizedUtcOffset();
      Time::ntpClient.setTimeOffset(Config::timezone);
    }
  }
}

int Time::hour = -1;
int Time::minute = -1;
RTC_DS1307 Time::rtc;
WiFiUDP Time::udp;
NTPClient Time::ntpClient = NTPClient(Time::udp);

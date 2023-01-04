# WordClock
**Based on [WordClock by panbachi](https://github.com/panbachi/wordclock)**

**Font and german layout based on https://www.mikrocontroller.net/articles/Word_Clock**

# Requirements

## Module:
* [Wemos D1 mini](https://www.az-delivery.de/products/d1-mini)
   [esp8266@2.7.4 by ESP8266 Community](https://github.com/esp8266/Arduino)
* [DS1307 RTC Module](https://lastminuteengineers.com/ds1307-rtc-arduino-tutorial/)

## Healthcheck
* [adafruit/FastLED@3.5.0 by Daniel Garcia](https://github.com/FastLED/FastLED)

## WordClock
* [adafruit/FastLED@3.5.0 by Daniel Garcia](https://github.com/FastLED/FastLED)
* [NTPClient@3.2.1 by Fabrice Weinberg](https://github.com/arduino-libraries/NTPClient)
* [WiFiManager@2.0.15-rc.1 by tzapu](https://github.com/tzapu/WiFiManager)
* [ArduinoJson@6.20.0 by Benoit Blanchon](https://github.com/bblanchon/ArduinoJson)
* [RTClib@2.1.1 by Adafruit](https://github.com/adafruit/RTClib)


# Assemble
[![Word-Clock - Die WLAN Wort-Uhr zum selber bauen](https://img.youtube.com/vi/FvAM1t0tISE/0.jpg)](https://www.youtube.com/watch?v=FvAM1t0tISE)

# Connection

|  Port   |     Connection      |
|---------|---------------------|
|  D3     | Databus LED Stripe  |
|  D1     | RTC Clock - SCL     |
|  D2     | RTC CLock - SDA     |


# Customizations
## Modify `user_config.h` to change config
| Key                 | Values                                                           | Comment                  |
|---------------------|------------------------------------------------------------------|--------------------------|
| GRID_ROWS           | 10<br>11                                                         | count of rows            |
| GRID_COLS           | 11                                                               | count of cols            |
| GRID_FIRST          | 0: top-left<br>1: top-right<br>2: buttom-left<br>3: buttom-right | position of first led    |
| GRID_LANGUAGE       | de_DE: german<br>de_DE_alt: german alternative                   | langauge                 |
| GRID_SINGLE_MINUTES | 0: before<br>1: after                                            | position of minutes leds |

# Installation
Make your Arduino ready for Wemos D1 mini e.g. https://makesmart.net/esp8266-d1-mini-programmieren/
- Change the grid settings in the `wordclock/user_config.h`.
- Upload the sketch `wordclock/wordclock.ino` to your Wemos D1 mini (or other ESP8266).
- Enjoy

# Usage
The WordClock creates a WiFi-Hotspot with the name "WordClock". Connect e.g. your smartphone to the hotspot and you will be forwared to the config page, where you can set the WiFi credentials.
Check in your router what IP-adress your WordClock got. Open a webbrowser and go to `http://[YOUR_WORDCLOCK_IP]`. For (example) the IP-adress `192.168.178.20` go to `http://192.168.178.20`.

# Functions

## Set color
You can set a foreground and background color on your clock.

## Set time offset
You can set a time offset to specify your timezone.

## Set DND
You can set a time span in which the clock should be switched off.

## PWA
You can use the webbrowser function "Add to start screen" to install the webinterface as an app to your android (and possibly ios) smartphone.

# Create own grid-layout
To create your own grid-layout visit the Wiki: [Create Grid-Layout](https://github.com/panbachi/wordclock/wiki/Create-Grid-Layout)

# Support me / Follow me
[![Web](https://img.shields.io/badge/www-panbachi.de-blue.svg?style=flat-square&colorB=3d72a8&colorA=333333)](https://www.panbachi.de)
[![Facebook](https://img.shields.io/badge/-%40panbachi.de-blue.svg?style=flat-square&logo=facebook&colorB=3B5998&colorA=333333)](https://www.facebook.com/panbachi.de/)
[![Twitter](https://img.shields.io/badge/-%40panbachi.de-blue.svg?style=flat-square&logo=twitter&colorB=1DA1F2&colorA=333333)](https://twitter.com/panbachi)
[![Instagram](https://img.shields.io/badge/-%40panbachi.de-blue.svg?style=flat-square&logo=instagram&colorB=E4405F&colorA=333333)](http://instagram.com/panbachi.de)
[![YouTube](https://img.shields.io/badge/-%40panbachi.de-blue.svg?style=flat-square&logo=youtube&colorB=FF0000&colorA=333333)](https://www.youtube.com/channel/UCO7f2L7ZsDCpOtRfKnPqNow)

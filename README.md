# WordClock

**Based loosly on [WordClock by panbachi](https://github.com/panbachi/wordclock) and [Word Clock One by SkyexTechnologies](https://github.com/SkyexTechnologies/word-clock-one)**

**Font and german layout based on https://www.mikrocontroller.net/articles/Word_Clock**

# Requirements

## Module:
* [Wemos D1 mini](https://www.az-delivery.de/products/d1-mini)
   [esp8266@2.7.4 by ESP8266 Community](https://github.com/esp8266/Arduino)
* [DS1307 RTC Module](https://lastminuteengineers.com/ds1307-rtc-arduino-tutorial/)


## Install / Update:

[Install with ESP Web](https://clemenstyp.github.io/wordclock/)



# Assemble

[![Word-Clock - Die WLAN Wort-Uhr zum selber bauen](https://img.youtube.com/vi/FvAM1t0tISE/0.jpg)](https://www.youtube.com/watch?v=FvAM1t0tISE)

# Connection

|  Port   |     Connection      |
|---------|---------------------|
|  D3     | Databus LED Stripe  |
|  D1     | RTC Clock - SCL     |
|  D2     | RTC CLock - SDA     |


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

## Build localy:
`docker run --rm --privileged -v "${PWD}":/config -it ghcr.io/esphome/esphome compile wordclock-esp8266-d1-mini-dev.debug.yaml`

or install it with brew
`brew install esphome`

and run:
`esphome compile wordclock-esp8266-d1-mini-dev.debug.yaml`



or use the docker sh script:
`./esphome.sh compile wordclock-esp8266-d1-mini-dev.debug.yaml`

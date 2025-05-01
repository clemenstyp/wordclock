#include <FS.h>
#include "LittleFS.h"
#include <ArduinoJson.h>

#include "config.h"
#include "types.h"
#include "time.h"
#include "led.h"
#include "utcOffset.h"

void Config::setup(){

    // Dateisystem formatieren
  //LittleFS.format();

  // Dateisystem initialisieren
  if( LittleFS.begin() ){
    Serial.println("Dateisystem: initialisiert");
  }else{
    Serial.println("Dateisystem: Fehler beim initialisieren");
  }
}

void Config::save() {
  //File file = SPIFFS.open("/wordclock_config.json", "w");
  File file = LittleFS.open("/wordclock_config.json", "w");

  if(!file) {
    Serial.println("Can't open wordclock_config.json for writing");
    return;
  }


  Time::ntpClient.setPoolServerName(Config::ntp.c_str());
  Time::ntpClient.setTimeOffset(Config::timezone);

  //StaticJsonDocument<1024> doc;

  JsonDocument doc;

  doc["color_bg_r"] = Config::color_bg.r;
  doc["color_bg_g"] = Config::color_bg.g;
  doc["color_bg_b"] = Config::color_bg.b;
  doc["color_fg_r"] = Config::color_fg.r;
  doc["color_fg_g"] = Config::color_fg.g;
  doc["color_fg_b"] = Config::color_fg.b;
  doc["power_supply"] = Config::power_supply;
  doc["brightness"] = Config::brightness;
  doc["tz_auto"] = Config::automatic_timezone;
  doc["timezone"] = Config::timezone;
  doc["dnd_active"] = Config::dnd_active;
  doc["dnd_start_hour"] = Config::dnd_start.hour;
  doc["dnd_start_minute"] = Config::dnd_start.minute;
  doc["dnd_end_hour"] = Config::dnd_end.hour;
  doc["dnd_end_minute"] = Config::dnd_end.minute;
  doc["ntp"] = Config::ntp;
  doc["healthcheck"] = Config::healthcheck;

  serializeJson(doc, file);

  file.close();
  Serial.println("Config saved.");
  // Serial.println("Config:");
  // serializeJson(doc, Serial);

}

void Config::load() {
  Config::color_bg.r = 0;
  Config::color_bg.g = 0;
  Config::color_bg.b = 0;

  Config::color_fg.r = 255;
  Config::color_fg.g = 255;
  Config::color_fg.b = 255;

  Config::power_supply = 500; // default: 500mA (USB 2.0 specification)
  Config::brightness = 0.5;

  Config::automatic_timezone = true;
  Config::timezone = 0;

  Config::dnd_active = false;
  Config::dnd_start.hour = -1;
  Config::dnd_start.minute = -1;
  Config::dnd_end.hour = -1;
  Config::dnd_end.minute = -1;
  Config::ntp = "pool.ntp.org";

  Config::healthcheck = false;

  //File file = SPIFFS.open("/wordclock_config.json", "r");
  File file = LittleFS.open("/wordclock_config.json", "r");

  if(!file) {
    Serial.println("Failed to open config file.");
    Config::save();
    return;
  }


  // StaticJsonDocument<1024> doc;
  JsonDocument doc;
  deserializeJson(doc, file);

  Serial.println("Config 1:");
  serializeJson(doc, Serial);

  Config::color_bg.r = doc["color_bg_r"].as<int>();
  Config::color_bg.g = doc["color_bg_g"].as<int>();
  Config::color_bg.b = doc["color_bg_b"].as<int>();

  Config::color_fg.r = doc["color_fg_r"].as<int>();
  Config::color_fg.g = doc["color_fg_g"].as<int>();
  Config::color_fg.b = doc["color_fg_b"].as<int>();

  if(doc["power_supply"]) {
    Config::power_supply = doc["power_supply"].as<int>();
  }

  if(doc["brightness"]) {
    Config::brightness =
      (doc["brightness"].as<double>() > Led::getMaxBrightnessPercnt()) ? Led::getMaxBrightnessPercnt() : doc["brightness"].as<double>();
  }

  if (doc["tz_auto"]) {
    Config::automatic_timezone = doc["tz_auto"].as<bool>();
  }

  // load the last known timezone in any case.
  Config::timezone = doc["timezone"].as<int>();

  if (Config::automatic_timezone) {
    UtcOffset::updateLocalizedUtcOffset();
  }

  Config::dnd_active = doc["dnd_active"].as<bool>();
  Config::dnd_start.hour = doc["dnd_start_hour"].as<int>();
  Config::dnd_start.minute = doc["dnd_start_minute"].as<int>();
  Config::dnd_end.hour = doc["dnd_end_hour"].as<int>();
  Config::dnd_end.minute = doc["dnd_end_minute"].as<int>();

  if(doc["ntp"]) {
    Config::ntp = doc["ntp"].as<String>();
  }

  if(doc["healthcheck"]){
    Config::healthcheck = doc["healthcheck"].as<bool>();
  }

  Time::ntpClient.setPoolServerName(Config::ntp.c_str());
  Time::ntpClient.setTimeOffset(Config::timezone);

  file.close();


  Serial.println("Config loaded.");

  // Serial.println("Config:");
  // serializeJson(doc, Serial);
}

color_t Config::color_bg{};
color_t Config::color_fg{};
int Config::power_supply{};
double Config::brightness{};
bool Config::automatic_timezone{};
int Config::timezone{};
bool Config::dnd_active{};
clock_time_t Config::dnd_start{};
clock_time_t Config::dnd_end{};
String Config::ntp{};
bool Config::healthcheck{};

#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#include "utcOffset.h"
#include "config.h"

int parseUtcOffsetToHours(const String& utcOffset) {
  int sign = (utcOffset[0] == '-') ? -1 : 1;
  int hours = utcOffset.substring(1, 3).toInt();
  
  return sign * hours;
}

void UtcOffset::updateLocalizedUtcOffset() {
/* remove the depricated ESP8266 API call:  
 *HTTPClient http;
 *http.begin("http://worldtimeapi.org/api/ip");
*/

//  use the new API like below:
  WiFiClient client;
  HTTPClient http;
  //http.begin(client, "http://worldtimeapi.org/api/ip");
  http.begin(client, "https://ipapi.co/json");
  int responseCode = http.GET();

  if (responseCode == 200) {
    String payload = http.getString();

    StaticJsonDocument<1024> doc;
    deserializeJson(doc, payload);

    // int utcOffset = doc["raw_offset"].as<int>();
    // int dstOffset = doc["dst_offset"].as<int>();

    // const int newTimezone = utcOffset + dstOffset;
    String utcOffsetStr = doc["utc_offset"];
    const int newTimezone = parseUtcOffsetToHours(utcOffsetStr);

    http.end();

    const int oldTimezone = Config::timezone;

    if (oldTimezone != newTimezone) {

      // save new timezone to config
      Serial.print("Old timezone: ");
      Serial.println(Config::timezone);
      Serial.print("New timezone: ");
      Serial.println(newTimezone);

      Config::timezone = newTimezone;
      Config::save();
    }

    return;
  }
  http.end();

  // use last known offset
  return;
}

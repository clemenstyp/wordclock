#include <Arduino.h>

#include "de_DE_round.h"

#include "../config.h"
#include "../dnd.h"
#include "../led.h"

void Grid_de_DE_round::setTime(int correctHour, int correctMinute) {
  if (correctHour == -1 || correctMinute == -1) {
    return;
  }

  if (DND::active(correctHour, correctMinute)) {
    for (int i = 0; i < NUM_LEDS; i++) {
      Led::ids[i].setRGB(0, 0, 0);
    }

    FastLED.show();

    return;
  }

  int correctMinuteOfDay = (correctHour * 60) + correctMinute;

  int minDiff = correctMinuteOfDay % 5;
  int minuteDifference = 0;
  if (minDiff <= 2) {
    minuteDifference = minDiff;
  } else {
    minuteDifference = minDiff - 5;
  }
  int roundedMinuteOfDay = correctMinuteOfDay - minuteDifference;

  int minute = roundedMinuteOfDay % 60;
  int hour = roundedMinuteOfDay / 60;
  int hourLimit = 6;

  // if the difference is -2 minutes - the first 3 led lights (0|0|0|x|x)
  // if the clock shows the correct time (diff = 0) the third led lights
  // (x|x|0|x|x) if the difference is +1 minute - the following led lights
  // (x|x|0|0|x)

  // für halb und viertel vor:
  if (minute >= 25) {
    hour += 1;
  }

  minute = minute / 5;
  hour = hour % 12;

  // background color
  for (int i = 0; i < NUM_LEDS; i++) {
    Led::ids[i].setRGB(Config::color_bg.r * 0.2,
                       Config::color_bg.g * 0.2,
                       Config::color_bg.b * 0.2);
  }

  // show es ist:
  for (int i = 0; i < 5; i++) {
    Led::ids[Led::getLedId(Grid_de_DE_round::time_it_is[i])].setRGB(
        Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
  }

  // show minutes
  for (int m = 0; m < 12; m++) {
    if (Grid_de_DE_round::time_minutes[minute][m] >= 0) {
      Led::ids[Led::getLedId(Grid_de_DE_round::time_minutes[minute][m])].setRGB(
          Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
    }
  }

  // show stunden

  if (hour == 1 && minute == 0) {
    hourLimit = 3; // show "ein" instead of "eins"
  }

  for (int h = 0; h < hourLimit; h++) {
    if (Grid_de_DE_round::time_hours[hour][h] >= 0) {
      Led::ids[Led::getLedId(Grid_de_DE_round::time_hours[hour][h])].setRGB(
          Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
    }
  }

  // single minutes 0: before, led 0,1,2,3
  int singleMinutesFirstLED = 0;
  if (GRID_SINGLE_MINUTES == 1) {
    singleMinutesFirstLED = NUM_LEDS - EXTRA_LEDS;
  }

  // if the difference is -2 minutes - the first 2 led lights (0|0|x|x|x)
  // if the clock shows the correct time (diff = 0) the third led lights
  // (x|x|0|x|x) if the difference is +1 minute - the following led lights
  // (x|x|x|0|x)
  switch (minuteDifference) {
  case -2:
    Led::ids[singleMinutesFirstLED].setRGB(Config::color_fg.r,
                                           Config::color_fg.g,
                                           Config::color_fg.b);
    Led::ids[singleMinutesFirstLED + 1].setRGB(Config::color_fg.r,
                                               Config::color_fg.g,
                                               Config::color_fg.b);
    break;
  case -1:
    Led::ids[singleMinutesFirstLED + 1].setRGB(Config::color_fg.r,
                                               Config::color_fg.g,
                                               Config::color_fg.b);
    break;
  case 0:
    Led::ids[singleMinutesFirstLED + 2].setRGB(Config::color_fg.r,
                                               Config::color_fg.g,
                                               Config::color_fg.b);
    break;
  case 1:
    Led::ids[singleMinutesFirstLED + 3].setRGB(Config::color_fg.r,
                                               Config::color_fg.g,
                                               Config::color_fg.b);
    break;
  case +2:
    Led::ids[singleMinutesFirstLED + 3].setRGB(Config::color_fg.r,
                                               Config::color_fg.g,
                                               Config::color_fg.b);
    Led::ids[singleMinutesFirstLED + 4].setRGB(Config::color_fg.r,
                                               Config::color_fg.g,
                                               Config::color_fg.b);
    break;
  default:
    break;
  }
  FastLED.setBrightness(Config::brightness * 255);
  FastLED.show();
}

int Grid_de_DE_round::time_it_is[5] = {0, 1, 3, 4, 5}; // es ist

int Grid_de_DE_round::time_minutes[12][12] = {
    {107, 108, 109, -1, -1, -1, -1, -1, -1, -1, -1, -1}, // uhr
    {7, 8, 9, 10, 35, 36, 37, 38, -1, -1, -1, -1},       // fünf nach
    {11, 12, 13, 14, 35, 36, 37, 38, -1, -1, -1, -1},    // zehn nach
    {26, 27, 28, 29, 30, 31, 32, 35, 36, 37, 38, -1},    // viertel nach
    {15, 16, 17, 18, 19, 20, 21, 35, 36, 37, 38, -1},    // zwanzig nach
    {7, 8, 9, 10, 39, 40, 41, 44, 45, 46, 47, -1},       // fünf vor halb
    {44, 45, 46, 47, -1, -1, -1, -1, -1, -1, -1, -1},    // halb
    {7, 8, 9, 10, 35, 36, 37, 38, 44, 45, 46, 47},       // fünf nach halb
    {15, 16, 17, 18, 19, 20, 21, 39, 40, 41, -1, -1},    // zwanzig vor
    {26, 27, 28, 29, 30, 31, 32, 39, 40, 41, -1, -1},    // viertel vor
    {11, 12, 13, 14, 39, 40, 41, -1, -1, -1, -1, -1},    // zehn vor
    {7, 8, 9, 10, 39, 40, 41, -1, -1, -1, -1, -1}        // fünf vor
};

int Grid_de_DE_round::time_hours[12][6] = {
    {49, 50, 51, 52, 53, -1},      // zwölf
    {57, 58, 59, 60, -1, -1},      // eins
    {55, 56, 57, 58, -1, -1},      // zwei
    {67, 68, 69, 70, -1, -1},      // drei
    {84, 85, 86, 87, -1, -1},      // vier
    {73, 74, 75, 76, -1, -1},      // fünf
    {100, 101, 102, 103, 104, -1}, // sechs
    {60, 61, 62, 63, 64, 65},      // sieben
    {89, 90, 91, 92, -1, -1},      // acht
    {80, 81, 82, 83, -1, -1},      // neun
    {93, 94, 95, 96, -1, -1},      // zehn
    {77, 78, 79, -1, -1, -1}       // elf
};

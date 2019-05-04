/*
  Anti-Aliased Crawlers for FastLED:
  originally created by Mark Kriegsman <kriegsman@tr.org>, November 29, 2013
  turned into a class by Matt Richard, September 5, 2017
*/

#ifndef Crawler_h
#define Crawler_h

#include "Arduino.h"
#include "FastLED.h"


class Crawler
{
  public:
    Crawler();        // constructor definiton
    int     pos16;   // position of the "fraction-based bar"
    int     delta16; // how many 16ths of a pixel to move the Fractional Bar
    int     width;    // width of each light bar, in whole pixels
    uint8_t hue;     // color for Fractional Bar
    int _NUM_LEDS;
    void setup(int _pos16, int _delta16, int _width, uint8_t _hue, int __NUM_LEDS);
    void drawFractionalBar(CRGB* _leds);
    void calcLoc();
    void render(CRGB* _leds);
};

#endif

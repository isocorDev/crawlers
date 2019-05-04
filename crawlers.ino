// Anti-aliased light bar example
//   v1 by Mark Kriegsman <kriegsman@tr.org>, November 29, 2013
//   v2 by Matt Richard, September 5, 2017 - created class based on Mark Kreigsman's code

#include <FastLED.h>
#include "Crawler.h"

#define CHIP_SET WS2813     // CHANGE: chip set for LED strip
#define DATA_PIN 9          // CHANGE: data pin for LED strip
#define COLOR_ORDER RGB     // CHANGE: led color order for LED strip
#define NUM_LEDS 1200       // CHANGE: number of LEDs on LED strip
#define BRIGHTNESS 128      // CHANGE: brightness for LED strip 0-255 = 0%-100%
CRGB leds[NUM_LEDS];        // DO NOT CHANGE: array of color values for each pixel in LED strip

#define NUM_CRAWLERS 100          // CHANGE: number of "glowworms" or "crawlers"
Crawler crawlers[NUM_CRAWLERS];   // DO NOT CHANGE: array of crawlers
uint8_t crawlerSpeed_min = 1;     // CHANGE: minimum range of normal speed - keep above 0 unless you want the chance of staying still
uint8_t crawlerSpeed_max = 5;     // CHANGE: maximum range of normal speed
uint8_t crawlerSuperSpeed_chance = 15;   // CHANGE: chance of a fast crawler, the lower the number the greater the chance
uint8_t crawlerSuperSpeed_min = 14;      // CHANGE: minimum range of fast speed
uint8_t crawlerSuperSpeed_max = 16;      // CHANGE: maximum range of fast speed
uint8_t crawlerWidth_min = 3;     // CHANGE: minimum range of crawler width
uint8_t crawlerWidth_max = 5;     // CHANGE: maximum range of crawler width

int InterframeDelay = 10;   // CHANGE: frame delay in ms

void setup() {
  delay(3000); // setup guard
  FastLED.addLeds<CHIP_SET, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  randomSeed(analogRead(0));

  for (int i = 0; i < NUM_CRAWLERS; i++) {
    // random initial position
    int cs_position = int(floor(random(NUM_LEDS / 2)));
    
    // SPEED - either superspeed or normal speed, then determine direction (+ or -)
    int cs_delta;
    if (random8(100) % crawlerSuperSpeed_chance == 0) {
      cs_delta = int(random(crawlerSuperSpeed_min, crawlerSuperSpeed_max));
    }else{
      cs_delta = random8(crawlerSpeed_min, crawlerSpeed_max);
    }
    if (random8(100) % 2 == 0) {
      cs_delta *= -1;//  flips positive to negative
    }
    
    int cs_width = int(random(crawlerWidth_min, crawlerWidth_max));

    uint8_t cs_hue = map( i, 0, NUM_CRAWLERS, 0, 255);
    
    crawlers[i].setup(cs_position, cs_delta, cs_width, cs_hue, NUM_LEDS / 2);
  }
}

void loop()
{
  // Draw everything:
  // clear the pixel buffer
  memset8( leds, 0, NUM_LEDS * sizeof(CRGB));

  // draw all of the crawlers
  // must pass FastLED array so the objects can write(and overwrite) to the main array
  for (int i = 0; i < NUM_CRAWLERS; i++) {
    crawlers[i].render(leds);
  }

  // mirror pixels to second half of strip
  for (int j = 0; j < (NUM_LEDS / 2); j++) {
    int newLED = (NUM_LEDS - 1) - j;
    leds[newLED] = leds[j];
  }

  FastLED.show();
  FastLED.delay(InterframeDelay);
}


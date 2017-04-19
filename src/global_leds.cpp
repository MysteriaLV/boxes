//
// Created by VermutMac on 4/19/2017.
//

#include "global_leds.h"

CRGB GLOBAL_LEDS[NUM_LEDS];


void setup_global_leds() {
//    FastLED.addLeds<NEOPIXEL, attached_pin>(leds, LENGTH);
    FastLED.addLeds<NEOPIXEL, 13>(GLOBAL_LEDS, NUM_LEDS);
    FastLED.setBrightness(1);
//    FastLED.clear(true);
}

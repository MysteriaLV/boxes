//
// Created by VermutMac on 4/19/2017.
//

#include "LedRibbon.h"

void LedRibbon::setup() {
    FastLED.addLeds<NEOPIXEL, 13>(this->leds, NUM_LEDS);

}
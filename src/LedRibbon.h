//
// Created by VermutMac on 4/19/2017.
//

#ifndef ALIENSBOXES_LEDRIBBON_H
#define ALIENSBOXES_LEDRIBBON_H

#include <FastLED.h>

#define NUM_LEDS 144*4

class LedRibbon {
    CRGB leds[NUM_LEDS];

public:
    void setup();

    void step(int idx, int v, int up);

    void finish(int idx, int v, int up);
};


#endif //ALIENSBOXES_LEDRIBBON_H

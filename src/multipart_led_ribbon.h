//
// Created by VermutMac on 4/19/2017.
//

#ifndef ALIENSBOXES_MULTIPART_LED_RIBBON_H
#define ALIENSBOXES_MULTIPART_LED_RIBBON_H

#include <FastLED.h>

#define NUM_LEDS 144*4

class MultipartLedRibbon {
public:
    void setup();
    void fill_sold_ext(int from, int length, uint32_t color);
    void show();

    CRGB leds[NUM_LEDS];
};

extern MultipartLedRibbon multipartLedRibbon;

#endif //ALIENSBOXES_MULTIPART_LED_RIBBON_H

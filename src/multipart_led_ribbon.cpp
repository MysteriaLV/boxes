//
// Created by VermutMac on 4/19/2017.
//

#include "multipart_led_ribbon.h"

MultipartLedRibbon multipartLedRibbon;

void MultipartLedRibbon::setup() {
    FastLED.addLeds<NEOPIXEL, 13>(leds, NUM_LEDS);
    FastLED.setBrightness(1);
}

void MultipartLedRibbon::fill_sold_ext(int from, int length, uint32_t color) {
    fill_solid(leds, length, color);
}

void MultipartLedRibbon::show() {
    FastLED.show();
}
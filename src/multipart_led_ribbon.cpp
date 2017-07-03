//
// Created by VermutMac on 4/19/2017.
//

#include "multipart_led_ribbon.h"

MultipartLedRibbon multipartLedRibbon;

void MultipartLedRibbon::setup() {
    FastLED.addLeds<NEOPIXEL, LED_RIBBON_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(100);
}

void MultipartLedRibbon::fill_sold_ext(int from, int length, uint32_t color) {
    fill_solid(&leds[from], length, color);
}

void MultipartLedRibbon::show() {
    FastLED.show();
}
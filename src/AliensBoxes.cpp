#include <Automaton.h>
#include "Atm_led_ribbon.h"
#include "multipart_led_ribbon.h"

Atm_button button;
Atm_led_ribbon ledRibbon;

int n = 0;

/*

void setup() {
    Serial.begin(57600);
    Serial.print("sfddsfds");
    button.trace(Serial);
    ledRibbon.trace(Serial);

    FastLED.addLeds<NEOPIXEL, 13>(multipartLedRibbon.leds, NUM_LEDS);
    ledRibbon.begin();

    button.begin(6)
            .onPress(ledRibbon, ledRibbon.EVT_MAKE_PROGRESS)
            .onRelease(ledRibbon, ledRibbon.EVT_WRONG_MOVE);
}
*/

void loop() {
    automaton.run();
}

void setup() {
    multipartLedRibbon.setup();

//    Serial.begin(57600);
//    Serial.print("sfddsfds");
//    button.trace(Serial);
//    ledRibbon.trace(Serial);
    ledRibbon.begin();
    button.begin(6)
            .onPress(ledRibbon, ledRibbon.EVT_MAKE_PROGRESS)
            .onRelease(ledRibbon, ledRibbon.EVT_WRONG_MOVE);

}

void loop2() {
    multipartLedRibbon.leds[n % NUM_LEDS] = CRGB::Red;
    multipartLedRibbon.leds[n % NUM_LEDS] %= quadwave8(n * 5);

    multipartLedRibbon.leds[(n + 144) % NUM_LEDS] = CRGB::Green;
    multipartLedRibbon.leds[(n + 144) % NUM_LEDS] %= quadwave8(n * 6);

    multipartLedRibbon.leds[(n + 244) % NUM_LEDS] = CRGB::Blue;
    multipartLedRibbon.leds[(n + 244) % NUM_LEDS] %= quadwave8(n * 7);

    multipartLedRibbon.leds[(n + 344) % NUM_LEDS] = CRGB::White;
    multipartLedRibbon.leds[(n + 344) % NUM_LEDS] %= quadwave8(n * 8);

    multipartLedRibbon.show();
    delay(10);

    multipartLedRibbon.leds[n % NUM_LEDS] = CRGB::Black;
    multipartLedRibbon.leds[(n + 144) % NUM_LEDS] = CRGB::Black;
    multipartLedRibbon.leds[(n + 244) % NUM_LEDS] = CRGB::Black;
    multipartLedRibbon.leds[(n + 344) % NUM_LEDS] = CRGB::Black;

    multipartLedRibbon.show();
    delay(10);
    n++;
}


#include <Automaton.h>
#include "Atm_led_ribbon.h"
//#include "global_leds.h"

Atm_button button;
Atm_led_ribbon ledRibbon;

void step_callback(int idx, int v, int up) {
    Serial.print("Step id=");
    Serial.println(v);
}

void setup() {
    Serial.begin(57600);
    Serial.print("sfddsfds");
    button.trace(Serial);
    ledRibbon.trace(Serial);

//    setup_global_leds();

    ledRibbon.begin(6613);

    button.begin(6)
            .onPress(ledRibbon, ledRibbon.EVT_MAKE_PROGRESS)
            .onRelease(ledRibbon, ledRibbon.EVT_WRONG_MOVE);
}

void loop() {
    automaton.run();
}

#include "Atm_main_sequence.h"
#include "multipart_led_ribbon.h"


void setup() {
    multipartLedRibbon.setup();

    Serial.begin(57600);
//    button1.trace(Serial);
//    q1OneButton.trace(Serial);
    main_sequence.trace( Serial );

    button1.begin(6);

    main_sequence.begin();
}

void loop() {
    automaton.run();
}

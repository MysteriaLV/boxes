#include "Atm_main_sequence.h"
#include "multipart_led_ribbon.h"

void setup() {
    multipartLedRibbon.setup();

    Serial.begin(57600);
//    button1.trace(Serial);

    button1.begin(2);
    button2.begin(3);
    button3.begin(4);
    button4.begin(5);
    button5.begin(6);
    button6.begin(7);

    main_sequence.begin();
}

void loop() {
    automaton.run();
}

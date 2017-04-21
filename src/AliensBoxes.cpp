#include "Atm_main_sequence.h"
#include "multipart_led_ribbon.h"
#include "SimpleModbusSlaveSoftwareSerial.h"

Atm_led led1, led2, led3;

void setup() {
    modbus_configure(57600, 3, 3, 1);

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

    led1.begin( 30 ).blink( 40, 250 ); // Setup blinking
    led2.begin( 31 ).blink( 40, 50 );
    led3.begin( 32 ).blink( 40, 150 );
    led1.trigger( led1.EVT_BLINK );   // Start blinking
    led2.trigger( led2.EVT_BLINK );
    led3.trigger( led3.EVT_BLINK );
}

void loop() {
    automaton.run();
}

#include "Atm_main_sequence.h"
#include "multipart_led_ribbon.h"

extern void modbus_setup();
extern void modbus_loop();
extern unsigned int holdingRegs[]; // function 3 and 16 register array


void setup() {
	multipartLedRibbon.setup();
	Serial.begin(57600);

	button1.begin(2);
	button2.begin(3);
	button3.begin(4);
	button4.begin(5);
	button5.begin(6);
	button6.begin(7);

	led1.begin(30);
	led2.begin(31);
	led3.begin(32);
	led4.begin(33);
	led5.begin(34);
	led6.begin(35);

	modbus_setup();
	main_sequence.begin();
}

void loop() {
	modbus_loop();
	automaton.run();
}

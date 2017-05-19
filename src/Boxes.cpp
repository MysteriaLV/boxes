#include "Atm_main_sequence.h"
#include "multipart_led_ribbon.h"

extern void modbus_setup();
extern void modbus_loop();
extern unsigned int holdingRegs[]; // function 3 and 16 register array

#define TEST_MODE
Atm_timer test_mode_timer1;
Atm_timer test_mode_timer2;

void setup() {
	Serial.begin(115200);
	modbus_setup();
	multipartLedRibbon.setup();

	button1.begin(38);
	button2.begin(40);
	button3.begin(42);
	button4.begin(44);
	button5.begin(46);
	button6.begin(48);
	button7.begin(50);
	button8.begin(52);

	led1.begin(23, true);
	led2.begin(25, true);
	led3.begin(27, true);
	led4.begin(29, true);
	led5.begin(31, true);
	led6.begin(33, true);
	led7.begin(35, true);
	led8.begin(37, true);

	ufo1.begin(39, true);
	ufo2.begin(41, true);
	ufo3.begin(43, true);
	ufo4.begin(45, true);
	ufo5.begin(47, true);
	ufo6.begin(49, true);
	ufo7.begin(51, true);
	ufo8.begin(53, true);

	door1.begin(22, true).trace(Serial);
	door2.begin(24, true);
	door3.begin(26, true);
	door4.begin(28, true);
	door5.begin(30, true);
	door6.begin(32, true);
	door7.begin(34, true);
	door8.begin(36, true);

#ifndef TEST_MODE
	main_sequence.begin();
#else
	button1.onPress(door1, door1.EVT_OFF).onRelease(door1, door1.EVT_ON).trace(Serial);
	button2.onPress(door2, door2.EVT_OFF).onRelease(door2, door2.EVT_ON);
	button3.onPress(door3, door3.EVT_OFF).onRelease(door3, door3.EVT_ON);
	button4.onPress(door4, door4.EVT_OFF).onRelease(door4, door4.EVT_ON);
	button5.onPress(door5, door5.EVT_OFF).onRelease(door5, door5.EVT_ON);
	button6.onPress(door6, door6.EVT_OFF).onRelease(door6, door6.EVT_ON);
	button7.onPress(door7, door7.EVT_OFF).onRelease(door7, door7.EVT_ON);
	button8.onPress(door8, door8.EVT_OFF).onRelease(door8, door8.EVT_ON);

	led1.blink(500).start();
	led2.blink(500).start();
	led3.blink(500).start();
	led4.blink(500).start();
	led5.blink(500).start();
	led6.blink(500).start();
	led7.blink(500).start();
	led8.blink(500).start();

	ufo1.blink(500).start();
	ufo2.blink(500).start();
	ufo3.blink(500).start();
	ufo4.blink(500).start();
	ufo5.blink(500).start();
	ufo6.blink(500).start();
	ufo7.blink(500).start();
	ufo8.blink(500).start();

	test_mode_timer1.begin(10)
			.repeat(NUM_LEDS)
			.onTimer( [] ( int idx, int v, int up ) {
				multipartLedRibbon.fill_sold_ext(0, NUM_LEDS, CRGB::Gold);
				multipartLedRibbon.fill_sold_ext(0, v, CRGB::White);
				multipartLedRibbon.show();
			})
			.onFinish(test_mode_timer2, test_mode_timer1.EVT_START)
			.start();

	test_mode_timer2.begin(1)
			.onFinish(test_mode_timer1, test_mode_timer1.EVT_START);
#endif
}

void loop() {
	modbus_loop();
	automaton.run();
}

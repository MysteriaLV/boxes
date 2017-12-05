#include "Atm_main_sequence.h"
#include "multipart_led_ribbon.h"

extern void modbus_setup();
extern void modbus_loop();

//#define MY_TEST_MODE
//#define MY_EASY_MODE
Atm_timer test_mode_timer1;
Atm_timer test_mode_timer2;

void setup() {
	Serial.begin(115200);
	modbus_setup();
	multipartLedRibbon.setup();

	button1.debounce(30).begin(38);
	button2.debounce(30).begin(40);
	button3.debounce(30).begin(42);
	button4.debounce(30).begin(44);
	button5.debounce(30).begin(46);
	button6.debounce(30).begin(48);
	button7.debounce(30).begin(50);
	button8.debounce(30).begin(52);

	led1.begin(23);
	led2.begin(25);
	led3.begin(27);
	led4.begin(29);
	led5.begin(31);
	led6.begin(33);
	led7.begin(35);
	led8.begin(37);

	ufo1.begin(39);
	ufo2.begin(41);
	ufo3.begin(43);
	ufo4.begin(45);
	ufo5.begin(47);
	ufo6.begin(49);
	ufo7.begin(51);
	ufo8.begin(53);

	door1.begin(22).off();
	door2.begin(24).on();
	door3.begin(26).on();
	door4.begin(28).on();
	door5.begin(30).on();
	door6.begin(32).on();
	door7.begin(34).on();
	door8.begin(36).on();

#ifndef MY_TEST_MODE
	main_sequence.begin();
#else
	button1.onPress(door2, door2.EVT_OFF).onRelease(door2, door2.EVT_ON).trace(Serial);
	button2.onPress(door3, door3.EVT_OFF).onRelease(door3, door3.EVT_ON);
	button3.onPress(door4, door4.EVT_OFF).onRelease(door4, door4.EVT_ON);
	button4.onPress(door5, door5.EVT_OFF).onRelease(door5, door5.EVT_ON);
	button5.onPress(door6, door6.EVT_OFF).onRelease(door6, door6.EVT_ON);
	button6.onPress(door7, door7.EVT_OFF).onRelease(door7, door7.EVT_ON);
	button7.onPress(door8, door8.EVT_OFF).onRelease(door8, door8.EVT_ON);

	led1.blink(500, 500).start();
	led2.blink(500, 500).start();
	led3.blink(500, 500).start();
	led4.blink(500, 500).start();
	led5.blink(500, 500).start();
	led6.blink(500, 500).start();
	led7.blink(500, 500).start();

	ufo1.blink(500, 500).start();
	ufo2.blink(500, 500).start();
	ufo3.blink(500, 500).start();
	ufo4.blink(500, 500).start();
	ufo5.blink(500, 500).start();
	ufo6.blink(500, 500).start();
	ufo7.blink(500, 500).start();

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

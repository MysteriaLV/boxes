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

	button1.begin(30);
	button2.begin(32);
	button3.begin(34);
	button4.begin(36);
	button5.begin(38);
	button6.begin(40);
	button7.begin(42);
	button8.begin(44);

	led1.begin(31);
	led2.begin(33);
	led3.begin(35);
	led4.begin(37);
	led5.begin(39);
	led6.begin(41);
	led7.begin(43);
	led8.begin(45);

#ifndef TEST_MODE
	main_sequence.begin();
#else
	button1.onPress(led1, led1.EVT_OFF).onRelease(led1, led1.EVT_ON);
	button2.onPress(led2, led2.EVT_OFF).onRelease(led2, led2.EVT_ON);
	button3.onPress(led3, led3.EVT_OFF).onRelease(led3, led3.EVT_ON);
	button4.onPress(led4, led4.EVT_OFF).onRelease(led4, led4.EVT_ON);
	button5.onPress(led5, led5.EVT_OFF).onRelease(led5, led5.EVT_ON);
	button6.onPress(led6, led6.EVT_OFF).onRelease(led6, led6.EVT_ON);
	button7.onPress(led7, led7.EVT_OFF).onRelease(led7, led7.EVT_ON);
	button8.onPress(led8, led8.EVT_OFF).onRelease(led8, led8.EVT_ON);

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

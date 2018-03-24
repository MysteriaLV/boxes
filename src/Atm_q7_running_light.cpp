#include "Atm_q7_running_light.h"
#include "Atm_main_sequence.h"
#include "multipart_led_ribbon.h"

const auto SPOT_WIDTH = 10;

Atm_running_light q7RunningLight;

/* Add optional parameters for the state machine to begin()
 * Add extra initialization code
 */

Atm_running_light &Atm_running_light::begin() {
	// clang-format off
  const static state_t state_table[] PROGMEM = {
    /*                   ON_ENTER    ON_LOOP    ON_EXIT  EVT_ZONE1  EVT_ZONE2  EVT_ZONE3  EVT_ZONE4  EVT_ZONE5  EVT_ZONE6  EVT_ZONE7  EVT_TIMEOUT  EVT_BTN1_PRESSED  EVT_BTN2_PRESSED  EVT_BTN3_PRESSED  EVT_BTN4_PRESSED  EVT_BTN5_PRESSED  EVT_BTN6_PRESSED  EVT_BTN7_PRESSED     ELSE */
    /*      INIT */      ENT_INIT,        -1,        -1,        -1,        -1,        -1,        -1,        -1,        -1,        -1,          -1,               -1,               -1,               -1,               -1,               -1,               -1,               -1, RUNNING,
    /*   RUNNING */   ENT_RUNNING,        -1,        -1,     ZONE1,     ZONE2,     ZONE3,     ZONE4,     ZONE5,     ZONE6,     ZONE7,     RUNNING,        INCORRECT,        INCORRECT,        INCORRECT,        INCORRECT,        INCORRECT,        INCORRECT,        INCORRECT,      -1,
    /*     ZONE1 */     ENT_ZONE1,        -1, EXT_ZONE1,        -1,        -1,        -1,        -1,        -1,        -1,        -1,   INCORRECT,          CORRECT,        INCORRECT,        INCORRECT,        INCORRECT,        INCORRECT,        INCORRECT,        INCORRECT,      -1,
    /*     ZONE2 */     ENT_ZONE2,        -1, EXT_ZONE2,        -1,        -1,        -1,        -1,        -1,        -1,        -1,   INCORRECT,        INCORRECT,          CORRECT,        INCORRECT,        INCORRECT,        INCORRECT,        INCORRECT,        INCORRECT,      -1,
    /*     ZONE3 */     ENT_ZONE3,        -1, EXT_ZONE3,        -1,        -1,        -1,        -1,        -1,        -1,        -1,   INCORRECT,        INCORRECT,        INCORRECT,          CORRECT,        INCORRECT,        INCORRECT,        INCORRECT,        INCORRECT,      -1,
    /*     ZONE4 */     ENT_ZONE4,        -1, EXT_ZONE4,        -1,        -1,        -1,        -1,        -1,        -1,        -1,   INCORRECT,        INCORRECT,        INCORRECT,        INCORRECT,          CORRECT,        INCORRECT,        INCORRECT,        INCORRECT,      -1,
    /*     ZONE5 */     ENT_ZONE5,        -1, EXT_ZONE5,        -1,        -1,        -1,        -1,        -1,        -1,        -1,   INCORRECT,        INCORRECT,        INCORRECT,        INCORRECT,        INCORRECT,          CORRECT,        INCORRECT,        INCORRECT,      -1,
    /*     ZONE6 */     ENT_ZONE6,        -1, EXT_ZONE6,        -1,        -1,        -1,        -1,        -1,        -1,        -1,   INCORRECT,        INCORRECT,        INCORRECT,        INCORRECT,        INCORRECT,        INCORRECT,          CORRECT,        INCORRECT,      -1,
    /*     ZONE7 */     ENT_ZONE7,        -1, EXT_ZONE7,        -1,        -1,        -1,        -1,        -1,        -1,        -1,        INIT,             INIT,             INIT,             INIT,             INIT,             INIT,             INIT,         FINISHED,      -1,
    /*   CORRECT */   ENT_CORRECT,        -1,        -1,        -1,        -1,        -1,        -1,        -1,        -1,        -1,          -1,               -1,               -1,               -1,               -1,               -1,               -1,               -1, RUNNING,
    /* INCORRECT */ ENT_INCORRECT,        -1,        -1,        -1,        -1,        -1,        -1,        -1,        -1,        -1,          -1,               -1,               -1,               -1,               -1,               -1,               -1,               -1, RUNNING,
    /*  FINISHED */  ENT_FINISHED,        -1,        -1,        -1,        -1,        -1,        -1,        -1,        -1,        -1,          -1,               -1,               -1,               -1,               -1,               -1,               -1,               -1,      -1,
  };
  // clang-format on
	Machine::begin(state_table, ELSE);

	button1.onPress(*this, this->EVT_BTN1_PRESSED);
	button2.onPress(*this, this->EVT_BTN2_PRESSED);
	button3.onPress(*this, this->EVT_BTN3_PRESSED);
	button4.onPress(*this, this->EVT_BTN4_PRESSED);
	button5.onPress(*this, this->EVT_BTN5_PRESSED);
	button6.onPress(*this, this->EVT_BTN6_PRESSED);
	button7.onPress(*this, this->EVT_BTN7_PRESSED);

	trace(Serial);
	return *this;
}

/* Add C++ code for each internally handled event (input)
 * The code must return 1 to trigger the event
 */

int Atm_running_light::event(int id) {
	switch (id) {
		case EVT_ZONE1:
			return getLength() - tick_reverse_location.value == BTN1_POSITION + 2;      // Magic number so we don't miss point 0
		case EVT_ZONE2:
            return getLength() - tick_reverse_location.value == BTN2_POSITION - SPOT_WIDTH / 2;
        case EVT_ZONE3:
            return getLength() - tick_reverse_location.value == BTN3_POSITION - SPOT_WIDTH / 2;
        case EVT_ZONE4:
            return getLength() - tick_reverse_location.value == BTN4_POSITION - SPOT_WIDTH / 2;
        case EVT_ZONE5:
            return getLength() - tick_reverse_location.value == BTN5_POSITION - SPOT_WIDTH / 2;
        case EVT_ZONE6:
            return getLength() - tick_reverse_location.value == BTN6_POSITION - SPOT_WIDTH / 2;
        case EVT_ZONE7:
            return getLength() - tick_reverse_location.value == BTN7_POSITION - SPOT_WIDTH / 2;
        case EVT_TIMEOUT:
			return timer_timeout.expired(this);
		default:
			return 0;
	}
}

/* Add C++ code for each action
 * This generates the 'output' for the state machine
 */

void Atm_running_light::action(int id) {
	switch (id) {
		case ENT_INIT:
			multipartLedRibbon.fill_sold_ext(getOffset(), getLength(), CRGB::MediumSeaGreen);
			multipartLedRibbon.show();

			led1.off();
			led2.off();
			led3.off();
			led4.off();
			led5.off();
			led6.off();
			led7.off();

			ufo1.off();
			ufo2.off();
			ufo3.off();
			ufo4.off();
			ufo5.off();
			ufo6.off();
			ufo7.off();

			tick_reverse_location.set(getLength());
			counter_progress.set(7);
			return;
		case ENT_RUNNING:
			multipartLedRibbon.fill_sold_ext(getLength() - tick_reverse_location.value, SPOT_WIDTH, CRGB::MediumSeaGreen);
			tick_reverse_location.decrement();
			multipartLedRibbon.fill_sold_ext(getLength() - tick_reverse_location.value, SPOT_WIDTH, CRGB::Red);
			multipartLedRibbon.show();

			timer_timeout.set(next_tick_timeout);
			return;
		case ENT_ZONE1:
			timer_timeout.set(next_press_timeout);
            currentLed = &led1;
            currentUfo = &ufo1;
            return;
		case EXT_ZONE1:
			return;
		case ENT_ZONE2:
			timer_timeout.set(next_press_timeout);
            currentLed = &led2;
            currentUfo = &ufo2;
			return;
		case EXT_ZONE2:
			return;
		case ENT_ZONE3:
			timer_timeout.set(next_press_timeout);
            currentLed = &led3;
            currentUfo = &ufo3;
			return;
		case EXT_ZONE3:
			return;
		case ENT_ZONE4:
			timer_timeout.set(next_press_timeout);
            currentLed = &led4;
            currentUfo = &ufo4;
			return;
		case EXT_ZONE4:
			return;
		case ENT_ZONE5:
			timer_timeout.set(next_press_timeout);
            currentLed = &led5;
            currentUfo = &ufo5;
			return;
		case EXT_ZONE5:
			return;
		case ENT_ZONE6:
			timer_timeout.set(next_press_timeout);
            currentLed = &led6;
            currentUfo = &ufo6;
			return;
		case EXT_ZONE6:
			return;
		case ENT_ZONE7:
			timer_timeout.set(next_press_timeout);
            currentLed = &led7;
            currentUfo = &ufo7;
			return;
		case EXT_ZONE7:
			return;
		case ENT_CORRECT:
            currentLed->on();
            currentUfo->on();
			counter_progress.decrement();
			return;
		case ENT_INCORRECT:
			return;
		case ENT_FINISHED:
			counter_progress.decrement();
			if (!counter_progress.expired()) {
				// Correct last answer due to transition, but not whole 7
				state(INIT);
				return;
			}

			timer_timeout.set(ATM_TIMER_OFF);
			counter_progress.set(ATM_COUNTER_OFF);
			led1.off();
			led2.off();
			led3.off();
			led4.off();
			led5.off();
			led6.off();
			led7.off();

			ufo1.off();
			ufo2.off();
			ufo3.off();
			ufo4.off();
			ufo5.off();
			ufo6.off();
			ufo7.off();

			multipartLedRibbon.fill_sold_ext(getOffset(), getLength(), CRGB::BlueViolet);
			multipartLedRibbon.show();

			main_sequence.trigger(main_sequence.EVT_SOLVED);
			return;
		default:
			break;
	}
}

/* State trace method
 * Sets the symbol table and the default logging method for serial monitoring
 */

Atm_running_light &Atm_running_light::trace(Stream &stream) {
	Machine::setTrace(&stream, atm_serial_debug::trace,
	                  "RUNNING_LIGHT\0EVT_ZONE1\0EVT_ZONE2\0EVT_ZONE3\0EVT_ZONE4\0EVT_ZONE5\0EVT_ZONE6\0EVT_ZONE7\0EVT_TIMEOUT\0EVT_BTN1_PRESSED\0EVT_BTN2_PRESSED\0EVT_BTN3_PRESSED\0EVT_BTN4_PRESSED\0EVT_BTN5_PRESSED\0EVT_BTN6_PRESSED\0EVT_BTN7_PRESSED\0ELSE\0INIT\0RUNNING\0ZONE1\0ZONE2\0ZONE3\0ZONE4\0ZONE5\0ZONE6\0ZONE7\0CORRECT\0INCORRECT\0FINISHED");
	return *this;
}


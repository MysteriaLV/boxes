#include "Atm_q5_multi_morse_reader.h"
#include "Atm_main_sequence.h"

Atm_multi_morse_reader q5multiMorseReader;

/* Add optional parameters for the state machine to begin()
 * Add extra initialization code
 */

Atm_multi_morse_reader &Atm_multi_morse_reader::begin() {
	// clang-format off
  const static state_t state_table[] PROGMEM = {
    /*                 ON_ENTER    ON_LOOP   ON_EXIT  EVT_TIMEOUT  EVT_BTN1_PRESSED  EVT_BTN2_PRESSED  EVT_BTN3_PRESSED  EVT_BTN4_PRESSED  EVT_BTN5_PRESSED  ELSE */
    /*     IDLE */     ENT_IDLE,        -1, EXT_IDLE,          L3,               -1,               -1,               S0,               -1,               -1,   -1,
    /*       S0 */       ENT_S0,        -1,       -1,        IDLE,             IDLE,               S1,             IDLE,             IDLE,             IDLE,   -1,
    /*       S1 */       ENT_S1,        -1,       -1,        IDLE,               S2,             IDLE,             IDLE,             IDLE,             IDLE,   -1,
    /*       S2 */       ENT_S2,        -1,       -1,        IDLE,             IDLE,             IDLE,             IDLE,             IDLE,               S3,   -1,
    /*       S3 */       ENT_S3,        -1,       -1,        IDLE,             IDLE,             IDLE,             IDLE,         FINISHED,             IDLE,   -1,
    /*       L1 */       ENT_L1,        -1,   EXT_L1,          L5,               -1,               -1,               S0,               -1,               -1,   -1,
    /*       L2 */       ENT_L2,        -1,   EXT_L2,          L1,               -1,               -1,               S0,               -1,               -1,   -1,
    /*       L3 */       ENT_L3,        -1,   EXT_L3,          L2,               -1,               -1,               S0,               -1,               -1,   -1,
    /*       L4 */       ENT_L4,        -1,   EXT_L4,        IDLE,               -1,               -1,               S0,               -1,               -1,   -1,
    /*       L5 */       ENT_L5,        -1,   EXT_L5,          L4,               -1,               -1,               S0,               -1,               -1,   -1,
    /* FINISHED */ ENT_FINISHED, ATM_SLEEP,       -1,          -1,               -1,               -1,               S0,               -1,               -1,   -1,
  };
  // clang-format on
	Machine::begin(state_table, ELSE);

	button1.onPress(*this, this->EVT_BTN1_PRESSED);
	button2.onPress(*this, this->EVT_BTN2_PRESSED);
	button3.onPress(*this, this->EVT_BTN3_PRESSED);
	button4.onPress(*this, this->EVT_BTN4_PRESSED);
	button5.onPress(*this, this->EVT_BTN5_PRESSED);

//	trace(Serial);
	return *this;
}

/* Add C++ code for each internally handled event (input)
 * The code must return 1 to trigger the event
 */

int Atm_multi_morse_reader::event(int id) {
	switch (id) {
		case EVT_TIMEOUT:
			return timer_timeout.expired( this );
	}
	return 0;
}

/* Add C++ code for each action
 * This generates the 'output' for the state machine
 */

void Atm_multi_morse_reader::action(int id) {
	switch (id) {
		case ENT_IDLE:
			timer_timeout.set(2000);
			counter_progress.set(getNumSteps());

			multipartLedRibbon.fill_sold_ext(this->getOffset(), getFullLength(), CRGB::Black);
			multipartLedRibbon.show();
			return;
		case EXT_IDLE:
			// NOOP
			return;

		case ENT_S0:
		case ENT_S1:
		case ENT_S2:
		case ENT_S3:
			counter_progress.decrement();
			timer_timeout.set(next_press_timeout);
			multipartLedRibbon.fill_sold_ext(this->getOffset(), (int) (getLength() / getNumSteps() * (getNumSteps() - counter_progress.value)), CRGB::Teal);
			multipartLedRibbon.show();
			return;

		case ENT_L1:
			timer_timeout.set(200);
			led1.on();
			return;
		case EXT_L1:
			led1.off();
			return;
		case ENT_L2:
			timer_timeout.set(200);
			led2.on();
			return;
		case EXT_L2:
			led2.off();
			return;
		case ENT_L3:
			timer_timeout.set(200);
			led3.on();
			return;
		case EXT_L3:
			led3.off();
			return;
		case ENT_L4:
			timer_timeout.set(200);
			led4.on();
			return;
		case EXT_L4:
			led4.off();
			return;
		case ENT_L5:
			timer_timeout.set(200);
			led5.on();
			return;
		case EXT_L5:
			led5.off();
			return;
		case ENT_FINISHED:
			multipartLedRibbon.fill_sold_ext(this->getOffset(), getFullLength(), CRGB::MediumSeaGreen);
			multipartLedRibbon.show();

			main_sequence.trigger(main_sequence.EVT_SOLVED);
			return;
	}
}


/* Optionally override the default trigger() method
 * Control how your machine processes triggers
 */

Atm_multi_morse_reader &Atm_multi_morse_reader::trigger(int event) {
	Machine::trigger(event);
	return *this;
}

/* Optionally override the default state() method
 * Control what the machine returns when another process requests its state
 */

int Atm_multi_morse_reader::state(void) {
	return Machine::state();
}

/* Nothing customizable below this line
 ************************************************************************************************
*/

/* Public event methods
 *
 */

/* State trace method
 * Sets the symbol table and the default logging method for serial monitoring
 */

Atm_multi_morse_reader &Atm_multi_morse_reader::trace(Stream &stream) {
	Machine::setTrace(&stream, atm_serial_debug::trace,
    "MULTI_MORSE_READER\0EVT_TIMEOUT\0EVT_BTN1_PRESSED\0EVT_BTN2_PRESSED\0EVT_BTN3_PRESSED\0EVT_BTN4_PRESSED\0EVT_BTN5_PRESSED\0ELSE\0IDLE\0S0\0S1\0S2\0S3\0L1\0L2\0L3\0L4\0L5\0FINISHED" );
	return *this;
}

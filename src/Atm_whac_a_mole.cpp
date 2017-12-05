#include "Atm_whac_a_mole.h"
#include "Atm_main_sequence.h"
#include "multipart_led_ribbon.h"

Atm_whac_a_mole q6WhacAMole;

/* Add optional parameters for the state machine to begin()
 * Add extra initialization code
 */

Atm_whac_a_mole &Atm_whac_a_mole::begin() {
	// clang-format off
  const static state_t state_table[] PROGMEM = {
    /*                   ON_ENTER    ON_LOOP   ON_EXIT  EVT_TIMEOUT  EVT_BTN1_PRESSED  EVT_BTN2_PRESSED  EVT_BTN3_PRESSED  EVT_BTN4_PRESSED  EVT_BTN5_PRESSED  EVT_BTN6_PRESSED  ELSE */
    /*      BTN1 */      ENT_BTN1,        -1, EXT_BTN1,   INCORRECT,          CORRECT,        INCORRECT,        INCORRECT,        INCORRECT,        INCORRECT,        INCORRECT,   -1,
    /*      BTN2 */      ENT_BTN2,        -1, EXT_BTN2,   INCORRECT,        INCORRECT,          CORRECT,        INCORRECT,        INCORRECT,        INCORRECT,        INCORRECT,   -1,
    /*      BTN3 */      ENT_BTN3,        -1, EXT_BTN3,   INCORRECT,        INCORRECT,        INCORRECT,          CORRECT,        INCORRECT,        INCORRECT,        INCORRECT,   -1,
    /*      BTN4 */      ENT_BTN4,        -1, EXT_BTN4,   INCORRECT,        INCORRECT,        INCORRECT,        INCORRECT,          CORRECT,        INCORRECT,        INCORRECT,   -1,
    /*      BTN5 */      ENT_BTN5,        -1, EXT_BTN5,   INCORRECT,        INCORRECT,        INCORRECT,        INCORRECT,        INCORRECT,          CORRECT,        INCORRECT,   -1,
    /*      BTN6 */      ENT_BTN6,        -1, EXT_BTN6,   INCORRECT,        INCORRECT,        INCORRECT,        INCORRECT,        INCORRECT,        INCORRECT,          CORRECT,   -1,
    /*   CORRECT */   ENT_CORRECT,        -1,       -1,          -1,               -1,               -1,               -1,               -1,               -1,               -1,   -1,
    /* INCORRECT */ ENT_INCORRECT,        -1,       -1,          -1,               -1,               -1,               -1,               -1,               -1,               -1,   -1,
    /*  FINISHED */  ENT_FINISHED, ATM_SLEEP,       -1,          -1,               -1,               -1,               -1,               -1,               -1,               -1,   -1,
  };
  // clang-format on
	Machine::begin(state_table, ELSE);

	randomSeed(analogRead(A0));

	button1.onPress(*this, this->EVT_BTN1_PRESSED);
	button2.onPress(*this, this->EVT_BTN2_PRESSED);
	button3.onPress(*this, this->EVT_BTN3_PRESSED);
	button4.onPress(*this, this->EVT_BTN4_PRESSED);
	button5.onPress(*this, this->EVT_BTN5_PRESSED);
	button6.onPress(*this, this->EVT_BTN6_PRESSED);

    trace(Serial);
	trigger(EVT_TIMEOUT);
	return *this;
}

/* Add C++ code for each internally handled event (input)
 * The code must return 1 to trigger the event
 */

int Atm_whac_a_mole::event(int id) {
	switch (id) {
		case EVT_TIMEOUT:
			return timer_timeout.expired(this);
		default:
			return 0;
	}
}

/* Add C++ code for each action
 * This generates the 'output' for the state machine
 */

void Atm_whac_a_mole::action(int id) {
	switch (id) {
		case ENT_BTN1:
			led1.on();
			return;
		case EXT_BTN1:
			led1.off();
			return;
		case ENT_BTN2:
			led2.on();
			return;
		case EXT_BTN2:
			led2.off();
			return;
		case ENT_BTN3:
			led3.on();
			return;
		case EXT_BTN3:
			led3.off();
			return;
		case ENT_BTN4:
			led4.on();
			return;
		case EXT_BTN4:
			led4.off();
			return;
		case ENT_BTN5:
			led5.on();
			return;
		case EXT_BTN5:
			led5.off();
			return;
		case ENT_BTN6:
			led6.on();
			return;
		case EXT_BTN6:
			led6.off();
			return;
		case ENT_CORRECT:
			counter_progress.decrement();
			if (counter_progress.expired()) {
				Machine::state(FINISHED);
				return;
			}

			multipartLedRibbon.fill_sold_ext(this->getOffset(),
			                                 (int) (getLength() / getNumSteps() * (getNumSteps() - counter_progress.value)),
			                                 CRGB::Teal);
			multipartLedRibbon.show();

			next_mole();
			return;
		case ENT_INCORRECT:
			counter_progress.set(getNumSteps());
			multipartLedRibbon.fill_sold_ext(this->getOffset(), getLength(), CRGB::Black);
			multipartLedRibbon.show();

			next_mole();
			return;
		case ENT_FINISHED:
			timer_timeout.set(ATM_TIMER_OFF);
			counter_progress.set(ATM_COUNTER_OFF );
			led1.off();
			led2.off();
			led3.off();
			led4.off();
			led5.off();
			led6.off();

			multipartLedRibbon.fill_sold_ext(getOffset(), getLength(), CRGB::MediumSeaGreen);
			multipartLedRibbon.show();

			main_sequence.trigger(main_sequence.EVT_SOLVED);
			return;
		default:
			break;
	}
}

void Atm_whac_a_mole::next_mole() {
	timer_timeout.set(next_press_timeout + counter_progress.value*next_press_timeout_per_step);
	Machine::state(randomize_mole());
}

int Atm_whac_a_mole::randomize_mole() {
	int next_mole = random(BTN1, BTN6+1);
	if (current_mole == next_mole)
		return randomize_mole();

	current_mole = next_mole;
	return current_mole;
}

/* Optionally override the default trigger() method
 * Control how your machine processes triggers
 */

Atm_whac_a_mole &Atm_whac_a_mole::trigger(int event) {
	Machine::trigger(event);
	return *this;
}

/* Optionally override the default state() method
 * Control what the machine returns when another process requests its state
 */

int Atm_whac_a_mole::state(void) {
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

Atm_whac_a_mole &Atm_whac_a_mole::trace(Stream &stream) {
	Machine::setTrace(&stream, atm_serial_debug::trace,
	                  "WHAC_A_MOLE\0EVT_TIMEOUT\0EVT_BTN1_PRESSED\0EVT_BTN2_PRESSED\0EVT_BTN3_PRESSED\0EVT_BTN4_PRESSED\0EVT_BTN5_PRESSED\0EVT_BTN6_PRESSED\0ELSE\0BTN1\0BTN2\0BTN3\0BTN4\0BTN5\0BTN6\0CORRECT\0INCORRECT\0FINISHED");
	return *this;
}


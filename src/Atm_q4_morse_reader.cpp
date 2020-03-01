#include "Atm_q4_morse_reader.h"
#include "multipart_led_ribbon.h"
#include "Atm_main_sequence.h"

/* Add optional parameters for the state machine to begin()
 * Add extra initialization code
 */
Atm_morse_reader q4SingleMorseReader;

Atm_morse_reader &Atm_morse_reader::begin() {
	// clang-format off
	const static state_t state_table[] PROGMEM = {
			/*                 ON_ENTER  ON_LOOP   ON_EXIT  EVT_TIMEOUT  EVT_SHORT_PRESS  EVT_LONG_PRESS  ELSE */
			/*     IDLE */     ENT_IDLE,      -1, EXT_IDLE,          -1,              S0,             -1,   -1,
			/*       S0 */       ENT_S0,      -1,       -1,        IDLE,              S1,           IDLE,   -1,
			/*       S1 */       ENT_S1,      -1,       -1,        IDLE,              S2,           IDLE,   -1,
			/*       S2 */       ENT_S2,      -1,       -1,        IDLE,            IDLE,             S3,   -1,
			/*       S3 */       ENT_S3,      -1,       -1,        IDLE,            IDLE,             S4,   -1,
			/*       S4 */       ENT_S4,      -1,       -1,        IDLE,            IDLE,             S5,   -1,
			/*       S5 */       ENT_S5,      -1,       -1,        IDLE,              S6,           IDLE,   -1,
			/*       S6 */       ENT_S6,      -1,       -1,        IDLE,              S7,           IDLE,   -1,
			/*       S7 */       ENT_S7,      -1,       -1,        IDLE,        FINISHED,           IDLE,   -1,
			/*       S8 */       ENT_S8,      -1,       -1,        IDLE,              -1,             -1,   -1,
			/*       S9 */       ENT_S9,      -1,       -1,        IDLE,              -1,             -1,   -1,
			/* FINISHED */ ENT_FINISHED,      -1,       -1,          -1,              -1,             -1,   -1,
	};
	// clang-format on
	Machine::begin(state_table, ELSE);

	button4.longPress(2, 600)
			.onPress(1, *this, this->EVT_SHORT_PRESS)  // Short press
			.onPress(2, *this, this->EVT_LONG_PRESS); // Long press

	trace(Serial);
	return *this;
}

/* Add C++ code for each internally handled event (input) 
 * The code must return 1 to trigger the event
 */

int Atm_morse_reader::event(int id) {
	switch (id) {
		case EVT_TIMEOUT:
			return timer_timeout.expired( this );
	}
	return 0;
}

/* Add C++ code for each action
 * This generates the 'output' for the state machine
 */

void Atm_morse_reader::action(int id) {
	switch (id) {
		case ENT_IDLE:
			timer_timeout.set(ATM_TIMER_OFF);

			multipartLedRibbon.fill_sold_ext(this->getOffset(), getFullLength(), CRGB::Black);
			multipartLedRibbon.show();

			// Define two leds (patterns)
			dot.begin(pin).blink(dotTime, longwaitTime, 3);
			dash.begin(pin).blink(dashTime, longwaitTime, 3);

			// Define a timer
			stepTimer.begin(3700).repeat(ATM_COUNTER_OFF);

			// Define a step sequencer and link it to the leds we defined earlier
			step.begin()
					.onStep(0, dot, Atm_led::EVT_BLINK)
					.onStep(1, dash, Atm_led::EVT_BLINK)
					.onStep(2, dot, Atm_led::EVT_BLINK);

			// Set up the timer to drive the step sequencer
			stepTimer.onTimer(step, Atm_step::EVT_STEP);

			// Start the timer
			stepTimer.start();
			return;
		case EXT_IDLE:
			stepTimer.stop();
			dot.off();
			dash.off();

			counter_progress.set(getNumSteps());
			return;
		case ENT_S0:
		case ENT_S1:
		case ENT_S2:
		case ENT_S3:
		case ENT_S4:
		case ENT_S5:
		case ENT_S6:
		case ENT_S7:
		case ENT_S8:
		case ENT_S9:
			counter_progress.decrement();
			timer_timeout.set(next_press_timeout);
			multipartLedRibbon.fill_sold_ext(this->getOffset(), (int) (getLength() / getNumSteps() * (getNumSteps() - counter_progress.value)), CRGB::Teal);
			multipartLedRibbon.show();
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

Atm_morse_reader &Atm_morse_reader::trigger(int event) {
	Machine::trigger(event);
	return *this;
}

/* Optionally override the default state() method
 * Control what the machine returns when another process requests its state
 */

int Atm_morse_reader::state() {
	return Machine::state();
}

/* Nothing customizable below this line                          
 ************************************************************************************************
*/

/* Public event methods
 *
 */

Atm_morse_reader &Atm_morse_reader::short_press() {
	trigger(EVT_SHORT_PRESS);
	return *this;
}

Atm_morse_reader &Atm_morse_reader::long_press() {
	trigger(EVT_LONG_PRESS);
	return *this;
}

/* State trace method
 * Sets the symbol table and the default logging method for serial monitoring
 */

Atm_morse_reader &Atm_morse_reader::trace(Stream &stream) {
	Machine::setTrace(&stream, atm_serial_debug::trace,
	                  "MORSE_READER\0EVT_TIMEOUT\0EVT_SHORT_PRESS\0EVT_LONG_PRESS\0ELSE\0IDLE\0S0\0S1\0S2\0S3\0S4\0S5\0S6\0S7\0S8\0S9\0FINISHED");
	return *this;
}




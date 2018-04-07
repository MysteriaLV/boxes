#include "Atm_main_sequence.h"


Atm_button button1, button2, button3, button4, button5, button6, button7, button8;
Atm_led led1, led2, led3, led4, led5, led6, led7, led8;
Atm_led ufo1, ufo2, ufo3, ufo4, ufo5, ufo6, ufo7, ufo8;
Atm_led door1, door2, door3, door4, door5, door6, door7, door8;
Atm_main_sequence main_sequence;

/* Add optional parameters for the state machine to begin()
 * Add extra initialization code
 */

Atm_main_sequence &Atm_main_sequence::begin() {
// clang-format off
    const static state_t state_table[] PROGMEM = {
            /*                                 ON_ENTER  ON_LOOP  ON_EXIT        EVT_SOLVED  ELSE */
            /*    Q1_ONE_BUTTON */    ENT_Q1_ONE_BUTTON,      -1,      -1,   Q2_TWO_BUTTONS,   -1,
            /*   Q2_TWO_BUTTONS */   ENT_Q2_TWO_BUTTONS,      -1,      -1, Q3_THREE_BUTTONS,   -1,
            /* Q3_THREE_BUTTONS */ ENT_Q3_THREE_BUTTONS,      -1,      -1,  Q4_SINGLE_MORSE,   -1,
            /*  Q4_SINGLE_MORSE */  ENT_Q4_SINGLE_MORSE,      -1,      -1,   Q5_MULTI_MORSE,   -1,
            /*   Q5_MULTI_MORSE */   ENT_Q5_MULTI_MORSE,      -1,      -1,   Q6_WHAC_A_MOLE,   -1,
            /*  Q6_WHAC_A_MOLE  */  ENT_Q6_WHAC_A_MOLE,       -1,      -1,   Q7_MULTI_SNAKE,   -1,
            /*   Q7_MULTI_SNAKE */   ENT_Q7_MULTI_SNAKE,      -1,      -1,         COMPLETE,   -1,
            /*         COMPLETE */         ENT_COMPLETE,      -1,      -1,               -1,   -1,
    };
// clang-format on
    Machine::begin(state_table, ELSE);

	trace(Serial);
	return *this;
}

/* Add C++ code for each internally handled event (input) 
 * The code must return 1 to trigger the event
 */

int Atm_main_sequence::event(int id) {
	return 0;
}

/* Add C++ code for each action
 * This generates the 'output' for the state machine
 */

void Atm_main_sequence::action(int id) {
	switch (id) {
		case ENT_Q1_ONE_BUTTON:
			q1OneButton.begin();
			led1.on();
//			ufo1.on();
			return;
		case ENT_Q2_TWO_BUTTONS:
			q1OneButton.sleep(ATM_SLEEP_FLAG);
			door2.off();
			led2.on();
//			ufo2.on();
			q2TwoButtons.begin();
			return;
		case ENT_Q3_THREE_BUTTONS:
			q2TwoButtons.sleep(ATM_SLEEP_FLAG);
			door3.off();
			led3.on();
//			ufo3.on();
			q3ThreeButtons.begin();
			return;
		case ENT_Q4_SINGLE_MORSE:
			q3ThreeButtons.sleep(ATM_SLEEP_FLAG);
			led1.off();
			ufo1.off();
			led2.off();
			ufo2.off();
			led3.off();
			ufo3.off();
			ufo4.on();
			door4.off();
			q4SingleMorseReader.begin();
			return;
		case ENT_Q5_MULTI_MORSE:
			q4SingleMorseReader.sleep(ATM_SLEEP_FLAG);
			led4.off();
			ufo4.off();
			ufo5.on();
			door5.off();
			q5multiMorseReader.begin();
			return;
		case ENT_Q6_WHAC_A_MOLE:
			q5multiMorseReader.sleep(ATM_SLEEP_FLAG);
            ufo5.off();
            door6.off();
            ufo6.on();
			q6WhacAMole.begin();
			return;
		case ENT_Q7_MULTI_SNAKE:
			q6WhacAMole.sleep(ATM_SLEEP_FLAG);
			door7.off();
			q7RunningLight.begin();
			return;
		case ENT_COMPLETE:
			q7RunningLight.sleep(ATM_SLEEP_FLAG);
			door8.off();
			led1.off();
			ufo1.off();
			led2.off();
			ufo2.off();
			led3.off();
			ufo3.off();
			led4.off();
			ufo4.off();
			led5.off();
			ufo5.off();
			led6.off();
			ufo6.off();
			led7.off();
			ufo7.off();
			led8.off();
			ufo8.off();
			return;
	}
}

/* Optionally override the default trigger() method
 * Control how your machine processes triggers
 */

Atm_main_sequence &Atm_main_sequence::trigger(int event) {
	Machine::trigger(event);
	return *this;
}

/* Optionally override the default state() method
 * Control what the machine returns when another process requests its state
 */

int Atm_main_sequence::state() {
	return Machine::state();
}

/* Nothing customizable below this line                          
 ************************************************************************************************
*/

/* Public event methods
 *
 */

Atm_main_sequence &Atm_main_sequence::solved() {
	trigger(EVT_SOLVED);
	return *this;
}

/* State trace method
 * Sets the symbol table and the default logging method for serial monitoring
 */

Atm_main_sequence &Atm_main_sequence::trace(Stream &stream) {
	Machine::setTrace(&stream, atm_serial_debug::trace,
	                  "MAIN_SEQUENCE\0EVT_SOLVED\0ELSE\0Q1_ONE_BUTTON\0Q2_TWO_BUTTONS\0Q3_THREE_BUTTONS\0Q4_SINGLE_MORSE\0Q5_MULTI_MORSE\0Q6_SINGLE_SNAKE\0Q7_MULTI_SNAKE\0COMPLETE");
	return *this;
}




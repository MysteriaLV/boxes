#include "Atm_main_sequence.h"

Atm_button button1;
Atm_q1_one_button q1OneButton;
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
            /*   Q5_MULTI_MORSE */   ENT_Q5_MULTI_MORSE,      -1,      -1,  Q6_SINGLE_SNAKE,   -1,
            /*  Q6_SINGLE_SNAKE */  ENT_Q6_SINGLE_SNAKE,      -1,      -1,   Q7_MULTI_SNAKE,   -1,
            /*   Q7_MULTI_SNAKE */   ENT_Q7_MULTI_SNAKE,      -1,      -1,         COMPLETE,   -1,
            /*         COMPLETE */         ENT_COMPLETE,      -1,      -1,               -1,   -1,
    };
    // clang-format on
    Machine::begin(state_table, ELSE);
    q1OneButton.begin();


    return *this;
}

/* Add C++ code for each internally handled event (input) 
 * The code must return 1 to trigger the event
 */

int Atm_main_sequence::event(int id) {
    switch (id) {
    }
    return 0;
}

/* Add C++ code for each action
 * This generates the 'output' for the state machine
 */

void Atm_main_sequence::action(int id) {
    switch (id) {
        case ENT_Q1_ONE_BUTTON:
            return;
        case ENT_Q2_TWO_BUTTONS:
            return;
        case ENT_Q3_THREE_BUTTONS:
            return;
        case ENT_Q4_SINGLE_MORSE:
            return;
        case ENT_Q5_MULTI_MORSE:
            return;
        case ENT_Q6_SINGLE_SNAKE:
            return;
        case ENT_Q7_MULTI_SNAKE:
            return;
        case ENT_COMPLETE:
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

int Atm_main_sequence::state(void) {
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



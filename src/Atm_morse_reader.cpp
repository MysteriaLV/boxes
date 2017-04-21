#include "Atm_morse_reader.h"

/* Add optional parameters for the state machine to begin()
 * Add extra initialization code
 */

Atm_morse_reader& Atm_morse_reader::begin() {
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
  Machine::begin( state_table, ELSE );
  return *this;          
}

/* Add C++ code for each internally handled event (input) 
 * The code must return 1 to trigger the event
 */

int Atm_morse_reader::event( int id ) {
  switch ( id ) {
    case EVT_TIMEOUT:
      return 0;
  }
  return 0;
}

/* Add C++ code for each action
 * This generates the 'output' for the state machine
 */

void Atm_morse_reader::action( int id ) {
  switch ( id ) {
    case ENT_IDLE:
      return;
    case EXT_IDLE:
      return;
    case ENT_S0:
      return;
    case ENT_S1:
      return;
    case ENT_S2:
      return;
    case ENT_S3:
      return;
    case ENT_S4:
      return;
    case ENT_S5:
      return;
    case ENT_S6:
      return;
    case ENT_S7:
      return;
    case ENT_S8:
      return;
    case ENT_S9:
      return;
    case ENT_FINISHED:
      return;
  }
}

/* Optionally override the default trigger() method
 * Control how your machine processes triggers
 */

Atm_morse_reader& Atm_morse_reader::trigger( int event ) {
  Machine::trigger( event );
  return *this;
}

/* Optionally override the default state() method
 * Control what the machine returns when another process requests its state
 */

int Atm_morse_reader::state( void ) {
  return Machine::state();
}

/* Nothing customizable below this line                          
 ************************************************************************************************
*/

/* Public event methods
 *
 */

Atm_morse_reader& Atm_morse_reader::short_press() {
  trigger( EVT_SHORT_PRESS );
  return *this;
}

Atm_morse_reader& Atm_morse_reader::long_press() {
  trigger( EVT_LONG_PRESS );
  return *this;
}

/* State trace method
 * Sets the symbol table and the default logging method for serial monitoring
 */

Atm_morse_reader& Atm_morse_reader::trace( Stream & stream ) {
  Machine::setTrace( &stream, atm_serial_debug::trace,
    "MORSE_READER\0EVT_TIMEOUT\0EVT_SHORT_PRESS\0EVT_LONG_PRESS\0ELSE\0IDLE\0S0\0S1\0S2\0S3\0S4\0S5\0S6\0S7\0S8\0S9\0FINISHED" );
  return *this;
}




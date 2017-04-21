#include "Atm_q3_three_buttons.h"
#include "Atm_main_sequence.h"

Atm_controller ctrl;
Atm_q3_three_buttons q3ThreeButtons;

Machine &Atm_q3_three_buttons::begin() {
    // clang-format off
    const static state_t state_table[] PROGMEM = {
            /*                           ON_ENTER  ON_LOOP  ON_EXIT  EVT_COUNTDOWN_ZERO  EVT_TIMER_TICK  EVT_MAKE_PROGRESS  EVT_WRONG_MOVE         ELSE */
            /*          IDLE */          ENT_IDLE,      -1,      -1,                 -1,             -1,     INIT_PROGRESS,             -1,          -1,
            /* INIT_PROGRESS */ ENT_INIT_PROGRESS,      -1,      -1,                 -1,             -1,                -1,             -1, PROGRESSING,
            /*   PROGRESSING */   ENT_PROGRESSING,      -1,      -1,           FINISHED,    PROGRESSING,                -1,           IDLE,          -1,
            /*      FINISHED */      ENT_FINISHED,      -1,      -1,                 -1,             -1,                -1,             -1,          -1,
    };
    // clang-format on
    Machine::begin(state_table, ELSE);

    counter_progress.set(ATM_COUNTER_OFF);
    timer_repeat.set(ATM_TIMER_OFF);

    ctrl.begin( false )
            .IF( button1 ).AND( button2 ).AND( button3 )
            .onChange( true, *this, EVT_MAKE_PROGRESS )
            .onChange( false, *this, EVT_WRONG_MOVE );

    //trace(Serial);
    return *this;
}

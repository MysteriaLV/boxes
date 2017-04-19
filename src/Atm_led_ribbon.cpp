#include "Atm_led_ribbon.h"

Atm_led_ribbon &Atm_led_ribbon::begin(int attached_pin) {
    // clang-format off
    const static state_t state_table[] PROGMEM = {
            /*                           ON_ENTER  ON_LOOP  ON_EXIT  EVT_COUNTDOWN_ZERO  EVT_TIMER_TICK  EVT_MAKE_PROGRESS  EVT_WRONG_MOVE         ELSE */
            /*          IDLE */          ENT_IDLE, -1, -1, -1, -1, INIT_PROGRESS, -1, -1,
            /* INIT_PROGRESS */ ENT_INIT_PROGRESS, -1, -1, -1, -1, -1, -1, PROGRESSING,
            /*   PROGRESSING */   ENT_PROGRESSING, -1, -1, FINISHED, PROGRESSING, -1, IDLE, -1,
            /*      FINISHED */      ENT_FINISHED, -1, -1, -1, -1, -1, -1, -1,
    };
    // clang-format on
    Machine::begin(state_table, ELSE);

//    FastLED.addLeds<NEOPIXEL, attached_pin>(leds, LENGTH);
    FastLED.addLeds<NEOPIXEL, 13>(leds, LENGTH);
    FastLED.setBrightness(1);

    counter_progress.set(ATM_COUNTER_OFF);
    timer_repeat.set(ATM_TIMER_OFF);

    return *this;
}

/* Add C++ code for each internally handled event (input)
 * The code must return 1 to trigger the event
 */

int Atm_led_ribbon::event(int id) {
    switch (id) {
        case EVT_TIMER_TICK:
            return timer_repeat.expired(this);
        case EVT_COUNTDOWN_ZERO:
            return counter_progress.expired();
    }
    return 0;
}

/* Add C++ code for each action
 * This generates the 'output' for the state machine
 *
 * Available connectors:
 *   push( connectors, ON_FINISHED, 0, <v>, <up> );
 */

void Atm_led_ribbon::action(int id) {
    switch (id) {
        case ENT_IDLE:
            timer_repeat.set(ATM_TIMER_OFF);
            counter_progress.set(LENGTH);

            fill_solid(leds, LENGTH /*number of leds*/, CRGB::Black);
            FastLED.show();
            return;
        case ENT_INIT_PROGRESS:
            timer_repeat.set(50);
            counter_progress.set(LENGTH);
            return;
        case ENT_PROGRESSING:
            counter_progress.decrement();
            fill_solid(leds, LENGTH - counter_progress.value /*number of leds*/, CRGB::Teal);
            FastLED.show();
            return;
        case ENT_FINISHED:
            counter_progress.set(ATM_COUNTER_OFF);
            fill_solid(leds, LENGTH /*number of leds*/, CRGB::MediumSeaGreen);
            FastLED.show();
            return;
    }
}

/* Optionally override the default trigger() method
 * Control how your machine processes triggers
 */

Atm_led_ribbon &Atm_led_ribbon::trigger(int event) {
    Machine::trigger(event);
    return *this;
}

/* Optionally override the default state() method
 * Control what the machine returns when another process requests its state
 */

int Atm_led_ribbon::state(void) {
    return Machine::state();
}

/* Nothing customizable below this line
 ************************************************************************************************
*/

/* Public event methods
 *
 */

Atm_led_ribbon &Atm_led_ribbon::make_progress() {
    trigger(EVT_MAKE_PROGRESS);
    return *this;
}

Atm_led_ribbon &Atm_led_ribbon::wrong_move() {
    trigger(EVT_WRONG_MOVE);
    return *this;
}

/*
 * onFinished() push connector variants ( slots 1, autostore 0, broadcast 0 )
 */

Atm_led_ribbon &Atm_led_ribbon::onFinished(Machine &machine, int event) {
    onPush(connectors, ON_FINISHED, 0, 1, 1, machine, event);
    return *this;
}

Atm_led_ribbon &Atm_led_ribbon::onFinished(atm_cb_push_t callback, int idx) {
    onPush(connectors, ON_FINISHED, 0, 1, 1, callback, idx);
    return *this;
}

/* State trace method
 * Sets the symbol table and the default logging method for serial monitoring
 */

Atm_led_ribbon &Atm_led_ribbon::trace(Stream &stream) {
    Machine::setTrace(&stream, atm_serial_debug::trace,
                      "LED_RIBBON\0EVT_COUNTDOWN_ZERO\0EVT_TIMER_TICK\0EVT_MAKE_PROGRESS\0EVT_WRONG_MOVE\0ELSE\0IDLE\0INIT_PROGRESS\0PROGRESSING\0FINISHED");
    return *this;
}

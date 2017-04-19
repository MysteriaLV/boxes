#pragma once

#include <Automaton.h>

#include "FastLED.h"

#define NUM_LEDS 144*4


class Atm_led_ribbon : public Machine {

public:
    enum {
        IDLE, INIT_PROGRESS, PROGRESSING, FINISHED
    }; // STATES
    enum {
        EVT_COUNTDOWN_ZERO, EVT_TIMER_TICK, EVT_MAKE_PROGRESS, EVT_WRONG_MOVE, ELSE
    }; // EVENTS
    Atm_led_ribbon(void) : Machine() {};

    Atm_led_ribbon &begin(int pin);

    Atm_led_ribbon &trace(Stream &stream);

    Atm_led_ribbon &trigger(int event);

    int state(void);

    Atm_led_ribbon &onFinished(Machine &machine, int event = 0);

    Atm_led_ribbon &onFinished(atm_cb_push_t callback, int idx = 0);

    Atm_led_ribbon &make_progress(void);

    Atm_led_ribbon &wrong_move(void);

private:
    enum {
        ENT_IDLE, ENT_INIT_PROGRESS, ENT_PROGRESSING, ENT_FINISHED
    }; // ACTIONS
    enum {
        ON_FINISHED, CONN_MAX
    }; // CONNECTORS
    atm_connector connectors[CONN_MAX];

    int event(int id);

    void action(int id);

    static const int LENGTH = 50;
    CRGB leds[LENGTH];

    atm_timer_millis timer_repeat;
    atm_counter counter_progress;
};

/*
Automaton::ATML::begin - Automaton Markup Language

<?xml version="1.0" encoding="UTF-8"?>
<machines>
  <machine name="Atm_led_ribbon">
    <states>
      <IDLE index="0" on_enter="ENT_IDLE">
        <EVT_MAKE_PROGRESS>INIT_PROGRESS</EVT_MAKE_PROGRESS>
      </IDLE>
      <INIT_PROGRESS index="1" on_enter="ENT_INIT_PROGRESS">
        <ELSE>PROGRESSING</ELSE>
      </INIT_PROGRESS>
      <PROGRESSING index="2" on_enter="ENT_PROGRESSING">
        <EVT_COUNTDOWN_ZERO>FINISHED</EVT_COUNTDOWN_ZERO>
        <EVT_TIMER_TICK>PROGRESSING</EVT_TIMER_TICK>
        <EVT_WRONG_MOVE>IDLE</EVT_WRONG_MOVE>
      </PROGRESSING>
      <FINISHED index="3" on_enter="ENT_FINISHED">
      </FINISHED>
    </states>
    <events>
      <EVT_COUNTDOWN_ZERO index="0" access="PRIVATE"/>
      <EVT_TIMER_TICK index="1" access="PRIVATE"/>
      <EVT_MAKE_PROGRESS index="2" access="PUBLIC"/>
      <EVT_WRONG_MOVE index="3" access="PUBLIC"/>
    </events>
    <connectors>
      <FINISHED autostore="0" broadcast="0" dir="PUSH" slots="1"/>
    </connectors>
    <methods>
    </methods>
  </machine>
</machines>

Automaton::ATML::end
*/
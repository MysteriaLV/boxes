#pragma once

#include <Automaton.h>
#include "ribbon_dimensions.h"

class Atm_running_light: public Machine {

 public:
  enum { INIT, RUNNING, ZONE1, ZONE2, ZONE3, ZONE4, ZONE5, ZONE6, ZONE7, CORRECT, INCORRECT, FINISHED }; // STATES
  enum { EVT_ZONE1, EVT_ZONE2, EVT_ZONE3, EVT_ZONE4, EVT_ZONE5, EVT_ZONE6, EVT_ZONE7, EVT_TIMEOUT, EVT_BTN1_PRESSED, EVT_BTN2_PRESSED, EVT_BTN3_PRESSED, EVT_BTN4_PRESSED, EVT_BTN5_PRESSED, EVT_BTN6_PRESSED, EVT_BTN7_PRESSED, ELSE }; // EVENTS
  Atm_running_light( void ) : Machine() {};
  Atm_running_light& begin( void );
  Atm_running_light& trace( Stream & stream );

  virtual uint16_t getOffset() { return Q1_START; };
  virtual uint16_t getLength() { return Q_LAST_LED; };

  atm_counter tick_reverse_location{};
  atm_counter counter_progress{};

#ifdef MY_EASY_MODE
	uint32_t next_press_timeout = 10000;
	uint32_t next_tick_timeout = 10;
#else
	uint32_t next_press_timeout = 1000;
	uint32_t next_tick_timeout = 50;
#endif

	uint32_t next_press_timeout_per_step = 100;
	atm_timer_millis timer_timeout{};

private:
  enum { ENT_INIT, ENT_RUNNING, ENT_ZONE1, EXT_ZONE1, ENT_ZONE2, EXT_ZONE2, ENT_ZONE3, EXT_ZONE3, ENT_ZONE4, EXT_ZONE4, ENT_ZONE5, EXT_ZONE5, ENT_ZONE6, EXT_ZONE6, ENT_ZONE7, EXT_ZONE7, ENT_CORRECT, ENT_INCORRECT, ENT_FINISHED }; // ACTIONS
  int event( int id );
  void action( int id );

    Atm_led *currentLed;
    Atm_led *currentUfo;

    uint16_t calculatePosition();
};

/*
Automaton::ATML::begin - Automaton Markup Language

<?xml version="1.0" encoding="UTF-8"?>
<machines>
  <machine name="Atm_running_light">
    <states>
      <INIT index="0" on_enter="ENT_INIT">
        <ELSE>RUNNING</ELSE>
      </INIT>
      <RUNNING index="1" on_enter="ENT_RUNNING">
        <EVT_ZONE1>ZONE1</EVT_ZONE1>
        <EVT_ZONE2>ZONE2</EVT_ZONE2>
        <EVT_ZONE3>ZONE3</EVT_ZONE3>
        <EVT_ZONE4>ZONE4</EVT_ZONE4>
        <EVT_ZONE5>ZONE5</EVT_ZONE5>
        <EVT_ZONE6>ZONE6</EVT_ZONE6>
        <EVT_ZONE7>ZONE7</EVT_ZONE7>
        <EVT_TIMEOUT>RUNNING</EVT_TIMEOUT>
        <EVT_BTN1_PRESSED>INCORRECT</EVT_BTN1_PRESSED>
        <EVT_BTN2_PRESSED>INCORRECT</EVT_BTN2_PRESSED>
        <EVT_BTN3_PRESSED>INCORRECT</EVT_BTN3_PRESSED>
        <EVT_BTN4_PRESSED>INCORRECT</EVT_BTN4_PRESSED>
        <EVT_BTN5_PRESSED>INCORRECT</EVT_BTN5_PRESSED>
        <EVT_BTN6_PRESSED>INCORRECT</EVT_BTN6_PRESSED>
        <EVT_BTN7_PRESSED>INCORRECT</EVT_BTN7_PRESSED>
      </RUNNING>
      <ZONE1 index="2" on_enter="ENT_ZONE1" on_exit="EXT_ZONE1">
        <EVT_TIMEOUT>INCORRECT</EVT_TIMEOUT>
        <EVT_BTN1_PRESSED>CORRECT</EVT_BTN1_PRESSED>
        <EVT_BTN2_PRESSED>INCORRECT</EVT_BTN2_PRESSED>
        <EVT_BTN3_PRESSED>INCORRECT</EVT_BTN3_PRESSED>
        <EVT_BTN4_PRESSED>INCORRECT</EVT_BTN4_PRESSED>
        <EVT_BTN5_PRESSED>INCORRECT</EVT_BTN5_PRESSED>
        <EVT_BTN6_PRESSED>INCORRECT</EVT_BTN6_PRESSED>
        <EVT_BTN7_PRESSED>INCORRECT</EVT_BTN7_PRESSED>
      </ZONE1>
      <ZONE2 index="3" on_enter="ENT_ZONE2" on_exit="EXT_ZONE2">
        <EVT_TIMEOUT>INCORRECT</EVT_TIMEOUT>
        <EVT_BTN1_PRESSED>INCORRECT</EVT_BTN1_PRESSED>
        <EVT_BTN2_PRESSED>CORRECT</EVT_BTN2_PRESSED>
        <EVT_BTN3_PRESSED>INCORRECT</EVT_BTN3_PRESSED>
        <EVT_BTN4_PRESSED>INCORRECT</EVT_BTN4_PRESSED>
        <EVT_BTN5_PRESSED>INCORRECT</EVT_BTN5_PRESSED>
        <EVT_BTN6_PRESSED>INCORRECT</EVT_BTN6_PRESSED>
        <EVT_BTN7_PRESSED>INCORRECT</EVT_BTN7_PRESSED>
      </ZONE2>
      <ZONE3 index="4" on_enter="ENT_ZONE3" on_exit="EXT_ZONE3">
        <EVT_TIMEOUT>INCORRECT</EVT_TIMEOUT>
        <EVT_BTN1_PRESSED>INCORRECT</EVT_BTN1_PRESSED>
        <EVT_BTN2_PRESSED>INCORRECT</EVT_BTN2_PRESSED>
        <EVT_BTN3_PRESSED>CORRECT</EVT_BTN3_PRESSED>
        <EVT_BTN4_PRESSED>INCORRECT</EVT_BTN4_PRESSED>
        <EVT_BTN5_PRESSED>INCORRECT</EVT_BTN5_PRESSED>
        <EVT_BTN6_PRESSED>INCORRECT</EVT_BTN6_PRESSED>
        <EVT_BTN7_PRESSED>INCORRECT</EVT_BTN7_PRESSED>
      </ZONE3>
      <ZONE4 index="5" on_enter="ENT_ZONE4" on_exit="EXT_ZONE4">
        <EVT_TIMEOUT>INCORRECT</EVT_TIMEOUT>
        <EVT_BTN1_PRESSED>INCORRECT</EVT_BTN1_PRESSED>
        <EVT_BTN2_PRESSED>INCORRECT</EVT_BTN2_PRESSED>
        <EVT_BTN3_PRESSED>INCORRECT</EVT_BTN3_PRESSED>
        <EVT_BTN4_PRESSED>CORRECT</EVT_BTN4_PRESSED>
        <EVT_BTN5_PRESSED>INCORRECT</EVT_BTN5_PRESSED>
        <EVT_BTN6_PRESSED>INCORRECT</EVT_BTN6_PRESSED>
        <EVT_BTN7_PRESSED>INCORRECT</EVT_BTN7_PRESSED>
      </ZONE4>
      <ZONE5 index="6" on_enter="ENT_ZONE5" on_exit="EXT_ZONE5">
        <EVT_TIMEOUT>INCORRECT</EVT_TIMEOUT>
        <EVT_BTN1_PRESSED>INCORRECT</EVT_BTN1_PRESSED>
        <EVT_BTN2_PRESSED>INCORRECT</EVT_BTN2_PRESSED>
        <EVT_BTN3_PRESSED>INCORRECT</EVT_BTN3_PRESSED>
        <EVT_BTN4_PRESSED>INCORRECT</EVT_BTN4_PRESSED>
        <EVT_BTN5_PRESSED>CORRECT</EVT_BTN5_PRESSED>
        <EVT_BTN6_PRESSED>INCORRECT</EVT_BTN6_PRESSED>
        <EVT_BTN7_PRESSED>INCORRECT</EVT_BTN7_PRESSED>
      </ZONE5>
      <ZONE6 index="7" on_enter="ENT_ZONE6" on_exit="EXT_ZONE6">
        <EVT_TIMEOUT>INCORRECT</EVT_TIMEOUT>
        <EVT_BTN1_PRESSED>INCORRECT</EVT_BTN1_PRESSED>
        <EVT_BTN2_PRESSED>INCORRECT</EVT_BTN2_PRESSED>
        <EVT_BTN3_PRESSED>INCORRECT</EVT_BTN3_PRESSED>
        <EVT_BTN4_PRESSED>INCORRECT</EVT_BTN4_PRESSED>
        <EVT_BTN5_PRESSED>INCORRECT</EVT_BTN5_PRESSED>
        <EVT_BTN6_PRESSED>CORRECT</EVT_BTN6_PRESSED>
        <EVT_BTN7_PRESSED>INCORRECT</EVT_BTN7_PRESSED>
      </ZONE6>
      <ZONE7 index="8" on_enter="ENT_ZONE7" on_exit="EXT_ZONE7">
        <EVT_TIMEOUT>INIT</EVT_TIMEOUT>
        <EVT_BTN1_PRESSED>INIT</EVT_BTN1_PRESSED>
        <EVT_BTN2_PRESSED>INIT</EVT_BTN2_PRESSED>
        <EVT_BTN3_PRESSED>INIT</EVT_BTN3_PRESSED>
        <EVT_BTN4_PRESSED>INIT</EVT_BTN4_PRESSED>
        <EVT_BTN5_PRESSED>INIT</EVT_BTN5_PRESSED>
        <EVT_BTN6_PRESSED>INIT</EVT_BTN6_PRESSED>
        <EVT_BTN7_PRESSED>CORRECT</EVT_BTN7_PRESSED>
      </ZONE7>
      <CORRECT index="9" on_enter="ENT_CORRECT">
        <ELSE>RUNNING</ELSE>
      </CORRECT>
      <INCORRECT index="10" on_enter="ENT_INCORRECT">
        <ELSE>RUNNING</ELSE>
      </INCORRECT>
      <FINISHED index="11" sleep="1" on_enter="ENT_FINISHED">
      </FINISHED>
    </states>
    <events>
      <EVT_ZONE1 index="0" access="PRIVATE"/>
      <EVT_ZONE2 index="1" access="PRIVATE"/>
      <EVT_ZONE3 index="2" access="PRIVATE"/>
      <EVT_ZONE4 index="3" access="PRIVATE"/>
      <EVT_ZONE5 index="4" access="PRIVATE"/>
      <EVT_ZONE6 index="5" access="PRIVATE"/>
      <EVT_ZONE7 index="6" access="PRIVATE"/>
      <EVT_TIMEOUT index="7" access="PRIVATE"/>
      <EVT_BTN1_PRESSED index="8" access="PRIVATE"/>
      <EVT_BTN2_PRESSED index="9" access="PRIVATE"/>
      <EVT_BTN3_PRESSED index="10" access="PRIVATE"/>
      <EVT_BTN4_PRESSED index="11" access="PRIVATE"/>
      <EVT_BTN5_PRESSED index="12" access="PRIVATE"/>
      <EVT_BTN6_PRESSED index="13" access="PRIVATE"/>
      <EVT_BTN7_PRESSED index="14" access="PRIVATE"/>
    </events>
    <connectors>
    </connectors>
    <methods>
    </methods>
  </machine>
</machines>

Automaton::ATML::end
*/
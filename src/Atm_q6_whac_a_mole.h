#pragma once

#include <Automaton.h>
#include "ribbon_dimensions.h"

class Atm_whac_a_mole: public Machine {

public:
	enum { BTN1, BTN2, BTN3, BTN4, BTN5, BTN6, CORRECT, INCORRECT, FINISHED }; // STATES
	enum { EVT_TIMEOUT, EVT_BTN1_PRESSED, EVT_BTN2_PRESSED, EVT_BTN3_PRESSED, EVT_BTN4_PRESSED, EVT_BTN5_PRESSED, EVT_BTN6_PRESSED, ELSE }; // EVENTS
	Atm_whac_a_mole( void ) : Machine() {};
	Atm_whac_a_mole& begin( void );
	Atm_whac_a_mole& trace( Stream & stream );
	Atm_whac_a_mole& trigger( int event );
	int state( void );

	virtual uint16_t getOffset() { return Q6_START; };
	virtual uint16_t getLength() { return (Q6_START - Q5_START) / 2; };

	atm_counter counter_progress{};

#ifdef MY_EASY_MODE
	virtual uint16_t getNumSteps() { return 3; };
	uint32_t next_press_timeout = 10000;
#else
	virtual uint16_t getNumSteps() { return 8; };
	uint32_t next_press_timeout = 800;
#endif

	uint32_t next_press_timeout_per_step = 100;
	atm_timer_millis timer_timeout{};
private:
	enum { ENT_BTN1, EXT_BTN1, ENT_BTN2, EXT_BTN2, ENT_BTN3, EXT_BTN3, ENT_BTN4, EXT_BTN4, ENT_BTN5, EXT_BTN5, ENT_BTN6, EXT_BTN6, ENT_CORRECT, ENT_INCORRECT, ENT_FINISHED }; // ACTIONS
	int event( int id );
	void action( int id );

	void next_mole();
	int randomize_mole();
	int current_mole = -1;
};

/*
Automaton::ATML::begin - Automaton Markup Language

<?xml version="1.0" encoding="UTF-8"?>
<machines>
  <machine name="Atm_whac_a_mole">
    <states>
      <BTN1 index="0" on_enter="ENT_BTN1" on_exit="EXT_BTN1">
        <EVT_TIMEOUT>INCORRECT</EVT_TIMEOUT>
        <EVT_BTN1_PRESSED>CORRECT</EVT_BTN1_PRESSED>
        <EVT_BTN2_PRESSED>INCORRECT</EVT_BTN2_PRESSED>
        <EVT_BTN3_PRESSED>INCORRECT</EVT_BTN3_PRESSED>
        <EVT_BTN4_PRESSED>INCORRECT</EVT_BTN4_PRESSED>
        <EVT_BTN5_PRESSED>INCORRECT</EVT_BTN5_PRESSED>
        <EVT_BTN6_PRESSED>INCORRECT</EVT_BTN6_PRESSED>
      </BTN1>
      <BTN2 index="1" on_enter="ENT_BTN2" on_exit="EXT_BTN2">
        <EVT_TIMEOUT>INCORRECT</EVT_TIMEOUT>
        <EVT_BTN1_PRESSED>INCORRECT</EVT_BTN1_PRESSED>
        <EVT_BTN2_PRESSED>CORRECT</EVT_BTN2_PRESSED>
        <EVT_BTN3_PRESSED>INCORRECT</EVT_BTN3_PRESSED>
        <EVT_BTN4_PRESSED>INCORRECT</EVT_BTN4_PRESSED>
        <EVT_BTN5_PRESSED>INCORRECT</EVT_BTN5_PRESSED>
        <EVT_BTN6_PRESSED>INCORRECT</EVT_BTN6_PRESSED>
      </BTN2>
      <BTN3 index="2" on_enter="ENT_BTN3" on_exit="EXT_BTN3">
        <EVT_TIMEOUT>INCORRECT</EVT_TIMEOUT>
        <EVT_BTN1_PRESSED>INCORRECT</EVT_BTN1_PRESSED>
        <EVT_BTN2_PRESSED>INCORRECT</EVT_BTN2_PRESSED>
        <EVT_BTN3_PRESSED>CORRECT</EVT_BTN3_PRESSED>
        <EVT_BTN4_PRESSED>INCORRECT</EVT_BTN4_PRESSED>
        <EVT_BTN5_PRESSED>INCORRECT</EVT_BTN5_PRESSED>
        <EVT_BTN6_PRESSED>INCORRECT</EVT_BTN6_PRESSED>
      </BTN3>
      <BTN4 index="3" on_enter="ENT_BTN4" on_exit="EXT_BTN4">
        <EVT_TIMEOUT>INCORRECT</EVT_TIMEOUT>
        <EVT_BTN1_PRESSED>INCORRECT</EVT_BTN1_PRESSED>
        <EVT_BTN2_PRESSED>INCORRECT</EVT_BTN2_PRESSED>
        <EVT_BTN3_PRESSED>INCORRECT</EVT_BTN3_PRESSED>
        <EVT_BTN4_PRESSED>CORRECT</EVT_BTN4_PRESSED>
        <EVT_BTN5_PRESSED>INCORRECT</EVT_BTN5_PRESSED>
        <EVT_BTN6_PRESSED>INCORRECT</EVT_BTN6_PRESSED>
      </BTN4>
      <BTN5 index="4" on_enter="ENT_BTN5" on_exit="EXT_BTN5">
        <EVT_TIMEOUT>INCORRECT</EVT_TIMEOUT>
        <EVT_BTN1_PRESSED>INCORRECT</EVT_BTN1_PRESSED>
        <EVT_BTN2_PRESSED>INCORRECT</EVT_BTN2_PRESSED>
        <EVT_BTN3_PRESSED>INCORRECT</EVT_BTN3_PRESSED>
        <EVT_BTN4_PRESSED>INCORRECT</EVT_BTN4_PRESSED>
        <EVT_BTN5_PRESSED>CORRECT</EVT_BTN5_PRESSED>
        <EVT_BTN6_PRESSED>INCORRECT</EVT_BTN6_PRESSED>
      </BTN5>
      <BTN6 index="5" on_enter="ENT_BTN6" on_exit="EXT_BTN6">
        <EVT_TIMEOUT>INCORRECT</EVT_TIMEOUT>
        <EVT_BTN1_PRESSED>INCORRECT</EVT_BTN1_PRESSED>
        <EVT_BTN2_PRESSED>INCORRECT</EVT_BTN2_PRESSED>
        <EVT_BTN3_PRESSED>INCORRECT</EVT_BTN3_PRESSED>
        <EVT_BTN4_PRESSED>INCORRECT</EVT_BTN4_PRESSED>
        <EVT_BTN5_PRESSED>INCORRECT</EVT_BTN5_PRESSED>
        <EVT_BTN6_PRESSED>CORRECT</EVT_BTN6_PRESSED>
      </BTN6>
      <CORRECT index="6" on_enter="ENT_CORRECT">
      </CORRECT>
      <INCORRECT index="7" on_enter="ENT_INCORRECT">
      </INCORRECT>
      <FINISHED index="8" sleep="1" on_enter="ENT_FINISHED">
      </FINISHED>
    </states>
    <events>
      <EVT_TIMEOUT index="0" access="PRIVATE"/>
      <EVT_BTN1_PRESSED index="1" access="PRIVATE"/>
      <EVT_BTN2_PRESSED index="2" access="PRIVATE"/>
      <EVT_BTN3_PRESSED index="3" access="PRIVATE"/>
      <EVT_BTN4_PRESSED index="4" access="PRIVATE"/>
      <EVT_BTN5_PRESSED index="5" access="PRIVATE"/>
      <EVT_BTN6_PRESSED index="6" access="PRIVATE"/>
    </events>
    <connectors>
    </connectors>
    <methods>
    </methods>
  </machine>
</machines>

Automaton::ATML::end
*/
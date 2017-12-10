#pragma once

#include <Automaton.h>
#include "ribbon_dimensions.h"

class Atm_multi_morse_reader: public Machine {

public:
  enum { IDLE, S0, S1, S2, S3, L1, L2, L3, L4, L5, FINISHED }; // STATES
	enum { EVT_TIMEOUT, EVT_BTN1_PRESSED, EVT_BTN2_PRESSED, EVT_BTN3_PRESSED, EVT_BTN4_PRESSED, EVT_BTN5_PRESSED, ELSE }; // EVENTS
	Atm_multi_morse_reader( void ) : Machine() {};
	Atm_multi_morse_reader& begin( void );
	Atm_multi_morse_reader& trace( Stream & stream );
	Atm_multi_morse_reader& trigger( int event );
	int state( void );

private:
  enum { ENT_IDLE, EXT_IDLE, ENT_S0, ENT_S1, ENT_S2, ENT_S3, ENT_L1, EXT_L1, ENT_L2, EXT_L2, ENT_L3, EXT_L3, ENT_L4, EXT_L4, ENT_L5, EXT_L5, ENT_FINISHED }; // ACTIONS
	int event( int id );
	void action( int id );

	virtual uint16_t getOffset() { return Q5_START; };
	virtual uint16_t getLength() { return (Q6_START - Q5_START) / 2; };

	virtual uint16_t getNumSteps() { return 5; };
	uint32_t next_press_timeout = 3000;

	atm_counter counter_progress{};
	atm_timer_millis timer_timeout{};

};

/*
Automaton::ATML::begin - Automaton Markup Language

<?xml version="1.0" encoding="UTF-8"?>
<machines>
  <machine name="Atm_multi_morse_reader">
    <states>
      <IDLE index="0" on_enter="ENT_IDLE" on_exit="EXT_IDLE">
        <EVT_TIMEOUT>L3</EVT_TIMEOUT>
        <EVT_BTN3_PRESSED>S0</EVT_BTN3_PRESSED>
      </IDLE>
      <S0 index="1" on_enter="ENT_S0">
        <EVT_TIMEOUT>IDLE</EVT_TIMEOUT>
        <EVT_BTN1_PRESSED>IDLE</EVT_BTN1_PRESSED>
        <EVT_BTN2_PRESSED>S1</EVT_BTN2_PRESSED>
        <EVT_BTN3_PRESSED>IDLE</EVT_BTN3_PRESSED>
        <EVT_BTN4_PRESSED>IDLE</EVT_BTN4_PRESSED>
        <EVT_BTN5_PRESSED>IDLE</EVT_BTN5_PRESSED>
      </S0>
      <S1 index="2" on_enter="ENT_S1">
        <EVT_TIMEOUT>IDLE</EVT_TIMEOUT>
        <EVT_BTN1_PRESSED>S2</EVT_BTN1_PRESSED>
        <EVT_BTN2_PRESSED>IDLE</EVT_BTN2_PRESSED>
        <EVT_BTN3_PRESSED>IDLE</EVT_BTN3_PRESSED>
        <EVT_BTN4_PRESSED>IDLE</EVT_BTN4_PRESSED>
        <EVT_BTN5_PRESSED>IDLE</EVT_BTN5_PRESSED>
      </S1>
      <S2 index="3" on_enter="ENT_S2">
        <EVT_TIMEOUT>IDLE</EVT_TIMEOUT>
        <EVT_BTN1_PRESSED>IDLE</EVT_BTN1_PRESSED>
        <EVT_BTN2_PRESSED>IDLE</EVT_BTN2_PRESSED>
        <EVT_BTN3_PRESSED>IDLE</EVT_BTN3_PRESSED>
        <EVT_BTN4_PRESSED>IDLE</EVT_BTN4_PRESSED>
        <EVT_BTN5_PRESSED>S3</EVT_BTN5_PRESSED>
      </S2>
      <S3 index="4" on_enter="ENT_S3">
        <EVT_TIMEOUT>IDLE</EVT_TIMEOUT>
        <EVT_BTN1_PRESSED>IDLE</EVT_BTN1_PRESSED>
        <EVT_BTN2_PRESSED>IDLE</EVT_BTN2_PRESSED>
        <EVT_BTN3_PRESSED>IDLE</EVT_BTN3_PRESSED>
        <EVT_BTN4_PRESSED>FINISHED</EVT_BTN4_PRESSED>
        <EVT_BTN5_PRESSED>IDLE</EVT_BTN5_PRESSED>
      </S3>
      <L1 index="5" on_enter="ENT_L1" on_exit="EXT_L1">
        <EVT_TIMEOUT>L5</EVT_TIMEOUT>
        <EVT_BTN3_PRESSED>S0</EVT_BTN3_PRESSED>
      </L1>
      <L2 index="6" on_enter="ENT_L2" on_exit="EXT_L2">
        <EVT_TIMEOUT>L1</EVT_TIMEOUT>
        <EVT_BTN3_PRESSED>S0</EVT_BTN3_PRESSED>
      </L2>
      <L3 index="7" on_enter="ENT_L3" on_exit="EXT_L3">
        <EVT_TIMEOUT>L2</EVT_TIMEOUT>
        <EVT_BTN3_PRESSED>S0</EVT_BTN3_PRESSED>
      </L3>
      <L4 index="8" on_enter="ENT_L4" on_exit="EXT_L4">
        <EVT_TIMEOUT>IDLE</EVT_TIMEOUT>
        <EVT_BTN3_PRESSED>S0</EVT_BTN3_PRESSED>
      </L4>
      <L5 index="9" on_enter="ENT_L5" on_exit="EXT_L5">
        <EVT_TIMEOUT>L4</EVT_TIMEOUT>
        <EVT_BTN3_PRESSED>S0</EVT_BTN3_PRESSED>
      </L5>
      <FINISHED index="10" sleep="1" on_enter="ENT_FINISHED">
        <EVT_BTN3_PRESSED>S0</EVT_BTN3_PRESSED>
      </FINISHED>
    </states>
    <events>
      <EVT_TIMEOUT index="0" access="PRIVATE"/>
      <EVT_BTN1_PRESSED index="1" access="PRIVATE"/>
      <EVT_BTN2_PRESSED index="2" access="PRIVATE"/>
      <EVT_BTN3_PRESSED index="3" access="PRIVATE"/>
      <EVT_BTN4_PRESSED index="4" access="PRIVATE"/>
      <EVT_BTN5_PRESSED index="5" access="PRIVATE"/>
    </events>
    <connectors>
    </connectors>
    <methods>
    </methods>
  </machine>
</machines>

Automaton::ATML::end
*/

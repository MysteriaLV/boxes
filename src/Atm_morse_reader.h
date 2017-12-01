#pragma once

#include <Automaton.h>

class Atm_morse_reader: public Machine {

 public:
	enum { IDLE, S0, S1, S2, S3, S4, S5, S6, S7, S8, S9, FINISHED }; // STATES
	enum { EVT_TIMEOUT, EVT_SHORT_PRESS, EVT_LONG_PRESS, ELSE }; // EVENTS
	Atm_morse_reader(  ) : Machine() {};
	Atm_morse_reader& begin(  );
	Atm_morse_reader& trace( Stream & stream );
	Atm_morse_reader& trigger( int event ) override;
	int state(  ) override;
	Atm_morse_reader& short_press(  );
	Atm_morse_reader& long_press(  );

 private:
	enum { ENT_IDLE, EXT_IDLE, ENT_S0, ENT_S1, ENT_S2, ENT_S3, ENT_S4, ENT_S5, ENT_S6, ENT_S7, ENT_S8, ENT_S9, ENT_FINISHED }; // ACTIONS
	int event( int id ) override;
	void action( int id ) override;

	virtual int getOffset() { return 128; };
	virtual int getLength() { return 24; };
	virtual uint16_t getNumSteps() { return 9; };

	atm_timer_millis timer_timeout{};
	atm_counter counter_progress{};

	Atm_led dot, dash;
	Atm_timer stepTimer;
	Atm_step step;

	const int pin = 29;		// Led4
	uint32_t dotTime = 100;
	uint32_t dashTime = 500;
	const int waitTime = 200;
	uint32_t longwaitTime = 300;
	const int longerwaitTime = 1000;

	uint32_t next_press_timeout = 3000;
};

/*
Automaton::ATML::begin - Automaton Markup Language

<?xml version="1.0" encoding="UTF-8"?>
<machines>
  <machine name="Atm_morse_reader">
    <states>
      <IDLE index="0" on_enter="ENT_IDLE" on_exit="EXT_IDLE">
        <EVT_SHORT_PRESS>S0</EVT_SHORT_PRESS>
      </IDLE>
      <S0 index="1" on_enter="ENT_S0">
        <EVT_TIMEOUT>IDLE</EVT_TIMEOUT>
        <EVT_SHORT_PRESS>S1</EVT_SHORT_PRESS>
        <EVT_LONG_PRESS>IDLE</EVT_LONG_PRESS>
      </S0>
      <S1 index="2" on_enter="ENT_S1">
        <EVT_TIMEOUT>IDLE</EVT_TIMEOUT>
        <EVT_SHORT_PRESS>S2</EVT_SHORT_PRESS>
        <EVT_LONG_PRESS>IDLE</EVT_LONG_PRESS>
      </S1>
      <S2 index="3" on_enter="ENT_S2">
        <EVT_TIMEOUT>IDLE</EVT_TIMEOUT>
        <EVT_SHORT_PRESS>IDLE</EVT_SHORT_PRESS>
        <EVT_LONG_PRESS>S3</EVT_LONG_PRESS>
      </S2>
      <S3 index="4" on_enter="ENT_S3">
        <EVT_TIMEOUT>IDLE</EVT_TIMEOUT>
        <EVT_SHORT_PRESS>IDLE</EVT_SHORT_PRESS>
        <EVT_LONG_PRESS>S4</EVT_LONG_PRESS>
      </S3>
      <S4 index="5" on_enter="ENT_S4">
        <EVT_TIMEOUT>IDLE</EVT_TIMEOUT>
        <EVT_SHORT_PRESS>IDLE</EVT_SHORT_PRESS>
        <EVT_LONG_PRESS>S5</EVT_LONG_PRESS>
      </S4>
      <S5 index="6" on_enter="ENT_S5">
        <EVT_TIMEOUT>IDLE</EVT_TIMEOUT>
        <EVT_SHORT_PRESS>S6</EVT_SHORT_PRESS>
        <EVT_LONG_PRESS>IDLE</EVT_LONG_PRESS>
      </S5>
      <S6 index="7" on_enter="ENT_S6">
        <EVT_TIMEOUT>IDLE</EVT_TIMEOUT>
        <EVT_SHORT_PRESS>S7</EVT_SHORT_PRESS>
        <EVT_LONG_PRESS>IDLE</EVT_LONG_PRESS>
      </S6>
      <S7 index="8" on_enter="ENT_S7">
        <EVT_TIMEOUT>IDLE</EVT_TIMEOUT>
        <EVT_SHORT_PRESS>FINISHED</EVT_SHORT_PRESS>
        <EVT_LONG_PRESS>IDLE</EVT_LONG_PRESS>
      </S7>
      <S8 index="9" on_enter="ENT_S8">
        <EVT_TIMEOUT>IDLE</EVT_TIMEOUT>
      </S8>
      <S9 index="10" on_enter="ENT_S9">
        <EVT_TIMEOUT>IDLE</EVT_TIMEOUT>
      </S9>
      <FINISHED index="11" on_enter="ENT_FINISHED">
      </FINISHED>
    </states>
    <events>
      <EVT_TIMEOUT index="0" access="PRIVATE"/>
      <EVT_SHORT_PRESS index="1" access="PUBLIC"/>
      <EVT_LONG_PRESS index="2" access="PUBLIC"/>
    </events>
    <connectors>
    </connectors>
    <methods>
    </methods>
  </machine>
</machines>

Automaton::ATML::end
*/


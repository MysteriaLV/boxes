#pragma once

#include <Automaton.h>
#include "Atm_q1_one_button.h"
#include "Atm_q2_two_buttons.h"
#include "Atm_q3_three_buttons.h"
#include "Atm_q4_morse_reader.h"
#include "Atm_q5_multi_morse_reader.h"
#include "Atm_q6_whac_a_mole.h"

class Atm_main_sequence: public Machine {

 public:
  enum { Q1_ONE_BUTTON, Q2_TWO_BUTTONS, Q3_THREE_BUTTONS, Q4_SINGLE_MORSE, Q5_MULTI_MORSE, Q6_WHAC_A_MOLE, Q7_MULTI_SNAKE, COMPLETE }; // STATES
  enum { EVT_SOLVED, ELSE }; // EVENTS
  Atm_main_sequence( void ) : Machine() {};
  Atm_main_sequence& begin( void );
  Atm_main_sequence& trace( Stream & stream );
  Atm_main_sequence& trigger( int event );
  int state( void );
  Atm_main_sequence& solved( void );

 private:
  enum { ENT_Q1_ONE_BUTTON, ENT_Q2_TWO_BUTTONS, ENT_Q3_THREE_BUTTONS, ENT_Q4_SINGLE_MORSE, ENT_Q5_MULTI_MORSE, ENT_Q6_WHAC_A_MOLE, ENT_Q7_MULTI_SNAKE, ENT_COMPLETE }; // ACTIONS
  int event( int id ); 
  void action( int id ); 

};

extern Atm_button button1, button2, button3, button4, button5, button6, button7, button8;
extern Atm_led led1, led2, led3, led4, led5, led6, led7, led8;
extern Atm_led ufo1, ufo2, ufo3, ufo4, ufo5, ufo6, ufo7, ufo8;
extern Atm_led door1, door2, door3, door4, door5, door6, door7, door8;
extern Atm_q1_one_button q1OneButton;
extern Atm_q2_two_buttons q2TwoButtons;
extern Atm_q3_three_buttons q3ThreeButtons;
extern Atm_morse_reader q4SingleMorseReader;
extern Atm_multi_morse_reader q5multiMorseReader;
extern Atm_whac_a_mole q6WhacAMole;
extern Atm_main_sequence main_sequence;

/*
Automaton::ATML::begin - Automaton Markup Language

<?xml version="1.0" encoding="UTF-8"?>
<machines>
  <machine name="Atm_main_sequence">
    <states>
      <Q1_ONE_BUTTON index="0" on_enter="ENT_Q1_ONE_BUTTON">
        <EVT_SOLVED>Q2_TWO_BUTTONS</EVT_SOLVED>
      </Q1_ONE_BUTTON>
      <Q2_TWO_BUTTONS index="1" on_enter="ENT_Q2_TWO_BUTTONS">
        <EVT_SOLVED>Q3_THREE_BUTTONS</EVT_SOLVED>
      </Q2_TWO_BUTTONS>
      <Q3_THREE_BUTTONS index="2" on_enter="ENT_Q3_THREE_BUTTONS">
        <EVT_SOLVED>Q4_SINGLE_MORSE</EVT_SOLVED>
      </Q3_THREE_BUTTONS>
      <Q4_SINGLE_MORSE index="3" on_enter="ENT_Q4_SINGLE_MORSE">
        <EVT_SOLVED>Q5_MULTI_MORSE</EVT_SOLVED>
      </Q4_SINGLE_MORSE>
      <Q5_MULTI_MORSE index="4" on_enter="ENT_Q5_MULTI_MORSE">
        <EVT_SOLVED>Q6_WHAC_A_MOLE</EVT_SOLVED>
      </Q5_MULTI_MORSE>
      <Q6_WHAC_A_MOLE index="5" on_enter="ENT_Q6_WHAC_A_MOLE">
        <EVT_SOLVED>Q7_MULTI_SNAKE</EVT_SOLVED>
      </Q6_WHAC_A_MOLE>
      <Q7_MULTI_SNAKE index="6" on_enter="ENT_Q7_MULTI_SNAKE">
        <EVT_SOLVED>COMPLETE</EVT_SOLVED>
      </Q7_MULTI_SNAKE>
      <COMPLETE index="7" on_enter="ENT_COMPLETE">
      </COMPLETE>
    </states>
    <events>
      <EVT_SOLVED index="0" access="PUBLIC"/>
    </events>
    <connectors>
    </connectors>
    <methods>
    </methods>
  </machine>
</machines>

Automaton::ATML::end
*/


#pragma once

#include "Atm_q1_one_button.h"

class Atm_q2_two_buttons : public Atm_q1_one_button {
public:
	Machine &begin();

protected:
	virtual int getOffset() { return Q2_START; };
	virtual int getLength() { return Q3_START - Q2_START; };
	Atm_controller ctrl;
};

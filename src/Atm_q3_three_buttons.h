#pragma once

#include "Atm_q2_two_buttons.h"

class Atm_q3_three_buttons: public Atm_q2_two_buttons {
public:
    Machine &begin();

protected:
	virtual int getOffset() { return Q3_START; };
	virtual int getLength() { return Q4_START - Q3_START; };
};

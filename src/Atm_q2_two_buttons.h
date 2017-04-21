#pragma once

#include "Atm_q1_one_button.h"

class Atm_q2_two_buttons : public Atm_q1_one_button {
public:
    Machine &begin();

protected:
    virtual int getOffset() { return 20; };
    virtual int getLength() { return 30; };
    Atm_controller ctrl;
};

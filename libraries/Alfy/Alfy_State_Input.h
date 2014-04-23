#ifndef ALFY_STATE_INPUT_H
#define ALFY_STATE_INPUT_H

#include <FL/Fl.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Input.H>

#include "Alfy_Strings.h"
#include "Alfy_Enumerations.h"

#include <string>

class Alfy_State_Input : public Fl_Input
{
    STATE _state;
    int _state_type;

    Fl_Color    BACK_COLOR,
                BAD_COLOR;
public:
    Alfy_State_Input(int X, int Y, int W = 80, int H = 24, const char *l=0);

    int handle(int event);

    void state_type(int type)   { _state_type = type;   }
    int state_type()            { return _state_type;   }

    void state(STATE s);
    void state(const char s[]);
    STATE state()               { return _state;        }

    const char* stateString();
};

#endif

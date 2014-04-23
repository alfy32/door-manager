#ifndef ALFY_PHONE_INPUT_H
#define ALFY_PHONE_INPUT_H

#include <FL/Fl.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Input.H>

#include "Alfy_Phone.H"

class Alfy_Phone_Input : public Fl_Input
{
    Alfy_Phone _number;

    Fl_Color    BACK_COLOR,
                BAD_COLOR;
public:
    Alfy_Phone_Input(int X, int Y, int W = 103, int H = 24, const char *l=0);

    int handle(int event);

    void phoneNumber(Alfy_Phone number)             { _number = number;     }
    Alfy_Phone phoneNumber()                        { return _number;       }
};

#endif

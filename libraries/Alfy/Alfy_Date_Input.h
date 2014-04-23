#ifndef ALFY_DATE_INPUT_H
#define ALFY_DATE_INPUT_H

#include <FL/Fl.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Input.H>

#include "Alfy_Date.h"

#include <string>

class Alfy_Date_Input : public Fl_Input
{
    Alfy_Date _date;

    std::string _default;
    Fl_Color    BACK_COLOR,
                BAD_COLOR;
public:
    Alfy_Date_Input(int X, int Y, int W = 80, int H = 24, const char *l=0);

    int handle(int event);

    void defaultNumber(std::string defaultNumber)   { _default = defaultNumber; value(_default.c_str()); }

    void date(Alfy_Date date)               { _date = date;     }
    Alfy_Date date()                        { return _date;     }
};

#endif

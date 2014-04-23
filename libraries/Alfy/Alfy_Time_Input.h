#ifndef ALFY_TIME_INPUT_H
#define ALFY_TIME_INPUT_H

#include <FL/Fl.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Input.H>

#include "Alfy_Time.h"

class Alfy_Time_Input : public Fl_Input
{
    Alfy_Time _time;

    Fl_Color    BACK_COLOR,
                BAD_COLOR;
public:
    Alfy_Time_Input(int X, int Y, int W = 70, int H = 24, const char *l=0);

    int handle(int event);

    Alfy_Time time()                { return _time;     }
    void time(Alfy_Time time_)      { _time = time_;    }
};

#endif

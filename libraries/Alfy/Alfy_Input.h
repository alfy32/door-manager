#ifndef ALFY_INPUT_H
#define ALFY_INPUT_H

#include <FL/Fl.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Input.H>

class Alfy_Input : public Fl_Input
{
    Fl_Color    BACK_COLOR,
                BAD_COLOR;
public:
    Alfy_Input(int X, int Y, int W=80, int H=24, const char *l=0);

    int handle_empty(int event);
    int handle(int event);
};

#endif

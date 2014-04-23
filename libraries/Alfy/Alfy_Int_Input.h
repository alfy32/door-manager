#ifndef ALFY_INT_INPUT_H
#define ALFY_INT_INPUT_H

#include <FL/Fl.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Input.H>

#include "Alfy_Strings.h"

#include <string>

class Alfy_Int_Input : public Fl_Input
{
    int _value_int;

    Fl_Color    BACK_COLOR,
                BAD_COLOR;
public:
    Alfy_Int_Input(int X, int Y, int W = 80, int H = 24, const char *l=0);

    int handle(int event);

    void value_int(int num);
    void value_int(const char num[]);
    int value_int();
    std::string value_string();
};

#endif

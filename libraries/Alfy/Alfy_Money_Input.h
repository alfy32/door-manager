#ifndef ALFY_MONEY_INPUT_H
#define ALFY_MONEY_INPUT_H

#include <FL/Fl.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Input.H>

#include "Alfy_Strings.h"

#include <string>

class Alfy_Money_Input : public Fl_Input
{
    double _money;

    Fl_Color    BACK_COLOR,
                BAD_COLOR;
public:
    Alfy_Money_Input(int X, int Y, int W = 80, int H = 24, const char *l=0);

    int handle(int event);

    void money(double amount);
    void money(const char amount[]);
    double money();
    std::string moneyString();
};

#endif

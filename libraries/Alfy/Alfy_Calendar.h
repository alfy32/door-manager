#ifndef ALFY_CALENDAR_H
#define ALFY_CALENDAR_H

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <SI/Si_Button.H>

#include "Alfy_Date.h"
#include "Alfy_Enumerations.h"
#include "Alfy_Strings.h"

#include <string>
#include <ctime>

class Alfy_Calendar : public Fl_Double_Window
{
    Fl_Box* dayHeaders[7];
    Fl_Box* monthHeader;
    Fl_Button* days[32];
    Fl_Button* selected_day;

    static const char* day_numbers[32];
    static const int days_months[13];

    int         BOX_WIDTH,
                BOX_HEIGHT,
                HEIGHT_NORMAL,
                HEIGHT_SHORT,
                TOP;

    Fl_Boxtype  HEADER_BOX,
                DAY_BOX,
                ARROW_BOX,
                WINDOW_BOX;

    Fl_Color    COLOR_CALBACKGROUND,
                COLOR_CALBUTTONS,
                COLOR_CALHEADER,
                COLOR_CALTODAY,
                COLOR_CALHIGHLIGHT;

    MONTH       current_month,
                actual_month;

    bool        show_month;

    int         day_names_type;

    int         current_year,
                actual_year,
                current_day,
                actual_day;

    void makeMonthHeaders();
    void makeHeaders();
    void makeDays(int month, int year);
    void moveDays(int month, int year);
    void setNumbers(int start);
    int getStartDay(int month, int year);
    char* getActualDateChar();
    int getDaysInMonth(int month);
    std::string getMonthLabel();

    static void cb_Day(Fl_Button* b, void* v)           {((Alfy_Calendar*)(b->parent()->user_data()))->cb_Day_Click(b,(int)v); }
    static void cb_NextMonth(Fl_Button* b, void* v)     {((Alfy_Calendar*)(b->parent()->user_data()))->cb_NextMonth_Click(b,v);}
    static void cb_PrevMonth(Fl_Button* b, void* v)     {((Alfy_Calendar*)(b->parent()->user_data()))->cb_PrevMonth_Click(b,v);}
    void cb_Day_Click(Fl_Button* b, int day);
    void cb_NextMonth_Click(Fl_Button* b, void* v);
    void cb_PrevMonth_Click(Fl_Button* b, void* v);
public:
    Alfy_Calendar(int X, int Y, int W = 7*30, int H = 8*20);

    void show();

    Alfy_Date getDate();
};

#endif

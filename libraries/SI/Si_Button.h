// this is the Si button implementation. It is the same as the regular Fl_Button, just with hover coloring.

#ifndef SI_BUTTON_H
#define SI_BUTTON_H

#include <FL/Fl_Button.H>

class Si_Button : public Fl_Button
{
public:
    Si_Button(int X, int Y, int W, int H, const char *L = 0, unsigned int Color=0);
    int handle(int);

    Fl_Color hover_color()              { return hover_color_;   }
    void hover_color(Fl_Color color)    { hover_color_ = color; }
private:
    int hover_;

    Fl_Color hover_color_;

    virtual void draw();
};

#endif // SI_BUTTON_H

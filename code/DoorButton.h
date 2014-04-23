#ifndef DOORBUTTON_H
#define DOORBUTTON_H

#include <fstream>
#include <string>

#include "door.h"

#include <FL/Fl_Button.H>
#include <FL/Fl_Jpeg_Image.H>

using namespace std;


class DoorButton : public Fl_Button
{
    Door door;
public:
    DoorButton(int X, int Y, int W, int H, const char *L=0);

    void add_door(Door door);

    Door get_door();
};

#endif // DOOR_H_INCLUDED

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "fltkgui.h"
#include "sqlite3.h"
#include "door.h"
#include <FL/Fl_Double_Window.H>
#include <FL/FL_JPEG_IMAGE.H>

const char FILE_PRICE[] = "prices.csv";
const char FILE_SIZE[] = "sizes.csv";

int db_callback(void *NotUsed, int col, char **values, char **colName);
int db_callback_price(void *NotUsed, int col, char **values, char **colName);
int db_callback_size(void *NotUsed, int col, char **values, char **colName);
void cb_resize(Fl_Double_Window*);
void restartDoors();
void addDoor(Door door);
void runSQL(sqlite3 *db, const char *pSQL);
void csvToSQL(sqlite3 *db, string fileName);
void openDatabase(sqlite3 *db, string name);

void cb_door_click(Fl_Button*, void*);
void cb_size(Fl_Widget*, void*);
void cb_swing(Fl_Widget*, void*);
void cb_jamb_size(Fl_Widget*, void*);
void cb_jamb_material(Fl_Widget*, void*);
void cb_sill(Fl_Widget*, void*);
void cb_get_price();

void door_options(Door door);
void get_sizes(string);
void read_price_csv();
void price_calc();
void read_size_csv();
void size_calc();

float string_to_float(const char number[]);

class Resize_Window : public Fl_Double_Window
{
public:
    Resize_Window(int W, int H, const char *l = 0)
    : Fl_Double_Window(W,H,l){}
    Resize_Window(int X, int Y, int W, int H, const char *l = 0)
    : Fl_Double_Window(X,Y,W,H,l) {}

    void resize(int X,int Y,int W,int H)
    {
        //save the old width and height
        int width = w();
        int height = h();

        //do the normal resize
        Fl_Double_Window::resize(X, Y, W, H);

        //check if it ws changed
        if(W != width || H != height)
           cb_resize(this);
    }
};

#endif

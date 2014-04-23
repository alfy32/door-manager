#ifndef DOOR_SIZE_CHOOSER_H
#define DOOR_SIZE_CHOOSER_H

#include <vector>
#include <string>
#include <stdlib.h>

#include <FL/Fl_Choice.H>

#include "DoorSize.h"
#include "sqlite3.h"

class Door_Size_Chooser : public Fl_Choice
{
    string style;                   //the style of the door
    sqlite3 *db;                    //a pointer to the database
    vector<DoorSize> sizes;         //the sizes for the given door
    double price_single;            //single door price
    double price_double;            //double door price
    vector<bool> available;         //whether the door is available

    static Door_Size_Chooser* me;

public:
    Door_Size_Chooser(int X, int Y, int W, int H, const char * L = 0);

    //returns the price givent the user_data of the widget.
    double get_price();

    //reads all necessary info from the database according to the given style of door.
    int set_door_style(sqlite3 *db, string style);

protected:
    //runs the SQL to get the sizes
    void get_sizes();
    void get_prices();
    void get_available();

    void fill_menu();

    int index_converter(int index);

    //database callback to fill the sizes vector with all sizes from the database
    static int load_sizes_sql_stat(void *NotUsed, int col, char **values, char **colName)
    { me->load_sizes_sql(NotUsed, col, values, colName); }
    int load_sizes_sql(void *NotUsed, int col, char **values, char **colName);
    //database callback to set the prices of the single and double doors.
    static int load_prices_sql_stat(void *NotUsed, int col, char **values, char **colName)
    { me->load_prices_sql(NotUsed, col, values, colName); }
    int load_prices_sql(void *NotUsed, int col, char **values, char **colName);
    //database callback to set whether the certain size is available for the door.
    static int load_available_sql_stat(void *NotUsed, int col, char **values, char **colName)
    { me->load_available_sql(NotUsed, col, values, colName); }
    int load_available_sql(void *NotUsed, int col, char **values, char **colName);

    float string_to_float(const char number[]);
};

//TODO Define "void cb_Door_Size_Chooser(Fl_Input*, void*)" in progam.
//say declare the callback for the menu items.
extern void cb_Door_Size_Chooser(Fl_Widget*, void*);


#endif

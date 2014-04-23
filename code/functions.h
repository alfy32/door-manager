#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "fltkgui.h"
#include "sqlite3.h"
#include "door.h"
#include "DoorButton.h"
#include <string>
#include <FL/Fl_Double_Window.H>
#include <FL/FL_JPEG_IMAGE.H>

//to be able to print
#include <FL/Fl_Printer.H>
#include <FL/Fl_PostScript.H>

//for file operations with the postscript -> pdf
#include <stdio.h>
#include <stdlib.h>
//the ghostscript command:  system("C:\\Progra~1\\gs\\gs9.05\\bin\\gswin32c -sDEVICE=pdfwrite -sOutputFile=TestPrint.pdf -dBATCH -dNOPAUSE myfile.ps");

void printGroupBox(Fl_Group* grouptoprint, bool printpdf);

/////////////////////////////////////

///**functions.cpp
float string_to_float(const char number[]);
string double_to_string(double number);
string strip_quotes(string);



///**callbacks_main
//void cb_MostUsedItemSelected(Fl_Browser*, void*);
//void cb_SearchTextChanged(Fl_Input* input, void*);
//void cb_resize(Fl_Double_Window* w);
//void cb_door_click(Fl_Button*, void* data);
//int db_callback(void *NotUsed, int col, char **values, char **colName);
//int db_callback_size(void *NotUsed, int col, char **values, char **colName);

///**functions_main
void restart_doors();
string get_select_door_WHERE();
DoorButton *add_door(Door door);
void door_options(Door door);
void get_sizes(string style);
void get_prices(string style);

///*callbacks_options
void cb_jamb(Fl_Widget *w, void *v);

///**functions_options
void set_door_swing(bool single);
void set_jamb_size();



const char FILE_PRICE[] = "prices.csv";
const char FILE_SIZE[] = "sizes.csv";

int db_callback(void *NotUsed, int col, char **values, char **colName);
int db_callback_price(void *NotUsed, int col, char **values, char **colName);
int db_callback_size(void *NotUsed, int col, char **values, char **colName);
void cb_resize(Fl_Double_Window*);
void runSQL(sqlite3 *db, const char *pSQL);
void csvToSQL(sqlite3 *db, string fileName);
void openDatabase(sqlite3 *db, string name);

void cb_update(Fl_Widget*, void*);
void cb_markup(Fl_Widget*, void*);
void cb_swing(Fl_Widget*, void*);
void cb_size(Fl_Widget*, void*);
void cb_door_click(DoorButton*, void*);

void get_sizes(string);
void read_price_csv();
void price_calc();
void read_size_csv();
void size_calc();



#endif

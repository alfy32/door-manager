//This is where the callbacks go. It works quite like visual basic, to tell the truth.
//all of the necessary widgets should have pointers available to them (see fltkgui.h)
#include "fltkgui.h"

const string LIMIT_QUERY = "";  // " LIMIT 50";

//the pointer to keep track of the options window
Fl_Double_Window *wnd_new;

//this is the "favorites" viewer click callback. the favorites box also helps
//things to resize correctly.
void cb_MostUsedItemSelected(Fl_Browser*, void*)
{
    //TODO decide if we need most selected doors
}

//When any of the text is changed in any of the search boxes, this is called
//so you can updade the door grid
void cb_SearchTextChanged(Fl_Input* input, void*)
{
    //point to the database
    sqlite3 * db = wnd_main->db;

    restart_doors();

    //add the beginnig of the SELECT statement to count the doors
    string search2 = "SELECT COUNT(*) AS count FROM doors " + get_select_door_WHERE();

    //execute the count sql statement
    runSQL(db, search2.c_str());

    //add the beginnig of the SELECT statement
    string search1 = "SELECT * FROM doors " + get_select_door_WHERE() + LIMIT_QUERY;

    //execute the SQL statement
    runSQL(db, search1.c_str());
}

//for when the window resized to change the width
void cb_resize(Fl_Double_Window* w)
{
    restart_doors();

    //remake the SQL statement and run it
    string search = "SELECT * FROM doors "
                + get_select_door_WHERE() + LIMIT_QUERY;

    runSQL(wnd_main->db, search.c_str());
}

//the callback for when a door is clicked on.
//opens the options window and gives it the needed info.
void cb_door_click(DoorButton* b, void*)
{
    //if there is already a window delete it to make the new one
    if(wnd_new != NULL)
        delete wnd_new;

    //make the new window
    wnd_new = make_door_info_dialog();
    wnd_new->show();

    //call this to set up the options window
    door_options(b->get_door());
}

bool one_door = false;

// This is the callback function to display the select data in the table
// it is called for ever row taken from the table
int db_callback(void *NotUsed, int col, char **values, char **colName)
{
    if(col == 1)
    {
        if(values[0][0] == '1' && values[0][1] == 0)
        {
            one_door = true;
            cout << "found one door" << endl;
        }
    }
    else
    {
        Door door(values[0],values[1],values[2],values[3]);

        DoorButton *b = add_door(door);

        if(one_door)
        {
            cout << "got it" << endl;
            cb_door_click(b,0);
            one_door = false;
        }
    }
/*
    //output the database for testing purposes
    int i;
    for(i=0; i<col; i++)
    {
        cout << colName[i] << ": " << values[i] << endl;

    }
    cout << endl;
*/
   // cout << ".";

	return 0;
}



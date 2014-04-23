//This is where the callbacks go. It works quite like visual basic, to tell the truth.
//all of the necessary widgets should have pointers available to them (see fltkgui.h)
#include "fltkgui.h"

const string LIMIT_QUERY = " LIMIT 50";
const string DB_NAME = "data";

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
    restart_doors();

    //get a count of the doors to see if there is only one.
    if(wnd_main->db.getInt("SELECT COUNT() AS count FROM doors " + get_select_door_WHERE()) == 1)
    {
        wnd_main->db.runSQL("SELECT * FROM doors " + get_select_door_WHERE(), db_callback_one_door);
    }
    else    //do a normal select and show all searched for doors
    {
        wnd_main->db.runSQL("SELECT * FROM doors " + get_select_door_WHERE() + LIMIT_QUERY, db_callback_door);
    }
}

//for when the window resized to change the width
void cb_resize(Fl_Double_Window* w)
{
    restart_doors();

    //remake the SQL statement and run it
    wnd_main->db.runSQL("SELECT * FROM doors " +
                        get_select_door_WHERE() + LIMIT_QUERY,
                        db_callback_door);
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

// This is called for every row in the database and
//  creates a door button for each row
int db_callback_door(void *NotUsed, int col, char **values, char **colName)
{
    //check if valid data came from the dataabase
    if(values[0] && values[1] && values[2] && values[3])
    {
        //create a door
        Door door(values[0],values[1],values[2],values[3]);

        //create a button with the values
        add_door(door);
    }

	return 0;
}

// This is the callback funtion for when there is only one door selected
//  from the database.
int db_callback_one_door(void *NotUsed, int col, char **values, char **colName)
{
    //check if valid data came from the dataabase
    if(values[0] && values[1] && values[2] && values[3])
    {
        //create a door
        Door door(values[0],values[1],values[2],values[3]);

        //create a button with the values
        DoorButton *b = add_door(door);

        //for testing
        //cout << "Just one door" << endl;

        //click the button because it is the only one
        cb_door_click(b,0);
    }

	return 0;
}



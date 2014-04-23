//This is where the callbacks go. It works quite like visual basic, to tell the truth.
//all of the necessary widgets should have pointers available to them (see fltkgui.h)
#include "fltkgui.h"

Fl_Double_Window *wnd_new;

//this is the "favorites" viewer click callback. the favorites box also helps
//things to resize correctly.
void cb_MostUsedItemSelected(Fl_Browser*, void*)
{

}

//When any of the text is changed in any of the search boxes, this is called
//so you can updade the door grid
void cb_SearchTextChanged(Fl_Input* input, void*)
{
    sqlite3 * db = (sqlite3*)(wnd_main->user_data());

    scroll_DoorGrid->clear();
    scroll_DoorGrid->redraw();
    restartDoors();

    string search = "WHERE style LIKE '";
    search += ipt_style->value();
    search += "%' AND ";
    search += "material LIKE '";
    search += ipt_material->value();
    search += "%' AND ";
    search += "glass LIKE '";
    search += ipt_glass_style->value();
    search += "%'";

    string search2 = "SELECT COUNT(*) AS count FROM doors " + search;

    runSQL(db, search2.c_str());

    string search1 = "SELECT * FROM doors " + search;

    runSQL(db, search1.c_str());
}

void cb_grid(Fl_Group*, void*)
{
    sqlite3 * db = (sqlite3*)(wnd_main->user_data());

    scroll_DoorGrid->clear();
    scroll_DoorGrid->redraw();
    restartDoors();

    string search = "SELECT * FROM doors ";
    search += "WHERE style LIKE '";
    search += ipt_style->value();
    search += "%' AND ";
    search += "material LIKE '";
    search += ipt_material->value();
    search += "%' AND ";
    search += "glass LIKE '";
    search += ipt_glass_style->value();
    search += "%'";

    runSQL(db, search.c_str());
}

void cb_door_click(Fl_Button*, void* data)
{
    Door *door = (Door*)data;

    if(wnd_new != NULL)
        delete wnd_new;

    wnd_new = make_door_info_dialog(*door);
    wnd_new->show();

    door_options(*door);

    cout << door->style();
}

void cb_resize(Fl_Double_Window* w)
{
    sqlite3 * db = (sqlite3*)(wnd_main->user_data());

    scroll_DoorGrid->clear();
    scroll_DoorGrid->redraw();
    restartDoors();

    string search = "SELECT * FROM doors ";
    search += "WHERE style LIKE '";
    search += ipt_style->value();
    search += "%' AND ";
    search += "material LIKE '";
    search += ipt_material->value();
    search += "%' AND ";
    search += "glass LIKE '";
    search += ipt_glass_style->value();
    search += "%'";


    runSQL(db, search.c_str());
}

bool one_door = false;
string * sizes;

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

        addDoor(door);

        if(one_door)
        {
            cout << "got it" << endl;
            cb_door_click(0,(void*)new Door(door));
            one_door = false;
        }
    }

    //output the database for testing purposes
    int i;
    for(i=0; i<col; i++)
    {
        cout << colName[i] << ": " << values[i] << endl;

    }
    cout << endl;

	return 0;
}

// This is the callback function to display the select data in the table
// it is called for ever row taken from the table
int db_callback_size(void *NotUsed, int col, char **values, char **colName)
{
    string temp = values[0];

    if(temp == "sizes")
    {
        if(sizes != 0)
        {
            delete [] sizes;
        }

        sizes = new string[col];

        for(int i=1; i<col; i++)
        {
            sizes[i] =  values[i];
        }
    }
    else
    {
        for(int i=1; i<col; i++)
        {
            temp = values[i];
            if(temp != "0")
                lst_DoorSize->add(sizes[i].c_str(),0,cb_size,0,0);
        }
    }



    //output the database for testing purposes
	for(int i=0; i<col; i++)
	{
		cout << colName[i] << ": " << values[i] << endl;

	}
	cout << endl;

	return 0;
}

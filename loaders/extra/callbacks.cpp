//This is where the callbacks go. It works quite like visual basic, to tell the truth.
//all of the necessary widgets should have pointers available to them (see fltkgui.h)
#include "fltkgui.h"

Fl_Double_Window *newWnd;
int price[2];

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

    string search = "WHERE door_style LIKE '";
    search += ipt_style->value();
    search += "%' AND ";
    search += "material LIKE '";
    search += ipt_material->value();
    search += "%' AND ";
    search += "glass_style LIKE '";
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
    search += "WHERE door_style LIKE '";
    search += ipt_style->value();
    search += "%' AND ";
    search += "material LIKE '";
    search += ipt_material->value();
    search += "%' AND ";
    search += "glass_style LIKE '";
    search += ipt_glass_style->value();
    search += "%'";

    runSQL(db, search.c_str());
}

void cb_door_click(Fl_Button*, void* data)
{
    Door *door = (Door*)data;

    if(newWnd != NULL)
        delete newWnd;

    newWnd = make_door_info_dialog(*door);
    newWnd->show();

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
    search += "WHERE door_style LIKE '";
    search += ipt_style->value();
    search += "%' AND ";
    search += "material LIKE '";
    search += ipt_material->value();
    search += "%' AND ";
    search += "glass_style LIKE '";
    search += ipt_glass_style->value();
    search += "%'";


    runSQL(db, search.c_str());
}

void cb_size(Fl_Widget* , void*)
{
    lst_DoorSize->label(lst_DoorSize->text());
    cb_get_price();
}

void cb_swing(Fl_Widget*, void*)
{
    lst_DoorSwing->label(lst_DoorSwing->text());
    cb_get_price();
}

void cb_jamb_size(Fl_Widget*, void*)
{
    lst_JambSize->label(lst_JambSize->text());
    cb_get_price();
}

void cb_jamb_material(Fl_Widget*, void*)
{
    lst_JambMaterial->label(lst_JambMaterial->text());
    cb_get_price();
}

void cb_sill(Fl_Widget*, void*)
{
    lst_Sill->label(lst_Sill->text());
    cb_get_price();
}

void cb_get_price()
{
    double total;
    bool single = lst_DoorSize->text()[0] < '5';

    if(single)
    {
        total = price[0];

        if(chk_BrickMoldNo->value())
            total -= 7;
    }
    else
    {
        total = price[1];

        if(chk_BrickMoldNo->value())
            total -= 12;
    }

    if(chk_DeadBoltYes)
        total += 5;

    val_Cost->value(total);
}

Fl_Double_Window *wnd_print;

//-----Door Information Window Callbacks.
void cb_PrintClicked(Fl_Button*, void*)
{
    wnd_print = make_print_dialog();
    wnd_print->show();

    Fl_JPEG_Image *img;

    string picture = "doors\\";
    picture += opt_DoorStyle->value();
    picture += ".jpg";
    img = new Fl_JPEG_Image(picture.c_str());

    box_Print_DoorImage->image(img->copy(130,251));

    opt_Print_LocationName->label(txt_LocationName->value());

    opt_Print_DoorSize->label(lst_DoorSize->text());
    opt_Print_DoorMaterial->label(opt_DoorMaterial->value());
    opt_Print_DoorStyle->label(opt_DoorStyle->value());
    opt_Print_DoorSwing->label(lst_DoorSwing->text());
    opt_Print_JambSize->label(lst_JambSize->text());
    opt_Print_JambMaterial->label(lst_JambMaterial->text());
    opt_Print_Sill->label(lst_Sill->text());
    if(chk_BrickMoldYes->value())
        opt_Print_Brickmold->label("Yes");
    else
        opt_Print_Brickmold->label("No");
    if(chk_DeadBoltNo->value())
        opt_Print_DeadBolt->label("Yes");
    else
        opt_Print_DeadBolt->label("No");
    opt_Print_GlassStyle->label(opt_GlassStyle->value());
    opt_Print_HingeColor->label(lst_HingeColor->text());
    //opt_Print_Price->label();
}
void cb_CancelClicked(Fl_Button*, void*)
{
    newWnd->hide();
}

bool one_door = false;
string *sizes;



// This is the callback function to display the select data in the table
// it is called for ever row taken from the table
int db_callback_price(void *NotUsed, int col, char **values, char **colName)
{
    price[0] = string_to_float(values[1]);
    price[1] = string_to_float(values[2]);

    //output the database for testing purposes
	for(int i=0; i<col; i++)
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
                lst_DoorSize->add(sizes[i].c_str(),0,cb_size,new string(temp),0);
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

//-----Print Preview Dialog Callbacks.
void cb_Preview_PrintClicked(Fl_Button*, void*)
{

}
void cb_Preview_CancelClicked(Fl_Button*, void*)
{

}

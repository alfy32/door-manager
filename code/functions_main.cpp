//All of the under the hood stuff goes here. You have access to
//all widgets that are named. (see fltkgui.h)
#include "functions.h"
#include <FL/FL_JPEG_IMAGE.H>

//deletes all door info
void restart_doors()
{
    scroll_DoorGrid->clear();
    scroll_DoorGrid->redraw();

    grp_DoorGrid->user_data(0);
    scroll_DoorGrid->user_data(0);
}

string get_select_door_WHERE()
{
    string search = "WHERE style LIKE '";
    search += ipt_style->value();
    search += "%' AND ";
    search += "material LIKE '";
    search += ipt_material->value();
    search += "%' AND ";
    search += "design LIKE '";
    search += ipt_design->value();
    search += "%' AND ";
    search += "glass LIKE '";
    search += ipt_glass_style->value();
    search += "%'";

    return search;
}

//adds a door to the scrollview
DoorButton *add_door(Door door)
{
    //point to the user data of the door grid to keep track of
    //the next positions of the doors
    int posX = (int)grp_DoorGrid->user_data();
    int posY = (int)scroll_DoorGrid->user_data();

    //find how wide the window is to find the number of columns and
    //the width of the doors
	int gridWidth = grp_DoorGrid->w() - 20;
	int cols = gridWidth/250;
	int width = gridWidth/cols;

    //set the beginning position of the door buttons
    if(posX == 0)
        posX = grp_DoorGrid->x();

    //create the new button
    DoorButton *o = new DoorButton(posX, posY, width, 310, "button");
    o->box(FL_NO_BOX);
    o->callback((Fl_Callback*)cb_door_click, 0);
    o->add_door(door);

    //add to the width
    posX += o->w();

    //make sure it didn't go off the edge and if so start the next row.
    if(posX > (grp_DoorGrid->x() + gridWidth - width))
    {
        posX = 0;
        posY += o->h();
    }

    //save the x and y postions for the next doors
    grp_DoorGrid->user_data((void*)posX);
    scroll_DoorGrid->user_data((void*)posY);

    scroll_DoorGrid->add(o);

    return o;
}

//sets up the options window when the door is selected
void door_options(Door door)
{
    //get the picture of the door
    string picture = "doors\\";
    picture += door.style();
    picture += ".jpg";
    Fl_JPEG_Image *img = new Fl_JPEG_Image(picture.c_str());

    //put the picture in the box
    boxDoorImage->image(img->copy(130,251));

    //set up the text in the boxes
    opt_DoorDesign->value(door.design().c_str());
    opt_DoorMaterial->value(door.material().c_str());
    opt_DoorStyle->value(door.style().c_str());
    opt_GlassStyle->value(door.glass_style().c_str());

    ///to set up the options window

    //get the sizes for the door
    lst_DoorSize->set_door_style(wnd_main->db.getDatabase(),door.style());

    set_door_swing(true);

    string sql;

    wnd_main->db.runSQL(sql+"SELECT label FROM PriceList " +
                        "WHERE list = 'SILL' " +
                        "AND type = 'SILL'",
                        db_callback_lst_sill);
    wnd_main->db.runSQL(sql+"SELECT label FROM PriceList " +
                        "WHERE list = 'HINGE' " +
                        "AND type = 'COLOR'",
                         db_callback_lst_hinge_color);
    wnd_main->db.runSQL(sql+"SELECT type FROM PriceList "+
                        "WHERE list = 'JAMB_MATERIAL'",
                         db_callback_lst_jamb_material);

    set_jamb_size();
}

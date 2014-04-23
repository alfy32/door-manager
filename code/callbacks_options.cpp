//This is where the callbacks go. It works quite like visual basic, to tell the truth.
//all of the necessary widgets should have pointers available to them (see fltkgui.h)
#include "fltkgui.h"

Fl_Double_Window *wnd_print;    //keeps track of the print window

//called when an option is chosen from the door size list
void cb_Door_Size_Chooser(Fl_Widget *w, void*v)
{
    bool single;
    if(lst_DoorSize->text())
    {
        single = lst_DoorSize->text()[0] < '5';

        lst_DoorSwing->clear();
        lst_DoorSwing->redraw();

        set_door_swing(single);
    }
    cb_update(w,v);
}

//called when the jamb material is chosen
// resets the jamb sizes according to the jamb material
// then updatest the prices
void cb_jamb(Fl_Widget *w, void *v)
{
    set_jamb_size();

    cb_update(w,v);
}

void cb_jamb_size(Fl_Widget *w, void *v)
{
    string jamb_size;
    if(lst_JambSize->text())
        jamb_size = lst_JambSize->text();
    int size = jamb_size.find("Custom");
    if(size != -1)
    {
        txt_CustomRipSize->value("");
        txt_CustomRipSize->show();
    }
    else
    {
        txt_CustomRipSize->value("");
        txt_CustomRipSize->hide();
    }

    cb_update(w,v);
}

//Called by anything that changes the cost
// updates the cost of everything and does the math
void cb_update(Fl_Widget*, void*)
{
    double total = 0;
    string single_double = "single";
    string sql = "";
    string sill, hinge_color, jamb_material, jamb_size;

    if(lst_DoorSize->text())
        total = lst_DoorSize->get_price();
    opt_DoorCost->value(total);

    if(lst_Sill->text())
        sill = lst_Sill->text();
    if(lst_HingeColor->text())
        hinge_color = lst_HingeColor->text();
    if(lst_JambMaterial->text())
        jamb_material = lst_JambMaterial->text();
    if(lst_JambSize->text())
        jamb_size = lst_JambSize->text();

    if(lst_DoorSize->text())
    {
        single_double = lst_DoorSize->text();

        if(single_double < "4'0")
            single_double = "single";
        else
            single_double = "double";
    }
    total += wnd_main->db.getDouble( sql +
                   "SELECT " + single_double + " FROM PriceList " +
                   "WHERE list = 'SILL' " +
                   "AND type = 'SILL' " +
                   "AND label = '" + sill + "'");
    total += wnd_main->db.getDouble( sql +
                   "SELECT " + single_double + " FROM PriceList " +
                   "WHERE list = 'HINGE' " +
                   "AND type = 'COLOR' " +
                   "AND label = '" + hinge_color + "'");
    total += wnd_main->db.getDouble( sql +
                   "SELECT " + single_double + " FROM PriceList " +
                   "WHERE list = 'SILL' " +
                   "AND type = 'SILL' " +
                   "AND label = '" + sill + "'");
    total += wnd_main->db.getDouble( sql +
                   "SELECT " + single_double + " FROM PriceList " +
                   "WHERE list = 'JAMB_MATERIAL' " +
                   "AND type = '" + jamb_material + "' " +
                   "AND label = '" + jamb_size + "'");
    int size = jamb_size.find("Custom");
    if(size != -1)
    {
        total += wnd_main->db.getDouble( sql +
                   "SELECT " + single_double + " FROM PriceList " +
                   "WHERE list = 'OTHER_OPTIONS' "
                   "AND label = 'Rip Jambs To Width'");
    }
    if(chk_NoBrickmold->value())
    {
        total -= wnd_main->db.getDouble( sql +
                   "SELECT " + single_double + " FROM PriceList " +
                   "WHERE list = 'OTHER_OPTIONS' "
                   "AND label = 'No Brickmould'");
    }
    if(chk_DeadBolt->value())
    {
        total += wnd_main->db.getDouble( sql +
                   "SELECT " + single_double + " FROM PriceList " +
                   "WHERE list = 'OTHER_OPTIONS' "
                   "AND label = 'Dead Bolt'");
    }
    if(chk_DentilShelf->value())
    {
        total += wnd_main->db.getDouble( sql +
                   "SELECT " + single_double + " FROM PriceList " +
                   "WHERE list = 'OTHER_OPTIONS' "
                   "AND label = 'Dentil Shelf'");
    }
    if(chk_OutswingSill->value())
    {
        total += wnd_main->db.getDouble( sql +
                   "SELECT " + single_double + " FROM PriceList " +
                   "WHERE list = 'OTHER_OPTIONS' "
                   "AND label = 'Outswing Sill'");
    }
    if(chk_ADASill->value())
    {
        total += wnd_main->db.getDouble( sql +
                   "SELECT " + single_double + " FROM PriceList " +
                   "WHERE list = 'OTHER_OPTIONS' "
                   "AND label = 'ADA Sill'");
    }
    if(chk_SpringHinge->value())
    {
        total += wnd_main->db.getDouble( sql +
                   "SELECT " + single_double + " FROM PriceList " +
                   "WHERE list = 'OTHER_OPTIONS' "
                   "AND label = 'Spring Hinge'");
    }

    opt_Cost->value(total);

    total += total * val_Markup->value() / 100;

    total += val_LaborCost->value();

    total += total * val_Taxes->value() / 100;

    val_Total->value(total);
}

//-----Door Information Window Callbacks.
void cb_PrintClicked(Fl_Button*, void*)
{
    if(wnd_print)
        delete wnd_print;

    wnd_print = make_print_dialog();
    wnd_print->show();

    Fl_JPEG_Image *img;

    string picture = "doors\\";
    picture += opt_DoorStyle->value();
    picture += ".jpg";
    img = new Fl_JPEG_Image(picture.c_str());

    box_Print_DoorImage->image(img->copy(130,251));

    opt_Customer->copy_label(txt_Customer->value());
    opt_Job->copy_label(txt_Job->value());
    opt_Date->copy_label(txt_Date->value());

    opt_Print_LocationName->copy_label(txt_LocationName->value());

    opt_Print_DoorSize->copy_label(lst_DoorSize->text());
    opt_Print_DoorMaterial->copy_label(opt_DoorMaterial->value());
    opt_Print_DoorStyle->copy_label(opt_DoorStyle->value());
    opt_Print_DoorSwing->copy_label(lst_DoorSwing->text());
    opt_Print_DoorDesign->copy_label(opt_DoorDesign->value());

    opt_Print_JambMaterial->copy_label(lst_JambMaterial->text());

    string jamb_size = "";
    if(lst_JambSize->text())
        jamb_size = lst_JambSize->text();
    int size = jamb_size.find("Custom");
    if(size != -1)
    {
        jamb_size += " Rip to: ";
        jamb_size += txt_CustomRipSize->value();
    }
    opt_Print_JambSize->copy_label(jamb_size.c_str());

    string door_size;
    if(lst_DoorSize->text())
    {
        door_size = lst_DoorSize->text();
        string sql = "";
        sql = sql+"SELECT * FROM net_frame " +
                        "WHERE door_size = '" +
                        sql_replace_single_quote(door_size) + "' ";
        sql = "";
        wnd_main->db.runSQL(sql+"SELECT * FROM net_frame " +
                        "WHERE door_size = '" +
                        sql_replace_single_quote(door_size) + "' ",
                        db_callback_NetFrame_RO);
    }


    opt_Print_Sill->copy_label(lst_Sill->text());
    opt_Print_GlassStyle->copy_label(opt_GlassStyle->value());
    opt_Print_HingeColor->copy_label(lst_HingeColor->text());

    chk_Print_NoBrickmold->value(chk_NoBrickmold->value());
    chk_Print_DeadBolt->value(chk_DeadBolt->value());
    chk_Print_DentilShelf->value(chk_DentilShelf->value());
    chk_Print_OutswingSill->value(chk_OutswingSill->value());
    chk_Print_ADASill->value(chk_ADASill->value());
    chk_Print_SpringHinge->value(chk_SpringHinge->value());

    if(opt_Print_DoorSwing->label())
    {
        Fl_JPEG_Image *image;
        picture = "Swing\\";
        picture += opt_Print_DoorSwing->label();
        picture += ".jpg";
        image = new Fl_JPEG_Image(picture.c_str());

        img_Print_swing->image(image->copy(75,175));
    }

    opt_Print_Notes->copy_label(txt_Notes->value());

    string cost = "$";
    cost += double_to_string(val_Total->value());
    opt_Print_Price->copy_label(cost.c_str());
}
void cb_CancelClicked(Fl_Button* b, void*)
{
    b->parent()->parent()->hide();
}

int db_callback_lst_sill(void *NotUsed, int col, char **values, char **colName)
{
    if(values[0])
    {
        lst_Sill->add(values[0],0,cb_update,0);
        //for testing
        //cout << "SILL: " << values[0] << endl;
    }
    return 0;
}

int db_callback_lst_hinge_color(void *NotUsed, int col, char **values, char **colName)
{
    if(values[0])
    {
        lst_HingeColor->add(values[0],0,cb_update,0);
        //for testing
        //cout << "HINGE COLOR: " << values[0] << endl;
    }
    return 0;
}

int db_callback_lst_jamb_material(void *NotUsed, int col, char **values, char **colName)
{
    if(values[0])
    {
        lst_JambMaterial->add(values[0],0,cb_jamb,0);
        //for testing
        //cout << "JAMB MATERIAL: " << values[0] << endl;
    }
    return 0;
}

int db_callback_lst_jamb_size(void *NotUsed, int col, char **values, char **colName)
{
    if(values[0])
    {
        lst_JambSize->add(fix_jamb_size(values[0]).c_str(),0,cb_jamb_size,0);
        //for testing
        //cout << "JAMB SIZE: " << values[0] << endl;
    }
    return 0;
}

int db_callback_lst_door_swing(void *NotUsed, int col, char **values, char **colName)
{
    if(values[0])
    {
        string type = "";

        if(values[1])
            type = values[1];

        if(type == "SECTION_HEADING")
        {
            string label = "_";
            label += values[0];
            lst_DoorSwing->add(label.c_str(),0,0,0,FL_MENU_INACTIVE);
        }
        else
            lst_DoorSwing->add(values[0]);

        //for testing
        //cout << "DOOR SWING: " << values[0] << endl;
    }
    return 0;
}

int db_callback_NetFrame_RO(void *NotUsed, int col, char **values, char **colName)
{
    string size = "";

    if(values[1] && values[2] && values[3] && values[4])
    {
        size = values[1];
        size += " x ";
        size += values[2];

        opt_Print_NetFrame->copy_label(size.c_str());

        size = values[3];
        size += " x ";
        size += values[4];

        opt_Print_RoughOpening->copy_label(size.c_str());
    }


    return 0;
}

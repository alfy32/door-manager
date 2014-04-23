//This is where the callbacks go. It works quite like visual basic, to tell the truth.
//all of the necessary widgets should have pointers available to them (see fltkgui.h)
#include "fltkgui.h"

Fl_Double_Window *wnd_print;    //keeps track of the print window
float price[3];                 //keeps track of the prices for each size

void cb_swing(Fl_Widget*w, void*v)
{
    cb_update(w,v);
}

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

void cb_jamb(Fl_Widget *w, void *v)
{
    set_jamb_size();

    cb_update(w,v);
}

void cb_labor(Fl_Value_Input*i, void*v)
{
    cb_update((Fl_Widget*)i,v);
}

void cb_update(Fl_Widget*, void*)
{
    double total = 0;
    bool single;
    string sill, hinge, jamb_material, jamb_size;

    if(lst_Sill->text())
        sill = lst_Sill->text();
    if(lst_HingeColor->text())
        hinge = lst_HingeColor->text();
    if(lst_JambMaterial->text())
        jamb_material = lst_JambMaterial->text();
    if(lst_JambSize->text())
        jamb_size = lst_JambSize->text();

    cout << jamb_size;

    if(lst_DoorSize->text())
    {
        single = lst_DoorSize->text()[0] < '5';
        total = lst_DoorSize->get_price();
        opt_DoorCost->value(total);

        if(single)
        {
            if(sill == "Bronze")
                total += 7;
            if(sill == "Brass")
                total += 43;
            if(sill == "Oak")
                total += 0;
            if(hinge != "Brass" && hinge != "")
                total += 5;

            if(jamb_material == "Primed" && jamb_size == "5-3/8 - 6-9/16")
                total += 15;
            if(jamb_material == "Primed" && jamb_size == "6-5/8 - 7-1/4")
                total += 30;
            if(jamb_material == "Primed" && jamb_size == "7-3/8 - 9-1/2")
                total += 45;
            if(jamb_material == "Oak" && jamb_size == "4-9/16")
                total += 136;
            if(jamb_material == "Oak" && jamb_size == "6-9/16")
                total += 163;
            if(jamb_material == "Oak" && jamb_size == "4-9/16 8'0\"")
                total += 222;
            if(jamb_material == "Oak" && jamb_size == "6-9/16 8'0\"")
                total += 222;
            if(jamb_material == "Knotty Alder" && jamb_size == "4-9/16")
                total += 100;
            if(jamb_material == "Knotty Alder" && jamb_size == "6-9/16")
                total += 130;
            if(jamb_material == "Solid Pine" && jamb_size == "4-9/16")
                total += 70;
            if(jamb_material == "Solid Pine" && jamb_size == "6-9/16")
                total += 82;
            if(jamb_material == "Composite" && jamb_size == "4-9/16")
                total += 83;
            if(jamb_material == "Composite" && jamb_size == "6-9/16")
                total += 93;
            if(chk_NeedsRipping->value())
                total += 5;

            if(chk_NoBrickmold->value())
                total -= 7;
            if(chk_DeadBolt->value())
                total += 5;
            if(chk_DentilShelf->value())
                total += 60;
            if(chk_OutswingSill->value())
                total += 10;
            if(chk_ADASill->value())
                total += 10;
            if(chk_SpringHinge->value())
                total += 12;
        }
        else
        {
            if(sill == "Bronze")
                total += 15;
            if(sill == "Brass")
                total += 65;
            if(sill == "Oak")
                total += 93;
            if(hinge != "Brass" && hinge != "")
                total += 10;

            if(jamb_material == "Primed" && jamb_size == "5-3/8 - 6-9/16")
                total += 30;
            if(jamb_material == "Primed" && jamb_size == "6-5/8 - 7-1/4")
                total += 50;
            if(jamb_material == "Primed" && jamb_size == "7-3/8 - 9-1/2")
                total += 100;
            if(jamb_material == "Oak" && jamb_size == "4-9/16")
                total += 192;
            if(jamb_material == "Oak" && jamb_size == "6-9/16")
                total += 226;
            if(jamb_material == "Oak" && jamb_size == "4-9/16 8'0\"")
                total += 260;
            if(jamb_material == "Oak" && jamb_size == "6-9/16 8'0\"")
                total += 260;
            if(jamb_material == "Knotty Alder" && jamb_size == "4-9/16")
                total += 150;
            if(jamb_material == "Knotty Alder" && jamb_size == "6-9/16")
                total += 180;
            if(jamb_material == "Solid Pine" && jamb_size == "4-9/16")
                total += 80;
            if(jamb_material == "Solid Pine" && jamb_size == "6-9/16")
                total += 96;
            if(jamb_material == "Composite" && jamb_size == "4-9/16")
                total += 91;
            if(jamb_material == "Composite" && jamb_size == "6-9/16")
                total += 106;
            if(chk_NeedsRipping->value())
                total += 10;

            if(chk_NoBrickmold->value())
                total -= 12;
            if(chk_DeadBolt->value())
                total += 5;
            if(chk_DentilShelf->value())
                total += 120;
            if(chk_OutswingSill->value())
                total += 20;
            if(chk_ADASill->value())
                total += 20;
            if(chk_SpringHinge->value())
                total += 24;
        }
    }
    opt_Cost->value(total);

    total += total * val_Markup->value() / 100;

    total += val_LaborCost->value() + total * val_Taxes->value() / 100;

    val_Total->value(total);
}


void cb_markup(Fl_Widget*, void*)
{
    double cost = opt_Cost->value();
    double markup = val_Markup->value();
    cost = cost + cost * markup / 100;

    val_Total->value(cost);
}

void cb_NeedsRipping_click(Fl_Check_Button*b, void*v)
{
    if(txt_CustomRipSize->active())
    {
        txt_CustomRipSize->value("");
        txt_CustomRipSize->deactivate();
    }
    else
        txt_CustomRipSize->activate();

    cb_update((Fl_Widget*)b,v);
}

//-----Door Information Window Callbacks.
void cb_PrintClicked(Fl_Button*, void*)
{
    if(wnd_print)
        delete wnd_print;

    wnd_print = make_print_dialog();
    wnd_print->show();

    int price[2];
    Fl_JPEG_Image *img;

    string picture = "doors\\";
    picture += opt_DoorStyle->value();
    picture += ".jpg";
    img = new Fl_JPEG_Image(picture.c_str());

    box_Print_DoorImage->image(img->copy(130,251));

    opt_Customer->label(txt_Customer->value());
    opt_Job->label(txt_Job->value());
    opt_Date->label(txt_Date->value());

    opt_Print_LocationName->label(txt_LocationName->value());

    opt_Print_DoorSize->label(lst_DoorSize->text());
    opt_Print_DoorMaterial->label(opt_DoorMaterial->value());
    opt_Print_DoorStyle->label(opt_DoorStyle->value());
    opt_Print_DoorSwing->label(lst_DoorSwing->text());
    opt_Print_DoorDesign->label(opt_DoorDesign->value());
    string jamb_size = "";
    if(lst_JambSize->text())
        jamb_size = lst_JambSize->text();
    if(chk_NeedsRipping->value())
    {
        jamb_size += " Rip to: ";
        jamb_size += txt_CustomRipSize->value();
    }
    opt_Print_JambSize->copy_label(jamb_size.c_str());
    opt_Print_JambMaterial->label(lst_JambMaterial->text());
    opt_Print_Sill->label(lst_Sill->text());
    opt_Print_GlassStyle->label(opt_GlassStyle->value());
    opt_Print_HingeColor->label(lst_HingeColor->text());

    chk_Print_NoBrickmold->value(chk_NoBrickmold->value());
    chk_Print_DeadBolt->value(chk_DeadBolt->value());
    chk_Print_DentilShelf->value(chk_DentilShelf->value());
    chk_Print_OutswingSill->value(chk_OutswingSill->value());
    chk_Print_ADASill->value(chk_ADASill->value());
    chk_Print_SpringHinge->value(chk_SpringHinge->value());

    opt_Print_Notes->label(txt_Notes->value());

    string cost = "$";
    cost += double_to_string(val_Total->value());
    opt_Print_Price->copy_label(cost.c_str());
}
void cb_CancelClicked(Fl_Button* b, void*)
{
    b->parent()->parent()->hide();
}

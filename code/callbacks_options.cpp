//This is where the callbacks go. It works quite like visual basic, to tell the truth.
//all of the necessary widgets should have pointers available to them (see fltkgui.h)
#include "fltkgui.h"

Fl_Double_Window *wnd_print;
float price[3];

void cb_swing(Fl_Widget*w, void*v)
{
    cb_update(w,v);
}

void cb_size(Fl_Widget *w, void *v)
{
    bool single = lst_DoorSize->text()[0] < '5';

    lst_DoorSwing->clear();
    lst_DoorSwing->redraw();

    if(single)
    {
        lst_DoorSwing->add("LHSI",0,cb_swing,0);
        lst_DoorSwing->add("LHSO",0,cb_swing,0);
        lst_DoorSwing->add("RHSI",0,cb_swing,0);
        lst_DoorSwing->add("RHSO",0,cb_swing,0);
    }
    else
    {
        lst_DoorSwing->add("_Both Operate");
        lst_DoorSwing->add("RHASI",0,cb_swing,0);
        lst_DoorSwing->add("RHASO",0,cb_swing,0);
        lst_DoorSwing->add("LHASI",0,cb_swing,0);
        lst_DoorSwing->add("_LHASO",0,cb_swing,0);
        lst_DoorSwing->add("_Left Stationary");
        lst_DoorSwing->add("Left LHSI",0,cb_swing,0);
        lst_DoorSwing->add("Left LHSO",0,cb_swing,0);
        lst_DoorSwing->add("Left RHSI",0,cb_swing,0);
        lst_DoorSwing->add("_Left RHSO",0,cb_swing,0);
        lst_DoorSwing->add("_Right Stationary");
        lst_DoorSwing->add("Right LHSI",0,cb_swing,0);
        lst_DoorSwing->add("Right LHSO",0,cb_swing,0);
        lst_DoorSwing->add("Right RHSI",0,cb_swing,0);
        lst_DoorSwing->add("Right RHSO",0,cb_swing,0);
    }

    cb_update(w,v);
}

void cb_update(Fl_Widget*, void*)
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

    if(chk_DeadBoltYes->value())
        total += 5;

    val_Cost->value(total);

    total = total + total * val_Markup->value() / 100;

    val_Price->value(total);
}

void cb_markup(Fl_Widget*, void*)
{
    double cost = val_Cost->value();
    double markup = val_Markup->value();
    cost = cost + cost * markup / 100;

    val_Price->value(cost);
}

//-----Door Information Window Callbacks.
void cb_PrintClicked(Fl_Button*, void*)
{
    wnd_print = make_print_dialog();
    wnd_print->show();

    int price[2];
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
    string cost = "$";
    cost += double_to_string(val_Price->value());
    opt_Print_Price->copy_label(cost.c_str());
}
void cb_CancelClicked(Fl_Button* b, void*)
{
    b->parent()->parent()->hide();
}

// This is the callback function to display the select data in the table
// it is called for ever row taken from the table
int db_callback_price(void *NotUsed, int col, char **values, char **colName)
{
    price[0] = string_to_float(values[1]);
    price[1] = string_to_float(values[2]);

    //void *cost = reinterpret_cast<void*>(&price[0]);


    //output the database for testing purposes
	for(int i=0; i<col; i++)
	{
		cout << colName[i] << ": " << values[i] << endl;

	}
	cout << endl;

	return 0;
}


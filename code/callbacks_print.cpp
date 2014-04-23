//This is where the callbacks go. It works quite like visual basic, to tell the truth.
//all of the necessary widgets should have pointers available to them (see fltkgui.h)
#include "fltkgui.h"
#include <FL/Fl_Printer.H>

//-----Print Preview Dialog Callbacks.
void cb_Preview_PrintClicked(Fl_Button*b, void*)
{
    printGroupBox(grp_PrintGroup, false);
}
void cb_Preview_CancelClicked(Fl_Button* b, void*)
{
    b->parent()->parent()->hide();
}
void cb_Preview_MakePDFClicked(Fl_Button*b, void*)
{
    printGroupBox(grp_PrintGroup, true);

    b->parent()->parent()->hide();
}

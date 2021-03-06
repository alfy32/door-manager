// generated by Fast Light User Interface Designer (fluid) version 1.0302

#ifndef fltkgui_h
#define fltkgui_h
#include <FL/Fl.H>
//#include <SI/Si_Button.H>
#include "Alfy_SQL.h"
#include "functions.h"
#include "door.h"
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Choice.H>
using namespace std;

class Resize_Window : public Fl_Double_Window {
public:
  Resize_Window(int W, int H, const char *l = 0);
  Resize_Window(int X, int Y, int W, int H, const char *l = 0);
  void resize(int X,int Y,int W,int H);
  Alfy_SQL db; 
};
extern Resize_Window *wnd_main;
#include <FL/Fl_Group.H>
extern Fl_Group *grp_Sidebar;
#include <FL/Fl_Input.H>
extern void cb_SearchTextChanged(Fl_Input*, void*);
extern Fl_Input *ipt_style;
extern Fl_Input *ipt_material;
extern Fl_Input *ipt_design;
extern Fl_Input *ipt_glass_style;
#include <FL/Fl_Browser.H>
extern void cb_MostUsedItemSelected(Fl_Browser*, void*);
extern Fl_Browser *bsr_MostUsed;
extern Fl_Group *grp_DoorGrid;
#include <FL/Fl_Scroll.H>
extern Fl_Scroll *scroll_DoorGrid;
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
extern Fl_Box *boxDoorImage;
#include <FL/Fl_Output.H>
extern Fl_Output *opt_DoorStyle;
extern Fl_Output *opt_DoorMaterial;
extern Fl_Output *opt_GlassStyle;
extern Fl_Output *opt_DoorDesign;
#include <FL/Fl_Value_Output.H>
extern Fl_Value_Output *opt_DoorCost;
#include "Door_Size_Chooser.h"
extern void cb_update(Door_Size_Chooser*, void*);
extern Door_Size_Chooser *lst_DoorSize;
#include <FL/Fl_Choice.H>
extern void cb_update(Fl_Choice*, void*);
extern Fl_Choice *lst_DoorSwing;
extern Fl_Choice *lst_Sill;
extern Fl_Choice *lst_HingeColor;
extern Fl_Input *txt_LocationName;
extern Fl_Input *txt_Customer;
extern Fl_Input *txt_Job;
extern Fl_Input *txt_Date;
extern Fl_Choice *lst_JambMaterial;
extern Fl_Choice *lst_JambSize;
extern Fl_Input *txt_CustomRipSize;
extern Fl_Input *txt_Notes;
#include <FL/Fl_Check_Button.H>
extern void cb_update(Fl_Check_Button*, void*);
extern Fl_Check_Button *chk_NoBrickmold;
extern Fl_Check_Button *chk_DeadBolt;
extern Fl_Check_Button *chk_DentilShelf;
extern Fl_Check_Button *chk_OutswingSill;
extern Fl_Check_Button *chk_ADASill;
extern Fl_Check_Button *chk_SpringHinge;
extern Fl_Check_Button *chk_CutDown;
extern Fl_Value_Output *opt_Cost;
#include <FL/Fl_Value_Input.H>
extern void cb_update(Fl_Value_Input*, void*);
extern Fl_Value_Input *val_Markup;
extern Fl_Value_Input *val_LaborCost;
extern Fl_Value_Input *val_Taxes;
extern Fl_Value_Input *val_Total;
#include <FL/Fl_Button.H>
extern void cb_PrintClicked(Fl_Button*, void*);
extern void cb_CancelClicked(Fl_Button*, void*);
Fl_Double_Window* make_door_info_dialog();
extern Fl_Group *grp_PrintGroup;
extern Fl_Box *opt_Customer;
extern Fl_Box *opt_Job;
extern Fl_Box *opt_Date;
extern Fl_Box *box_Print_DoorImage;
extern Fl_Box *opt_Print_LocationName;
extern Fl_Box *opt_Print_DoorSize;
extern Fl_Box *opt_Print_DoorMaterial;
extern Fl_Box *opt_Print_DoorStyle;
extern Fl_Box *opt_Print_DoorSwing;
extern Fl_Box *opt_Print_DoorDesign;
extern Fl_Box *opt_Print_JambSize;
extern Fl_Box *opt_Print_JambMaterial;
extern Fl_Box *opt_Print_Sill;
extern Fl_Box *opt_Print_GlassStyle;
extern Fl_Box *opt_Print_HingeColor;
extern Fl_Box *opt_Print_Price;
extern Fl_Box *opt_Print_Notes;
extern Fl_Box *opt_CompanyInfo;
extern Fl_Box *label_other;
extern Fl_Box *opt_Print_NetFrame;
extern Fl_Box *opt_Print_RoughOpening;
extern Fl_Box *img_Print_swing;
extern Fl_Box *opt_Print_Swing;
extern Fl_Box *opt_Print_Brickmould;
extern Fl_Box *opt_Print_DeadBolt;
extern void cb_Preview_PrintClicked(Fl_Button*, void*);
extern void cb_Preview_CancelClicked(Fl_Button*, void*);
extern void cb_Preview_MakePDFClicked(Fl_Button*, void*);
Fl_Double_Window* make_print_dialog();
void infoDialogReady(); 
#endif

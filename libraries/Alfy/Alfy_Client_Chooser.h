#ifndef CLIENT_CHOOSER_H
#define CLIENT_CHOOSER_H

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>

#include <Alfy/Alfy_Table.h>
#include <Alfy/Alfy_Phone_Input.h>
#include <Alfy/Alfy_Database_Template.h>
#include <Alfy/Alfy_Client.h>
#include <Alfy/Alfy_Strings.h>

class Alfy_Client_Chooser : public Fl_Double_Window
{
    Fl_Input* ipt_first;
    Fl_Input* ipt_last;
    Alfy_Phone_Input* ipt_phone;
    Fl_Button* btn_create;
    Alfy_Table* bsr_clients;

    Alfy_Database<Alfy_Client>* data;

    int _clientID;

    inline static void cb_ipt(Fl_Input* i, void* v)     { ((Alfy_Client_Chooser*)(i->parent()->user_data()))->cb_ipt_Change(i,v); }
    void cb_ipt_Change(Fl_Input* i, void* v);

    inline static void cb_Create(Fl_Button* i, void* v) {((Alfy_Client_Chooser*)(i->parent()->user_data()))->cb_Create_Click(i,v);}
    void cb_Create_Click(Fl_Button* i, void* v);

    inline static void cb_bsr(Alfy_Table* t, void* v)   { if(t->callback_context() == Fl_Table_Row::CONTEXT_CELL) ((Alfy_Client_Chooser*)(t->parent()))->cb_bsr_choose(t,v);}
    void cb_bsr_choose(Alfy_Table* t, void* v);

    void updateBrowser();
public:
    Alfy_Client_Chooser(int X, int Y);

    void setDatabase(Alfy_Database<Alfy_Client>& database)     { data = &database; updateBrowser();}

    int clientID()          { return _clientID; }
    void clientID(int ID)   { _clientID = ID;   }
};

#endif

//All of the under the hood stuff goes here. You have access to
//all widgets that are named. (see fltkgui.h)
#include "functions.h"
#include <FL/FL_JPEG_IMAGE.H>

const string TABLE_PRICE_LIST = "price_list";

void set_door_swing(bool single)
{
    if(single)
    {
        lst_DoorSwing->add("LHSI",0,cb_swing,0);
        lst_DoorSwing->add("LHSO",0,cb_swing,0);
        lst_DoorSwing->add("RHSI",0,cb_swing,0);
        lst_DoorSwing->add("RHSO",0,cb_swing,0);
    }
    else
    {
        lst_DoorSwing->add("_Both Operate",0,0,0,FL_MENU_INACTIVE);
        lst_DoorSwing->add("RHASI",0,cb_swing,0);
        lst_DoorSwing->add("RHASO",0,cb_swing,0);
        lst_DoorSwing->add("LHASI",0,cb_swing,0);
        lst_DoorSwing->add("_LHASO",0,cb_swing,0);
        lst_DoorSwing->add("_Left Stationary",0,0,0,FL_MENU_INACTIVE);
        lst_DoorSwing->add("Left LHSI",0,cb_swing,0);
        lst_DoorSwing->add("Left LHSO",0,cb_swing,0);
        lst_DoorSwing->add("Left RHSI",0,cb_swing,0);
        lst_DoorSwing->add("_Left RHSO",0,cb_swing,0);
        lst_DoorSwing->add("_Right Stationary",0,0,0,FL_MENU_INACTIVE);
        lst_DoorSwing->add("Right LHSI",0,cb_swing,0);
        lst_DoorSwing->add("Right LHSO",0,cb_swing,0);
        lst_DoorSwing->add("Right RHSI",0,cb_swing,0);
        lst_DoorSwing->add("Right RHSO",0,cb_swing,0);
    }
}

//run some SQL commands to read from the pice list and find the options
// for the lists
void set_lists()
{
	char *zErrMsg = 0;          //error variables
	int rc;
	string pSQL;                //SQL string to be executed
	sqlite3 *db = wnd_main->db; //database pointer

	pSQL = "SELECT * FROM " + TABLE_PRICE_LIST +
            "WHERE list = 'JAMB_MATERIAL'";

            //TODO finish this tomarrow

    // run the SQL command and check for errors
	if( SQLITE_OK != sqlite3_exec(db, pSQL.c_str(), db_callback, 0, &zErrMsg) )
	{
		//outputs the error message for testing
		cout << endl << zErrMsg << endl;
		//free the error
		sqlite3_free(zErrMsg);
	}
}

//sets the Jamb size list depending on the Jamb Material
void set_jamb_size()
{
    if(lst_JambMaterial->text())
    {
        string jamb = lst_JambMaterial->text();

        //clear the list
        lst_JambSize->clear();

        if(jamb == "Primed")
        {
            lst_JambSize->add("4-9\\/16 - 5-1\\/4",0,cb_update,0);
            lst_JambSize->add("5-3\\/8 - 6-9\\/16",0,cb_update,0);
            lst_JambSize->add("6-5\\/8 - 7-1\\/4",0,cb_update,0);
            lst_JambSize->add("7-3\\/8 - 9-1\\/2",0,cb_update,0);
        }
        else if(jamb == "Oak")
        {
            lst_JambSize->add("4-9\\/16",0,cb_update,0);
            lst_JambSize->add("6-9\\/16",0,cb_update,0);
            lst_JambSize->add("4-9\\/16 8'0\"",0,cb_update,0);
            lst_JambSize->add("6-9\\/16 8'0\"",0,cb_update,0);
        }
        else if(jamb == "Knotty Alder")
        {
            lst_JambSize->add("4-9\\/16",0,cb_update,0);
            lst_JambSize->add("6-9\\/16",0,cb_update,0);
        }
        else if(jamb == "Solid Pine")
        {
            lst_JambSize->add("4-9\\/16",0,cb_update,0);
            lst_JambSize->add("6-9\\/16",0,cb_update,0);
        }
        else if(jamb == "Composite")
        {
            lst_JambSize->add("4-9\\/16",0,cb_update,0);
            lst_JambSize->add("6-9\\/16",0,cb_update,0);
        }

    }
    lst_JambSize->redraw();
}

//runs an SQL statement and watches for an error
void runSQL(sqlite3 *db, const char *pSQL)
{
    //error variables
	char *zErrMsg = 0;
	int rc;

    //execute the SQL
	rc = sqlite3_exec(db, pSQL, db_callback, 0, &zErrMsg);

	//if an error occurs
	if( rc!=SQLITE_OK )
	{
		//outputs the error message for testing
		cout << endl << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}

void price_calc()
{

}

//opens the database and checks for errors
void openDatabase(sqlite3 *db, string name)
{
    char *zErrMsg = 0;
	int rc;

	// Open the test.db file
	rc = sqlite3_open(name.c_str(), &db);

	if( rc ){
		// failed
		cout << "Can't open database: " << stderr << " " << sqlite3_errmsg(db);
		//fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	}
	else
	{
		// success
		fprintf(stderr, "Open database successfully\n\n");
	}
}

void infoDialogReady()
{

}

//prints a pdf or straight to printer of a groupbox and its contents. The pdf printing requires ghostscript to be installed. Google it.
void printGroupBox(Fl_Group* grouptoprint, bool printpdf)
{

    int w, h;
    float scale_tmp, scale;

    if (printpdf)
    {

        FILE *fp = fopen ( "printfile.ps", "w" );

        Fl_PostScript_File_Device ps_device;

        ps_device.start_job(fp,1);

        //postscript generation
        ps_device.set_current();
        ps_device.start_page();
        //if( ps_device.start_page() ) break;
        w = h = 0;
        ps_device.printable_rect(&w,&h);
        // scale the printer device so that the window fits on the page
        scale = 1;
        if (grouptoprint->w() > w || grouptoprint->h() > h)
        {
            scale = (float)w/grouptoprint->w();
            scale_tmp = (float)h/grouptoprint->h();
            if ( scale_tmp < scale) scale = scale_tmp;
            ps_device.scale(scale, scale);
        }
        ps_device.print_widget(grouptoprint);
        ps_device.end_page();
        ps_device.end_job();

        //create the pdf. The complicatedness is to account for windows 7 being a different path. 1 is returned on error,
        //0 on success. See what I did here?
        if (system("C:\\Progra~1\\gs\\gs9.05\\bin\\gswin32c -sDEVICE=pdfwrite -sOutputFile=Invoice.pdf -dBATCH -dNOPAUSE printfile.ps")==1)
            std::cout << endl << system("\"C:\\Program Files (x86)\\gs\\gs9.05\\bin\\gswin32c\" -sDEVICE=pdfwrite -sOutputFile=Invoice.pdf -dBATCH -dNOPAUSE printfile.ps");

        //show the pdf
        system("start acrord32.exe Invoice.pdf");
        //system("DEL printfile.ps");
    }
    else
    {
        Fl_Printer printer;
        printer.start_job(1);
        //Printer
        printer.set_current();
        printer.start_page();
        //if( printer.start_page() ) break;
        w = h = 0;
        printer.printable_rect(&w,&h);

        // scale the printer device so that the window fits on the page
        scale = 1;
        if (grouptoprint->w() > w || grouptoprint->h() > h)
        {
            scale = (float)w/grouptoprint->w();
            scale_tmp = (float)h/grouptoprint->h();
            if ( scale_tmp < scale) scale = scale_tmp;
            printer.scale(scale, scale);
        }
        printer.print_widget(grouptoprint);
        printer.end_page();
        printer.end_job();
    }
}

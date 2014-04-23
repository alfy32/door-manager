//All of the under the hood stuff goes here. You have access to
//all widgets that are named. (see fltkgui.h)
#include "functions.h"
#include <FL/FL_JPEG_IMAGE.H>

const string TABLE_PRICE_LIST = "price_list";

void set_door_swing(bool single)
{
    string sql;

    if(single)
    {
        wnd_main->db.runSQL(sql+"SELECT label FROM PriceList " +
                        "WHERE list = 'DOOR_SWING_SINGLE'",
                        db_callback_lst_door_swing);
    }
    else
    {
        wnd_main->db.runSQL(sql+"SELECT label,type FROM PriceList " +
                        "WHERE list = 'DOOR_SWING_DOUBLE'",
                        db_callback_lst_door_swing);
    }
}

//sets the Jamb size list depending on the Jamb Material
void set_jamb_size()
{
    lst_JambSize->clear();

    if(lst_JambMaterial->text())
    {
        string sql = "SELECT label FROM PriceList ";
        sql = sql + "WHERE list = 'JAMB_MATERIAL' " +
                    "AND type = '" + lst_JambMaterial->text() + "'";

        //output for testing
        //cout << "JAMB MATERIAL: " << lst_JambMaterial->text() << endl;
        //cout << sql << endl;

        wnd_main->db.runSQL(sql,
                        db_callback_lst_jamb_size);
    }
}

string fix_jamb_size(string source)
{
    string fixed = "";

    for(int i = 0; i < source.length(); i++)
    {
        if(source[i] == '/')
            fixed += "\\/";
        else
            fixed += source[i];
    }
    return fixed;
}

// Replaces any ' with ''
string sql_replace_single_quote(string source)
{
	string fixed = "";
	int size = source.length();

	for(int i = 0; i < size; i++)
	{
		if(source[i] == '\'')
			fixed += "''";
		else
			fixed += source[i];
	}
	return fixed;
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

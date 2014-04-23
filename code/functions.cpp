//All of the under the hood stuff goes here. You have access to
//all widgets that are named. (see fltkgui.h)
#include "functions.h"
#include <FL/FL_JPEG_IMAGE.H>

int posx = 0, posy = 0;

void restartDoors()
{
    posx = posy = 0;
}

//adds a door to the scrollview
void addDoor(Door door)
{
    if(posx == 0)
        posx = grp_DoorGrid->x();

    int gridWidth = grp_DoorGrid->w() - 20;
    int cols = gridWidth/250;
    int width = gridWidth/cols;

    Fl_JPEG_Image *img;
    Fl_Button *o = new Fl_Button(posx, posy, width, 310, "button");
    o->box(FL_NO_BOX);
    o->callback((Fl_Callback*)cb_door_click, (void*)new Door(door));

    posx += o->w();
    if(posx > (grp_DoorGrid->x() + gridWidth - width))
    {
        posx = 0;
        posy += o->h();
    }

    string picture = "doors\\";
    picture += door.style();
    picture += ".jpg";
    img = new Fl_JPEG_Image(picture.c_str());

    o->image(img->copy(72,160));

    string label = "Style:";
    label += door.style();
    label += " \nMaterial: ";
    label += door.material();
    label += " \nDesign: ";
    label += door.design();
    label += " \nGlass: ";
    label += door.glass_style();

    o->copy_label(label.c_str());

    scroll_DoorGrid->add(o);
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
	if( rc!=SQLITE_OK ){
		sqlite3_free(zErrMsg);
		//outputs the error message for testing
		cout << endl << zErrMsg << endl;
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
    opt_Design->value(door.design().c_str());
    opt_DoorMaterial->value(door.material().c_str());
    opt_DoorStyle->value(door.style().c_str());
    opt_GlassStyle->value(door.glass_style().c_str());

    get_sizes(door.style());
    string price = "SELECT * FROM prices WHERE style == '";
    price += door.style();
    price += "'";

    char *zErrMsg = 0;
	int rc;
	sqlite3 *db = (sqlite3*)wnd_main->user_data();

    //execute the SQL
	rc = sqlite3_exec(db, price.c_str(), db_callback_price, 0, &zErrMsg);

	//if an error occurs
	if( rc!=SQLITE_OK ){
		sqlite3_free(zErrMsg);
		//outputs the error message for testing
		cout << endl << zErrMsg << endl;
	}

	lst_DoorSize->value(0);

    lst_DoorSwing->add("LHSI",0,cb_swing,0);
    lst_DoorSwing->add("LHSO",0,cb_swing,0);
    lst_DoorSwing->add("RHSI",0,cb_swing,0);
    lst_DoorSwing->add("RHSO",0,cb_swing,0);

    lst_JambSize->add("4-9\\/16 - 5-1\\/4",0,cb_update,0);
    lst_JambSize->add("5-3\\/8  - 6-9\\/16",0,cb_update,0);
    lst_JambSize->add("6-5\\/8  - 7-1\\/4",0,cb_update,0);
    lst_JambSize->add("7-3\\/8  - 9-1\\/2",0,cb_update,0);

    lst_JambMaterial->add("Primed",0,cb_update,0);
    lst_JambMaterial->add("Oak",0,cb_update,0);
    lst_JambMaterial->add("Knotty Alder",0,cb_update,0);
    lst_JambMaterial->add("Solid Pine",0,cb_update,0);
    lst_JambMaterial->add("White Clad",0,cb_update,0);

    lst_Sill->add("Mill",0,cb_update,0);
    lst_Sill->add("Bronze",0,cb_update,0);
    lst_Sill->add("Brass",0,cb_update,0);
    lst_Sill->add("Oak",0,cb_update,0);
}

void get_sizes(string style)
{
    char *zErrMsg = 0;
	int rc;
	sqlite3 *db = (sqlite3*)wnd_main->user_data();

 	style = "SELECT * FROM sizes WHERE style == '" + style + "' OR style == 'sizes'";

    //execute the SQL
	rc = sqlite3_exec(db, style.c_str(), db_callback_size, 0, &zErrMsg);

	//if an error occurs
	if( rc!=SQLITE_OK ){
		sqlite3_free(zErrMsg);
		//outputs the error message for testing
		cout << endl << zErrMsg << endl;
	}
}

float string_to_float(const char number[])
{
    bool negative = false;

    int decimalIndex = 0;

    if(number[0] == '-')
    {
        decimalIndex = 1;
        negative = true;
    }

    while(number[decimalIndex] != '.')
    {
        if(number[decimalIndex] == 0)
        {
            decimalIndex = 0;
            break;
        }
        decimalIndex++;
    }

    int nullIndex = decimalIndex;

    while(number[nullIndex] != 0)
        nullIndex++;

    int num = 0;
    float decimal = 0;
    int start = 0;

    if(negative)
        start = 1;

    if(decimalIndex == 0)
    {
        if(number[0] == '.')
        {
            for(int x = 1; x < nullIndex; x++)
            {
                decimal += (number[x] - 48);
                decimal /= 10;
            }
        }
        else
        {
            for(int x = 0; x < nullIndex; x++)
            {
                num *= 10;
                num += number[x] - 48;
            }

        }
    }
    else
    {
        for(int x = start; x < decimalIndex; x++)
        {
            num *= 10;
            num += number[x] - 48;
        }

        for(int x = nullIndex - 1; x > decimalIndex; x--)
        {
            decimal += (number[x] - 48);
            decimal /= 10;
        }
    }
    if(negative)
        return 0 - (decimal + num);
    else
        return decimal + num;
}

string double_to_string(double number)
{
    std::string negative = "";

    if(number < 0)
    {
        negative = "-";
        number = -number;
    }

    int temp,
        digits = 3;

    for(int x = 20; x >= 0; x--)
    {
        //make temp equal to 10 to the x power
        temp = 1;
        for(int y = 0; y < x; y++)
            temp *= 10;

        if((int)number/temp != 0)
        {
            digits += x;
            break;
        }
    }

    char num[digits+2];

    num[digits+1] = 0;                                  //sets the null character toterminte the string
    num[digits]   = ((int)((number+.001)*100)%10) + 48; //sets the hundredths
    num[digits-1] = ((int)((number+.001)*10)%10) + 48;  //sets the tenths
    num[digits-2] = '.';                                //sets the decimal point

    //sets all the rest of the numbers
    for(int x = 0; x < digits-2; x++)
    {
        //make temp equal to 10 to the x power
        temp = 1;
        for(int y = 0; y < x; y++)
            temp *= 10;

        //adds one digit at a time
        num[digits-3-x] = ((int)(number/temp)%10) + 48;
    }

    return negative + num;
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

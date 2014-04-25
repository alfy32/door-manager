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

//reads all of the doors from a csv file
void csvToSQL(sqlite3 *db, string fileName)
{
    //open the file
    ifstream file(fileName.c_str());

    runSQL((sqlite3*)wnd_main->user_data(),"CREATE TABLE doors (door_style TEXT, material TEXT, design TEXT, glass_style TEXT)");

    //check if the file is good
	if(file)
	{
	    //read the column headers from the file
		Door::readDoor(file);

        //read the first door from the file
		Door door = Door::readDoor(file);

        //loop until the end of the file is reached
		while(!file.eof())
		{
		    //call the doorToSQL function to convert the door into and SQL statement
		    //run the insert statement
			runSQL(db, Door::doorToSQL(door).c_str());

            //read the next door
			door = Door::readDoor(file);
		}
		//close the file
		file.close();
	}
	else
        //for if the file didn't exits output a fail message
		cout << "Fail: csv file does not exist.";
}

//reads a line from the csv for the prices
int read_line_price(ifstream &file, string text[])
{
	int count = 0;
	char ch = file.get();

	if(file.eof())
        return 0;
	do
	{
		if(ch == ',')
		{
			count++;
		}
		else
			text[count] += ch;

		ch = file.get();
	}
	while(ch != '\n');

	return count + 1;
}

//creates the SQL string to insert the prices from the csv
string insertSQL_price(ifstream &file)
{
	string sql = "INSERT INTO price VALUES ('";
	string line[20];

	int size = read_line_price(file,line);

	sql += line[0];
	sql += "'";

	for(int i = 1; i < size; i++)
	{
		sql += ", '";
		sql += line[i];
		sql += "'";

	}

	sql += ")";

	return sql;
}

//creates the price table for the doors.
void create_table_price(ifstream &file)
{
	string sql = "CREATE TABLE price (";
	string text[20];

	int size = read_line_price(file,text);

	sql += text[0];
	sql += " TEXT";

	for(int i = 1; i < size; i++)
	{
		sql += ", ";
		sql += text[i];
		sql += " TEXT";

	}

	sql += ")";

	runSQL((sqlite3*)(wnd_main->user_data()), sql.c_str());
}

//reads the csv for the prices of the doors.
void read_price_csv()
{
    string sql;
    ifstream file(FILE_PRICE);

    create_table_price(file);

    sql = insertSQL_price(file);

    while(!file.eof())
    {
        cout << sql << endl;
        runSQL((sqlite3*)(wnd_main->user_data()), sql.c_str());

        sql = insertSQL_price(file);
    }
}

//reads a line from the csv for the prices
int read_line_size(ifstream &file, string text[])
{
	int count = 0;
	char ch = file.get();

	if(file.eof())
        return 0;
	do
	{
		if(ch == ',')
		{
			count++;
		}
		else
			text[count] += ch;

		ch = file.get();
	}
	while(ch != '\n');

	return count + 1;
}

//creates the SQL string to insert the prices from the csv
string insertSQL_size(ifstream &file)
{
	string sql = "INSERT INTO size VALUES ('";
	string line[20];

	int size = read_line_size(file,line);

	sql += line[0];
	sql += "'";

	for(int i = 1; i < size; i++)
	{
		sql += ", '";
		sql += line[i];
		sql += "'";

	}

	sql += ")";

	return sql;
}

//creates the price table for the doors.
void create_table_size(ifstream &file)
{
	string sql = "CREATE TABLE size (";
	string text[20];

	int size = read_line_size(file,text);

	sql += text[0];
	sql += " TEXT";

	for(int i = 1; i < size; i++)
	{
		sql += ", ";
		sql += text[i];
		sql += " TEXT";

	}

	sql += ")";

	runSQL((sqlite3*)(wnd_main->user_data()), sql.c_str());
}

//reads the csv for the prices of the doors.
void read_size_csv()
{
    string sql;
    ifstream file(FILE_SIZE);

    create_table_size(file);

    sql = insertSQL_size(file);

    while(!file.eof())
    {
        cout << sql << endl;
        runSQL((sqlite3*)(wnd_main->user_data()), sql.c_str());

        sql = insertSQL_size(file);
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
    string price = "SELECT * FROM price WHERE style == '";
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


    lst_DoorSwing->add("_Single Door");
    lst_DoorSwing->add("LHSI",0,cb_swing,0);
    lst_DoorSwing->add("LHSO",0,cb_swing,0);
    lst_DoorSwing->add("RHSI",0,cb_swing,0);
    lst_DoorSwing->add("_RHSO",0,cb_swing,0);
    lst_DoorSwing->add("_Double Door");
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

    lst_JambSize->add("4 9 16ths - 5 fourth",0,cb_jamb_size,0);
    lst_JambSize->add("5 3 8ths  - 6 9 16ths",0,cb_jamb_size,0);
    lst_JambSize->add("6 5 8ths  - 7 fourth",0,cb_jamb_size,0);
    lst_JambSize->add("7 3 8ths  - 9 half",0,cb_jamb_size,0);

    lst_JambMaterial->add("Primed",0,cb_jamb_material,0);
    lst_JambMaterial->add("Oak",0,cb_jamb_material,0);
    lst_JambMaterial->add("Knotty Alder",0,cb_jamb_material,0);
    lst_JambMaterial->add("Solid Pine",0,cb_jamb_material,0);
    lst_JambMaterial->add("White Clad",0,cb_jamb_material,0);

    lst_Sill->add("Mill",0,cb_sill,0);
    lst_Sill->add("Bronze",0,cb_sill,0);
    lst_Sill->add("Brass",0,cb_sill,0);
    lst_Sill->add("Oak",0,cb_sill,0);
}

void get_sizes(string style)
{
    char *zErrMsg = 0;
	int rc;
	sqlite3 *db = (sqlite3*)wnd_main->user_data();

 	style = "SELECT * FROM size WHERE style == '" + style + "' OR style == 'sizes'";

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

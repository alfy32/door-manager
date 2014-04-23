#include "Door_Size_Chooser.h"

//to make the static functions for the database work
Door_Size_Chooser* Door_Size_Chooser::me = 0;

const string TABLE_SIZES = "sizes";
const string TABLE_PRICES = "prices";
const string STYLE_COLUMN_NAME = "style";
const string MAX_SIZE_SINGLE_DOOR = "4'";

//uses the default constructor of Fl_Chooser
Door_Size_Chooser::Door_Size_Chooser(int X, int Y, int W, int H, const char * L)
:Fl_Choice(X,Y,W,H,L)
{
    me = this;
}

//sets up the menu given a door style
int Door_Size_Chooser::set_door_style(sqlite3 *database, string style_)
{
    //sets the database pointer
    db = database;

    //sets the style of the door
    style = style_;

    get_sizes();
    get_prices();
    get_available();

    fill_menu();
}

double Door_Size_Chooser::get_price()
{
    if(DoorSize(text()).getWidth() < MAX_SIZE_SINGLE_DOOR)
        return price_single;
    else
        return price_double;
}

//gets the sizes from the SQL
void Door_Size_Chooser::get_sizes()
{
    //error variables for SQL commands
	char *zErrMsg = 0;
	int rc;

    //prepares the SQL statement
	string pSQL = "SELECT * FROM " + TABLE_SIZES + " WHERE " +
                 STYLE_COLUMN_NAME + " = 'sizes'";

    //execute the SQL
	rc = sqlite3_exec(db, pSQL.c_str(), load_sizes_sql_stat, 0, &zErrMsg);

	//if an error occurs
	if( rc!=SQLITE_OK )
	{
	    //outputs the error message for testing
		cout << endl << zErrMsg << endl;

		sqlite3_free(zErrMsg);
	}
}

//gets the prices from the SQL
void Door_Size_Chooser::get_prices()
{
    //error variables for SQL commands
	char *zErrMsg = 0;
	int rc;

    //prepare the SQL statement to get the sizes
    string pSQL = "SELECT * FROM " + TABLE_PRICES + " WHERE " +
                 STYLE_COLUMN_NAME + " = '" + style + "'";

    //execute the SQL
	rc = sqlite3_exec(db, pSQL.c_str(), load_prices_sql_stat, 0, &zErrMsg);

	//if an error occurs
	if( rc!=SQLITE_OK )
	{
	    //outputs the error message for testing
		cout << endl << zErrMsg << endl;

		sqlite3_free(zErrMsg);
	}
}

//gets the available from the SQL
void Door_Size_Chooser::get_available()
{
    //error variables for SQL commands
	char *zErrMsg = 0;
	int rc;

    //prepare the SQL statement to get the sizes
    string pSQL = "SELECT * FROM " + TABLE_SIZES + " WHERE " +
                 STYLE_COLUMN_NAME + " = '" + style + "'";

    //execute the SQL
	rc = sqlite3_exec(db, pSQL.c_str(), load_available_sql_stat, 0, &zErrMsg);

	//if an error occurs
	if( rc!=SQLITE_OK )
	{
	    //outputs the error message for testing
		cout << endl << zErrMsg << endl;

		sqlite3_free(zErrMsg);
	}
}

void Door_Size_Chooser::fill_menu()
{
    for(int i = 0; i < sizes.size(); i++)
    {
        if(available.at(i))
            add(sizes[i].toString().c_str(),0,cb_Door_Size_Chooser,(void*)i);
    }
}

//converts from the index of the menu item to the index of the data
//counts the available sizes up to the index given and returns the count.
int Door_Size_Chooser::index_converter(int index)
{
    int count = 0;
    int i;

    for(i = 0; i < available.size() && count < index; i++)
    {
        if(available[i])
            count++;
    }

    return i;
}

//SQL callback to get the actual sizes possible
int Door_Size_Chooser::load_sizes_sql(void *NotUsed, int col, char **values, char **colName)
{
    sizes.clear();

    for(int i = 1; i < col; i++)
    {
        //output for testing
        //cout << colName[i] << ": " << values[i] << endl;

        //add each size to the vector
        sizes.push_back(DoorSize(values[i]));
    }
}

//SQL callback to get the single and double door prices
int Door_Size_Chooser::load_prices_sql(void *NotUsed, int col, char **values, char **colName)
{
    //clear the prices
    price_single = price_double = 0;

    //set the single and double prices
    if(values[1])
        price_single = string_to_float(values[1]);
    if(values[2])
        price_double = string_to_float(values[2]);

    //output for testing
    //for(int i = 0; i < col; i++)
    //{
    //    cout << colName[i] << ": " << values[i] << endl;
    //}
}

//SQL callback for which doors are available
int Door_Size_Chooser::load_available_sql(void *NotUsed, int col, char **values, char **colName)
{
    available.clear();
    bool avail;

    for(int i = 1; i < col; i++)
    {
        //output for testing
        //cout << colName[i] << ": " << values[i] << endl;

        //add each size to the vector
        if(values[i])
        {
            if(values[i][0] == '1')
                available.push_back(true);
            else
                available.push_back(false);
        }
    }
}

//converts a string to a float
float Door_Size_Chooser::string_to_float(const char number[])
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


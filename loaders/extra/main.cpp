#include <iostream>
#include "sqlite3.h"

using namespace std;

void runSQL(sqlite3 *db, const char *pSQL);
void csvToSQL(sqlite3 *db, string fileName);
void openDatabase(sqlite3 *db, string name);
void read_price_csv();
void read_size_csv();

int maina()
{


	return 0;
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
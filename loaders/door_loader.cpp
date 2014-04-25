#include <iostream>
#include <fstream>
#include <string>
#include "sqlite3.h"

using namespace std;

//global constants
const char DB_DOOR[] = "doors.db";
const char FILE_DOOR[] = "doors.csv";

//door structure
struct Door
{
	string style;
	string material;
	string design;
	string glass;
};

//function prototypes
void runSQL(sqlite3 *db, const char *pSQL);
Door read_door(ifstream &in);
string doorToSQL(Door door);
int db_callback(void *NotUsed, int col, char **values, char **colName);

int main()
{
	ifstream file(FILE_DOOR);	//csv file
	sqlite3 * db;				//database structure
	char *zErrMsg = 0;			//error variables
	int rc;

	// Open the test.db file
	rc = sqlite3_open(DB_DOOR, &db);

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

	runSQL(db, "DROP TABLE doors");

	runSQL(db, "CREATE TABLE doors (style TEXT, material TEXT, design TEXT, glass TEXT)");


	//begin read file
	if(!file)
		//for if the file didn't exits output a fail message
		cout << "Fail: csv file does not exist.";
	else
	{
		Door door;

		//read the column headers from the file
		read_door(file);

		//read the first door from the file
		door = read_door(file);
	
        //loop until the end of the file is reached
		while(!file.eof())
		{
		    //call the doorToSQL function to convert the door into and SQL statement
		    //run the insert statement
			runSQL(db, doorToSQL(door).c_str());

            //read the next door
			door = read_door(file);
		}
		//close the file
		file.close();
	}  

	//output everything for testing
	runSQL(db, "SELECT * FROM doors");

	sqlite3_close(db);

	system("pause");

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

//read a door from the csv
Door read_door(ifstream &in)
{
	char text[80];
	Door door;

	in.getline(text,80,',');
	door.style = text;

	in.getline(text,80,',');
	door.material = text;

	in.getline(text,80,',');
	door.design = text;

	in.getline(text,80,'\n');
	door.glass = text;

	return door;
}

//convert the door info into an sql string
string doorToSQL(Door door)
{
    string statement =	"INSERT INTO doors VALUES ('"; 
	statement += door.style; 
	statement += "','";
	statement += door.material;
	statement += "','";
	statement += door.design;
	statement += "','";
	statement += door.glass;
	statement += "')";

	//output for testing
	cout << statement << endl;

    return statement;
}

// This is the callback function to display the select data in the table
// it is called for ever row taken from the table
int db_callback(void *NotUsed, int col, char **values, char **colName)
{
    //output the database for testing purposes
    int i;
    for(i=0; i<col; i++)
    {
        cout << colName[i] << ": " << values[i] << endl;

    }
    cout << endl;

	return 0;
}
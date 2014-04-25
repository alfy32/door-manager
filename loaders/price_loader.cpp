#include <iostream>
#include <fstream>
#include <string>
#include "sqlite3.h"

using namespace std;

struct Price
{
	string style;
	string single_;
	string double_;
};

//global constants
const char DB_DOOR[] = "doors.db";
const char FILE_PRICE[] = "prices.csv";

//function prototypes
Price read_line(ifstream &file);
void create_table_price(ifstream &file);
string insert_SQL_price(Price price);
void runSQL(sqlite3 *db, const char *pSQL);
int db_callback(void *NotUsed, int col, char **values, char **colName);

int main()
{
	ifstream file(FILE_PRICE);	//csv file
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

	runSQL(db, "DROP TABLE prices");

	runSQL(db, "CREATE TABLE prices (style TEXT, single TEXT, double TEXT)");


	//begin read file
	if(!file)
		//for if the file didn't exits output a fail message
		cout << "Fail: csv file does not exist.";
	else
	{
		Price price;

		//read the column headers from the file
		read_line(file);

		//read the first door from the file
		price = read_line(file);
	
        //loop until the end of the file is reached
		while(!file.eof())
		{
		    //call the doorToSQL function to convert the door into and SQL statement
		    //run the insert statement
			runSQL(db, insert_SQL_price(price).c_str());

            //read the next door
			price = read_line(file);
		}
		//close the file
		file.close();
	}  

	//output everything for testing
	runSQL(db, "SELECT * FROM prices");

	system("pause");

	return 0;
}

//reads a line from the csv for the prices
Price read_line(ifstream &in)
{
	char text[80];
	Price price;

	in.getline(text,80,',');
	price.style = text;

	in.getline(text,80,',');
	price.single_ = text;

	in.getline(text,80,'\n');
	price.double_= text;

	return price;
}

//creates the SQL string to insert the prices from the csv
string insert_SQL_price(Price price)
{
	//start the sql insert statement
	string sql = "INSERT INTO prices VALUES ('";

	sql += price.style;
	sql += "','";
	sql += price.single_;
	sql += "','";
	sql += price.double_;
	sql += "')";

	cout << sql << endl;

	return sql;
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
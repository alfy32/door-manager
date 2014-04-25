#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "sqlite3.h"

using namespace std;

//global constants
const char DB_DOOR[] = "doors.db";
const char FILE_SIZE[] = "sizes.csv";

//function prototypes
int read_line_size(ifstream &file, string text[]);
string insertSQL_size(ifstream &file);
string create_table_size(ifstream &file);
void runSQL(sqlite3 *db, const char *pSQL);
int db_callback(void *NotUsed, int col, char **values, char **colName);

int main()
{
	ifstream file(FILE_SIZE);	//csv file
	sqlite3 * db;				//database structure
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

	runSQL(db, "DROP TABLE sizes");

	string sql;

    runSQL(db, create_table_size(file).c_str());

    sql = insertSQL_size(file);

    while(!file.eof())
    {
        cout << sql << endl;
        runSQL(db, sql.c_str());

        sql = insertSQL_size(file);
    }

	runSQL(db, "SELECT * FROM sizes");

	system("pause");

	return 0;
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
	string sql = "INSERT INTO sizes VALUES ('";
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
string create_table_size(ifstream &file)
{
	string sql = "CREATE TABLE sizes (";
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

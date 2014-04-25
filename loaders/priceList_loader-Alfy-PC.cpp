#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "sqlite3.h"

using namespace std;

//global constants
const char DB_DOOR[] = "doors.db";
const char FILE_PRICELIST[] = "PriceList.csv";
const string TABLE_NAME = "pricelist";
const int MAX_COLS = 20;

//function prototypes
string create_table(ifstream &file);
int read_line(ifstream &file, string text[]);
string insertSQL(ifstream &file);
void runSQL(sqlite3 *db, const char *pSQL);
int db_callback(void *NotUsed, int col, char **values, char **colName);

int main()
{
	ifstream file(FILE_PRICELIST);	//csv file
	sqlite3 * db;					//database structure
	string sql;

	// Open the test.db file
	if( sqlite3_open(DB_DOOR, &db) )
		cout << "Can't open database: " << stderr << " " << sqlite3_errmsg(db);
	else
		cout << "Open database successfully\n\n";

	//drop the old table
	sql = "DROP TABLE " + TABLE_NAME;
	runSQL(db, sql.c_str());

	sql = create_table(file);
	cout << sql << endl;
    runSQL(db, sql.c_str());

    sql = insertSQL(file);

    while(!file.eof())
    {
        cout << sql << endl;
        runSQL(db, sql.c_str());

        sql = insertSQL(file);
    }

	sql = "SELECT * FROM " + TABLE_NAME;
	runSQL(db, sql.c_str());

	system("pause");

	return 0;
}

string create_table(ifstream &file)
{
	string sql = "CREATE TABLE " + TABLE_NAME + " (";
	string text[MAX_COLS];

	int size = read_line(file,text);

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

int read_line(ifstream &file, string text[])
{
	int count = 0;
	char ch = file.get();	//get the first character from the file
	char ch_last = 'a';

	//if the file is empty then quit
	if(file.eof())
        return 0;

	//take each charater one at a time until there is a ,
	//this means get the next word
	//when the \n character is reached we are done
	while(ch != '\n')
	{
		if(ch == ',')
		{
			// Removes opening and closing quotes if they exist 
			int size = text[count].length();
			if(size && text[count][0] == '"' && text[count][size-1] == '"')
				text[count] = string(text[count], 1, size-2);
			
			count++;
		}
		else
		{
			if(ch == '\'')	//replace ' with ''
				text[count] += "''";
			else if(ch == '"' && ch_last == '"' && file.peek() != ','); 
				//do nothing or don't add the second "
			else
				text[count] += ch;
		}
		ch_last = ch;
		ch = file.get();
	}
	

	return count + 1;
}

//creates the SQL string to insert the prices from the csv
string insertSQL(ifstream &file)
{
	string sql = "INSERT INTO " + TABLE_NAME + " VALUES ('";
	string line[MAX_COLS];

	int size = read_line(file,line);

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
		cout << zErrMsg << endl << endl;

		sqlite3_free(zErrMsg);
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
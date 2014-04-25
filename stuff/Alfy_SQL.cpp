#include "Alfy_SQL.h"

// Initailizes the database
Alfy_SQL::Alfy_SQL(string fileName)
{
	_fileName = fileName;
}

// Initializes with a premade sqlite3 structure
Alfy_SQL::Alfy_SQL(string fileName, sqlite3 *db)
{
	_fileName = fileName;
	_db = db;
}

// Opens the database
//  outputs any errors through the command line.
void Alfy_SQL::open()
{
	if(sqlite3_open(_fileName.c_str(), &_db))
		cout << "Can't open database: " << sqlite3_errmsg(_db);
	else
		cout << "Open database successfully\n\n";
}

// Closes the database
//  outputs any errors through the command line.
void Alfy_SQL::close()
{
	sqlite3_close(_db);
}

// Executes the sql statement and outputs any error to the command prompt
//  Uses the default callback: alfy_SQL_db_callback
//  Built for testing and non SELECT statements
void Alfy_SQL::runSQL(const char *pSQL)
{
    //error variables
	char *zErrMsg = 0;

    //if an error occurs
	if( sqlite3_exec(_db, pSQL, alfy_SQL_db_callback, 0, &zErrMsg) != SQLITE_OK )
	{
		//outputs the error message for testing
		cout << zErrMsg << endl << endl;

		sqlite3_free(zErrMsg);
	}
}

// Executes the sql statement and outputs any error to the command prompt
//  Uses the default callback: alfy_SQL_db_callback
//  Built for testing and non SELECT statements
void Alfy_SQL::runSQL(string pSQL)
{
    //error variables
	char *zErrMsg = 0;

    //if an error occurs
	if( sqlite3_exec(_db, pSQL.c_str(), alfy_SQL_db_callback, 0, &zErrMsg) != SQLITE_OK )
	{
		//outputs the error message for testing
		cout << zErrMsg << endl << endl;

		sqlite3_free(zErrMsg);
	}
}

// Executes the sql statement and outputs any error to the command prompt
//  Uses a given callback function
//  Built for SELECT statements
void Alfy_SQL::runSQL(const char *pSQL, 
	int callback(void*, int, char**, char**))
{
    //error variables
	char *zErrMsg = 0;

    //if an error occurs
	if( sqlite3_exec(_db, pSQL, callback, 0, &zErrMsg) != SQLITE_OK )
	{
		//outputs the error message for testing
		cout << zErrMsg << endl << endl;

		sqlite3_free(zErrMsg);
	}
}

// Executes the sql statement and outputs any error to the command prompt
//  Uses a given callback function
//  Built for SELECT statements
void Alfy_SQL::runSQL(string pSQL, 
	int callback(void*, int, char**, char**))
{
    //error variables
	char *zErrMsg = 0;

    //if an error occurs
	if( sqlite3_exec(_db, pSQL.c_str(), callback, 0, &zErrMsg) != SQLITE_OK )
	{
		//outputs the error message for testing
		cout << zErrMsg << endl << endl;

		sqlite3_free(zErrMsg);
	}
}

// Reads the first row of the database and returns
//  the double from the given column.
double Alfy_SQL::getDouble(string pSQL, int col)
{
	sqlite3_stmt *stmt;	// stores the results of the query
	double value;		// stores the double value

	// runs the statement and puts the results in stmt
	if( sqlite3_prepare_v2(_db, pSQL.c_str(), pSQL.length(), &stmt, NULL) )
	{
		// output error message
		cout << "Prepare Error: " << sqlite3_errmsg(_db) << endl;

		//quit and return -1
		return -1;
	}

	// steps to the first row of values
	sqlite3_step(stmt);

	// gets a double value from the given column
	value = sqlite3_column_double(stmt, col);

	// clears the stmt
	sqlite3_finalize(stmt);

	return value;
}

// Reads the first row of the database and returns
//  the integer from the given column.
int Alfy_SQL::getInt(string pSQL, int col)
{
	sqlite3_stmt *stmt;	// stores the results of the query
	int value;			// stores the integer value

	// runs the statement and puts the results in stmt
	if( sqlite3_prepare_v2(_db, pSQL.c_str(), pSQL.length(), &stmt, NULL) )
	{
		// output error message
		cout << "Prepare Error: " << sqlite3_errmsg(_db) << endl;

		//quit and return -1
		return -1;
	}

	// steps to the first row of values
	sqlite3_step(stmt);

	// gets a integer value from the given column
	value = sqlite3_column_int(stmt, col);

	// clears the stmt
	sqlite3_finalize(stmt);

	return value;
}

// Reads the first row of the database and returns
//  the string from the given column.
string Alfy_SQL::getString(string pSQL, int col)
{
	sqlite3_stmt *stmt;	// stores the results of the query
	string value;		// stores the string value

	// runs the statement and puts the results in stmt
	if( sqlite3_prepare_v2(_db, pSQL.c_str(), pSQL.length(), &stmt, NULL) )
	{
		// output error message
		cout << "Prepare Error: " << sqlite3_errmsg(_db) << endl;

		//quit and return ERROR
		return "ERROR";
	}

	// steps to the first row of values
	sqlite3_step(stmt);

	// gets a string value from the given column
	if(sqlite3_column_text(stmt, col))
		value = (char*)sqlite3_column_text(stmt, col);
	else
		value = "ERROR";

	// clears the stmt
	sqlite3_finalize(stmt);

	return value;
}

// Reads the first row of the database and returns
//  the blob from the given column.
const void *Alfy_SQL::getBlob(string pSQL, int col)
{
	sqlite3_stmt *stmt;	// stores the results of the query

	// runs the statement and puts the results in stmt
	if( sqlite3_prepare_v2(_db, pSQL.c_str(), pSQL.length(), &stmt, NULL) )
	{
		// output error message
		cout << "Prepare Error: " << sqlite3_errmsg(_db) << endl;

		//quit and return 0
		return 0;
	}

	// steps to the first row of values
	sqlite3_step(stmt);

	// gets a blob value from the given column
	const void *value = sqlite3_column_blob(stmt, col);

	// clears the stmt
	sqlite3_finalize(stmt);

	return value;
}

// This is the default callback for SQL commands
//  It is called once for each row of the dataabase
//  It just sends any data retirieved to the command prompt
//  Made for testing purposes
int alfy_SQL_db_callback(void *NotUsed, int col, char **values, char **colName)
{
	//Outputs the column name and the value for each column
    for(int i=0; i<col; i++)
		cout << colName[i] << ": " << values[i] << endl;

    cout << endl;

	return 0;
}













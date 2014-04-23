#ifndef ALFY_SQL_H
#define ALFY_SQL_H

#include <iostream>
#include <string>

#include "sqlite3.h"

using namespace std;

//prototype used to output all values to the cmd prompt
// built for testing
int alfy_SQL_db_callback(void *NotUsed, int col, char **values, char **colName);

class Alfy_SQL
{
	sqlite3 *_db;
	string _fileName;

public:
	Alfy_SQL(string fileName = "database.db");
	Alfy_SQL(string fileName, sqlite3 *db);

	void open();
	void close();

	void setName(string fileName)	{ _fileName = fileName;	}
	string getName()				{ return _fileName;		}

	sqlite3 *getDatabase()			{ return _db;			}

	void runSQL(const char *pSQL);
	void runSQL(string pSQL);
	void runSQL(const char *pSQL, 
		int callback(void*, int, char**, char**));
	void runSQL(string pSQL, 
		int callback(void*, int, char**, char**));

	
	double getDouble(string pSQL, int col = 0);
	int getInt(string pSQL, int col = 0);
	string getString(string pSQL, int col = 0);
	const void *getBlob(string pSQL, int col = 0);
};

#endif

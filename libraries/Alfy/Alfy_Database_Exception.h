#ifndef ALFY_DATABASE_EXCEPTION_H
#define	ALFY_DATABASE_EXCEPTION_H

/*
when it is thrown

Constructor. When the item's size doesn't match the database's item size
Write item. When you try to write an item and the id already exists
ReadItem(const char id[]). when the id is not found
EditItem(Item &item, const char id[]). when the id is not found
EditItem(Item &item, int index). when the new id is different
DeleteItem(const char id[]). when the id is not found
*/

class Alfy_Database_Exception
{
private:
	char exception[30];
public:
	//accepts a string as the default constructor
	Alfy_Database_Exception(const char what[])
	{
		int index = 0;

		do
		{
			exception[index] = what[index];
		}
		while(what[index++] != 0 && index < 30);
	}
	//returns the what or the string given
	const char* what()
	{	return exception;	}
};

#endif

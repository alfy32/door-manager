#ifndef ALFY_DATABASE_TEMPLATE_H
#define ALFY_DATABASE_TEMPLATE_H

#include <fstream>
using namespace std;

template<typename Item>
class Alfy_Database
{
private:
	char _fileName[255];
	int _count;
public:
	//default constructor creates the database if it doesn't exist
	Alfy_Database(const char fileName[] = "Database.db");

	//returns the name of the file
	const char *getName() { return _fileName; }
	int getCount() { return _count; }	//returns a count of the items

	Item readItem(int index);			//return item from chosen location in the database
	void writeItem(Item &item);			//write an item to the end of the database
	void editItem(Item&, int index);	//edit an item
	void deleteItem(int index);			//deletes an item

	//reads a member of an item. The offset is the size of the members before the desired one.
	template<typename Member>
	Member* readMember(Member& member, int index, int offset);

protected:	//inside actions
	void create();						//create the file
	void writeCount();					//writes the count to the database
	void readCount();					//reads the count from the database
	bool exists() const;				//check if the database exist
};
///////////////////////////////////////////////////


//default constructor to set fileName
//*************************************************
template<typename Item>
Alfy_Database<Item>::Alfy_Database(const char fileName[])
{
	//*************************
	//set the file name
	//*************************
	int index = 0;
	do _fileName[index] = fileName[index];
	while(fileName[index++] != 0);
	_fileName[index] = 0;

	//*********************************
	//check if the file already exists
	//*********************************
	if(exists())
	{
		//************************************
		//make sure the item is the same size
		//and it is the right database
		//************************************
		int size = 0;

		//read the item count and size
		fstream file(_fileName, ios::in | ios::binary);
		file.read(reinterpret_cast<char*>(&_count), sizeof(int));
		file.read(reinterpret_cast<char*>(&size), sizeof(int));

		//check the size to make sure it is ok to use the database
		if(size != sizeof(Item))
			throw std::string("Data size doesn't match");
	}
	//*********************************************
	//create an empty database if it doesn't exist
	//*********************************************
	else
		create();
}
///////////////////////////////////////////////////


//return item from chosen location in the database
//*************************************************
template<typename Item>
Item Alfy_Database<Item>::readItem(int index)
{
	Item item;

	//make sure the item number is valid
	if(index >= 0 && index < _count)
	{
		fstream file(_fileName, ios::in | ios::binary);
		file.seekg(2*sizeof(int) + (index * sizeof(Item)), ios::beg);
		file.read(reinterpret_cast<char*>(&item), sizeof(Item));
		file.close();
	}

	return item;
}
//write an item to the end of the database
//*************************************************
template<typename Item>
void Alfy_Database<Item>::writeItem(Item &item)
{
	fstream file(_fileName, ios::out | ios::in | ios::binary);

	//write item
	file.seekp(2*sizeof(int) + (_count * sizeof(Item)), ios::beg);
	file.write(reinterpret_cast<char*>(&item), sizeof(Item));

	//increment count
	_count++;

	//write count
	file.seekp(0, ios::beg);
	file.write(reinterpret_cast<char*>(&_count), sizeof(int));

	file.close();
}
//edit an item
//*************************************************
template<typename Item>
void Alfy_Database<Item>::editItem(Item &item, int index)
{
	//check if location given is valid.
	if(index >=0 && index <= _count)
	{
		fstream file(_fileName, ios::out | ios::in | ios::binary);
		file.seekp(2*sizeof(int) + (index * sizeof(Item)), ios::beg);
		file.write(reinterpret_cast<char*>(&item), sizeof(Item));
		file.close();
	}
}

//deletes an item
//*************************************************
template<typename Item>
void Alfy_Database<Item>::deleteItem(int index)
{
	//if the item is the last one just say it doesn't exist
	if(index == _count - 1)
	{
		//decrement count
		_count--;

		//write the count
		fstream file(_fileName, ios::in | ios::out | ios::binary);
		file.seekp(0, ios::beg);
		file.write(reinterpret_cast<char*>(&_count), sizeof(int));
		file.close();
	}
	//if any other valid index is given copy last to the given location
	else if(index >= 0 && index < _count - 1)
	{
		//decrement count
		_count--;

		Item item;

		fstream file(_fileName, ios::in | ios::out | ios::binary);

		//read the last item
		file.seekg(2*sizeof(int) + (_count * sizeof(Item)), ios::beg);
		file.read(reinterpret_cast<char*>(&item), sizeof(Item));

		//write it to the delete location
		file.seekp(2*sizeof(int) + (index * sizeof(Item)), ios::beg);
		file.write(reinterpret_cast<char*>(&item), sizeof(Item));

		//write the count
		file.seekp(0, ios::beg);
		file.write(reinterpret_cast<char*>(&_count), sizeof(int));

		file.close();
	}
}
///////////////////////////////////////////////////


//read a member
//*************************************************
template<typename Item>
template<typename Member>
Member* Alfy_Database<Item>::readMember(Member& member, int index, int offset)
{
	//make sure index is valid
	if(index >= 0 && index < getCount())
	{
		fstream file(_fileName, ios::in | ios::binary);

		//read selected item
		file.seekg(2*sizeof(int) + offset + (index * sizeof(Item)), ios::beg);
		file.read(reinterpret_cast<char*>(&member), sizeof(Member));
		file.close();
	}

	return &member;
}
///////////////////////////////////////////////////


//creates the database file
//*************************************************
template<typename Item>
void Alfy_Database<Item>::create()
{
	//set count to zero
	_count = 0;
	//find the size of the item
	int size = sizeof(Item);

	fstream file(_fileName, ios::out | ios::binary);
	file.write(reinterpret_cast<char*>(&_count),sizeof(int));
	file.write(reinterpret_cast<char*>(&size), sizeof(int));
	file.close();
}
//set the count of items
//*************************************************
template<typename Item>
void Alfy_Database<Item>::writeCount()
{
	fstream file(_fileName, ios::out | ios::in | ios::binary);
	file.write(reinterpret_cast<char*>(&_count),sizeof(int));
	file.close();
}
//return the number of items
//*************************************************
template<typename Item>
void Alfy_Database<Item>::readCount()
{
	fstream file(_fileName, ios::in | ios::binary);
	file.read(reinterpret_cast<char*>(&_count),sizeof(int));
	file.close();
}
//check for the database file
//*************************************************
template<typename Item>
bool Alfy_Database<Item>::exists() const
{
	fstream file(_fileName, ios::in);
	if(!file)
	{
		file.close();
		return false;
	}
	else
	{
		file.close();
		return true;
	}
}
///////////////////////////////////////////////////


#endif

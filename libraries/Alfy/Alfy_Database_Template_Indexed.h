#ifndef ALFY_DATABASE_TEMPLATE_INDEXED_H
#define ALFY_DATABASE_TEMPLATE_INDEXED_H

const int ID = 13;

#include <fstream>

#include "Alfy_Database_Exception.h"

using namespace std;


const int SIZE_COUNT = sizeof(int);					//size of the count variable
const int SIZE_SIZE = sizeof(int);					//size of the int to track Item size
const int SIZE_GOOD = sizeof(bool);					//to tell if the references were all written
//keep track of where the items start in the database
const int REFS_START = SIZE_GOOD;
const int ITEM_START = SIZE_COUNT + SIZE_SIZE;


template<typename Item, typename IDtype>
class Alfy_Database_Indexed
{
	struct Reference			//things to keep track of in memory for sorting and quick access
	{
		int index;
		IDtype id;
	};
private:
	char _fileName[255];		//name of the database file
	char _refName[255];			//name used for the reference database
	int _count;					//tracks the item count
	int SIZE_ITEM;				//holds the item size
	int SIZE_ID;				//size of the id
	int SIZE_REFS;				//size of the int used to keep the items sorted

	Reference *reference;		//a pointer to dynamically allocate the references
public:
	//default constructor creates the database if it doesn't exist
	Alfy_Database_Indexed(const char fileName[] = "Database.db");
	~Alfy_Database_Indexed();					//clears dynamic memory and saves the references

	const char *getName() { return _fileName; };  //returns the name of the file
	int getCount()		  { return _count;	  };  //returns a count of the items

	//binary search find the id
	int findByID(IDtype id);			//finds the reference index of the given ID

	void writeItem(Item &item);			//write an item to the end and place the reference in sorted order
	Item readItem(IDtype id);			//return item with given ID
	Item readItemIndex(int index);		//reads by the sorted index
	Item readByActualIndex(int index);	//reads by the index
	//edit an item by giving the index or the ID
	void editItem(Item &item, IDtype id);		//by ID
	void editItemIndex(Item &item, int index);	//by sorted index
	//edit an item by giving the index or the ID and change the ID
	void editItemID(Item &item, IDtype id);		//by ID
	void editItemIDIndex(Item &item, int index);//by sorted index

	void deleteItem(IDtype id);			//deletes item with given ID

//inside hidden actions
protected:
	void create();						//create the file
	bool exists() const;				//check if the database exists
	void setCount(int count);			//for certain functions to add or subtract the number of items
	void readCount();					//reads the count from the database
};

//default constructor to set fileName
//**************************************
template<typename Item, typename IDtype>
Alfy_Database_Indexed<Item, IDtype>::Alfy_Database_Indexed(const char fileName[])
:SIZE_ITEM(sizeof(Item)), SIZE_ID(sizeof(IDtype)), SIZE_REFS(sizeof(int))
{
	//*************************
	//set the file name
	//*************************
    int index = 0;
	do _fileName[index] = fileName[index];
	while(fileName[index++] != 0);

	//*************************
	//set the ref name
	//*************************
	index = 0;
	do
	{
		_refName[index] = fileName[index];
		index++;
	}
	while(fileName[index] != '.' && fileName[index] != 0);
 	//add .dll to the end
	_refName[index++] = '.';
	_refName[index++] = 'd';
	_refName[index++] = 'l';
	_refName[index++] = 'l';
	_refName[index++] = 0;

	//*********************************
	//check if the file already exists
	//*********************************
	if(exists())
	{
		//*******************************************
		//read the count and item size
		//*******************************************
		int size = 0;	//read the size to a temp variable to check against

		//read the count and item size
		fstream file(_fileName, ios::in | ios::binary);
		file.seekg(0L, ios::beg);
		file.read(reinterpret_cast<char*>(&_count), SIZE_COUNT);
		file.read(reinterpret_cast<char*>(&size), SIZE_SIZE);
		file.close();

		//*********************************************************
		//check the size to make sure it is ok to use the database
		//*********************************************************
		if(size !=SIZE_ITEM)
			throw Alfy_Database_Exception("Data size doesn't match");

		//**************************************************
		//read the references to set up the sorted database
		//**************************************************
		if(_count != 0)
		{
			fstream refFile(_refName, ios::in | ios::binary);

			if(refFile)
			{
				//allocate the array
				reference = new Reference[_count];
				Item tempItem;
				int refsIndex;

				//open the file to read in the reference array
				fstream file(_fileName, ios::in | ios::binary);

				//read and place the references
				for(int index = 0; index < _count; index++)
				{
					//read the reference ints
					refFile.seekg(REFS_START + (index * SIZE_REFS), ios::beg);
					refFile.read(reinterpret_cast<char*>(&refsIndex), SIZE_REFS);

					//read the item
					file.seekg(ITEM_START + (refsIndex * SIZE_ITEM), ios::beg);
					file.read(reinterpret_cast<char*>(&tempItem), SIZE_ITEM);

					//add its info to reference
					reference[index].index = refsIndex;
					reference[index].id = tempItem.indexer();
				}
				file.close();
			}
			refFile.close();
		}
		else
		{

			fstream refFile(_refName, ios::out | ios::binary);
			bool bad = false;
			refFile.seekp(0, ios::beg);
			refFile.write(reinterpret_cast<char*>(&bad), SIZE_GOOD);
			refFile.close();
		}
	}
	//*********************************************
	//create an empty database if it doesn't exist
	//*********************************************
	else
	{
		create();

		//create ref database
		fstream refFile(_refName, ios::out | ios::binary);
		bool bad = false;
		refFile.seekp(0, ios::beg);
		refFile.write(reinterpret_cast<char*>(&bad), SIZE_GOOD);
		refFile.close();
	}
}
//destructor
//**************************************
template<typename Item, typename IDtype>
Alfy_Database_Indexed<Item, IDtype>::~Alfy_Database_Indexed()
{
	//deallocate the reference memory
	delete [] reference;
}
//////////////////////////////////////////////////////



//finds the index of the reference containing the item location
//**************************************
template<typename Item, typename IDtype>
int Alfy_Database_Indexed<Item, IDtype>::findByID(IDtype id)
{
	//************************
	//find the item by the ID
	//************************
	int start = 0;			//index of first element of the array
	int	end = _count -1;	//index of last element of the array
	int	middle;				//index of the middle of the first and last
	int	index = -1;			//index where the value is found
	bool found = false;		//to quit the loop when the element is found

	while(!found && start <= end)
	{
		//find middle
		middle = (start + end)/2;
		//see if the value is the middle
		if(id == reference[middle].id)
		{
			found = true;
			index = middle;
		}
		//see if the value is smaller than the middle
		else if(id < reference[middle].id)
			end = middle - 1;
		//see if the value is bigger
		else
			start = middle + 1;
	}
	return index;
}
//////////////////////////////////////////////////////



//write item to the end of the file and place index in the reference array
//****************************************************
template<typename Item, typename IDtype>
void Alfy_Database_Indexed<Item, IDtype>::writeItem(Item &item)
{
	//if this is the first item wirte it to zero and set its reference to zero
	if(_count == 0)
	{
		//increment the count
		_count++;

		//open the database file
		fstream file(_fileName, ios::out | ios::in | ios::binary);
		fstream refFile(_refName, ios::out | ios::in | ios::binary);

		//set the reference in memory
		reference = new Reference[_count];
		reference[0].index = 0;
		reference[0].id = item.indexer();

		//write the count
		file.seekp(0, ios::beg);
		file.write(reinterpret_cast<char*>(&_count),SIZE_COUNT);

		//write the item
		file.seekp(ITEM_START, ios::beg);
		file.write(reinterpret_cast<char*>(&item),SIZE_ITEM);

		//write the reference
		int temp = 0;
		refFile.seekp(REFS_START, ios::beg);
		refFile.write(reinterpret_cast<char*>(&temp), sizeof(temp));

		refFile.close();
		file.close();
	}
	//if there are already one or more items find the location then write it
	else
	{
		int newIndex;			//the location where the new item will be placed

		//////////////////////////////////////
		//find the location to place the item
		//////////////////////////////////////

		int start = 0;			//index of first element of the array
		int	end = _count -1;	//index of last element of the array
		int	middle;				//index of the middle of the first and last

		while(start <= end)
		{
			//find middle
			middle = (start + end)/2;

			//if the ids are the same throw an exception
			if(item.indexer() == reference[middle].id)
				throw Alfy_Database_Exception("Can't write same ID");

			//see if the value is smaller than the middle
			if(item.indexer() < reference[middle].id)
				end = middle - 1;
			//if the value is bigger
			else
				start = middle + 1;
		} //middle is now an item that is next to the new item we have to find out if the new item goes before or after

		//if the new ID is smaller than the middle
		if(item.indexer() < reference[middle].id)
			newIndex = middle;		//the new item goes before middle
		else
			newIndex = middle + 1;	//the new item goes after middle

		///////////////////////////////
		//write the count and the item
		///////////////////////////////

		//open the database file
		fstream file(_fileName, ios::out | ios::in | ios::binary);

		//write the item
		file.seekp(ITEM_START + (_count *SIZE_ITEM), ios::beg);
		file.write(reinterpret_cast<char*>(&item),SIZE_ITEM);

		//increment the count
		_count++;

		//write the count
		file.seekp(0, ios::beg);
		file.write(reinterpret_cast<char*>(&_count), SIZE_COUNT);

		file.close();

		/////////////////////////////////////////////////////
		//open the ref file and write that it isn't good yet
		/////////////////////////////////////////////////////

		//open the database file
		fstream refFile(_refName, ios::out | ios::in | ios::binary);

		//go to the start
		refFile.seekp(0, ios::beg);

		//write that it didn't work
		bool good = false;
		refFile.write(reinterpret_cast<char*>(&good), SIZE_GOOD);

		/////////////////////////////////////////
		//create the new array that is one biger
		/////////////////////////////////////////

		Reference *tempRef = new Reference[_count];

		//////////////////////////
		//place the new reference
		//////////////////////////

		//copy all up to the new index
		for(int x = 0; x < newIndex; x++)
			tempRef[x] = reference[x];
		//place the new value
		tempRef[newIndex].index = _count-1;
		tempRef[newIndex].id = item.indexer();
		//copy all after the newIndex
		for(int x = newIndex; x < _count-1; x++)
			tempRef[x+1] = reference[x];
		//delete the old array point to the new one
		delete [] reference;
		reference = tempRef;

		//////////////////////////////////////
		//write the updated reference indexes
		//////////////////////////////////////

		//find start of the references
		refFile.seekp(REFS_START, ios::beg);

		//write all the reference indexes
		for(int index = 0; index < _count; index++)
			refFile.write(reinterpret_cast<char*>(&(reference[index].index)), SIZE_REFS);

		//go to the start
		refFile.seekp(0, ios::beg);

		//write that it did work
		good = true;
		refFile.write(reinterpret_cast<char*>(&good), SIZE_GOOD);

		refFile.close();
	}
}
//returns the desired item structure by ID
//**************************************
template<typename Item, typename IDtype>
Item Alfy_Database_Indexed<Item, IDtype>::readItem(IDtype id)
{
	//find the index
	int index = findByID(id);

	if(index == -1)
		throw Alfy_Database_Exception("Invalid ID");
	//******************************
	//read the item given the index
	//******************************
	Item item;

	fstream file(_fileName, ios::in | ios::binary);

	//read selected item
	file.seekg(ITEM_START + (reference[index].index *SIZE_ITEM), ios::beg);
	file.read(reinterpret_cast<char*>(&item),SIZE_ITEM);
	file.close();

	return item;
}
//returns the desired item structure by sorted index
//**************************************
template<typename Item, typename IDtype>
Item Alfy_Database_Indexed<Item, IDtype>::readItemIndex(int index)
{
	Item item;

	fstream file(_fileName, ios::in | ios::binary);

	//read selected item
	file.seekg(ITEM_START + (reference[index].index *SIZE_ITEM), ios::beg);
	file.read(reinterpret_cast<char*>(&item),SIZE_ITEM);
	file.close();

	return item;
}
//returns the desired item structure by actual index
//**************************************
template<typename Item, typename IDtype>
Item Alfy_Database_Indexed<Item, IDtype>::readByActualIndex(int index)
{
	Item item;

	fstream file(_fileName, ios::in | ios::binary);

	//read selected item
	file.seekg(ITEM_START + (index *SIZE_ITEM), ios::beg);
	file.read(reinterpret_cast<char*>(&item),SIZE_ITEM);
	file.close();

	return item;
}
//edit an Item by ID without changing the id
//****************************************************
template<typename Item, typename IDtype>
void Alfy_Database_Indexed<Item, IDtype>::editItem(Item &item, IDtype id)
{
	int index = findByID(id);

	if(index == -1)
		throw Alfy_Database_Exception("That ID is not found");

	editItemIndex(item, index);
}
//edit an Item by sorted Index without changing the id
//****************************************************
template<typename Item, typename IDtype>
void Alfy_Database_Indexed<Item, IDtype>::editItemIndex(Item &item, int index)
{
	Item oldItem;

	fstream file(_fileName, ios::out | ios::in | ios::binary);

	//read the old one
	file.seekg(ITEM_START + (reference[index].index *SIZE_ITEM), ios::beg);
	file.read(reinterpret_cast<char*>(&oldItem),SIZE_ITEM);

	//make sure the ID is the same
	if(oldItem.indexer() != item.indexer())
		throw Alfy_Database_Exception("You can't change the ID");

	//write the new one
	file.seekp(ITEM_START + (reference[index].index *SIZE_ITEM), ios::beg);
	file.write(reinterpret_cast<char*>(&item),SIZE_ITEM);

	file.close();
}
//edit an Item by ID and change the ID
//****************************************************
template<typename Item, typename IDtype>
void Alfy_Database_Indexed<Item, IDtype>::editItemID(Item &item, IDtype id)
{
	deleteItem(id);

	writeItem(item);
}
//edit an Item by sorted Index
//****************************************************
template<typename Item, typename IDtype>
void Alfy_Database_Indexed<Item, IDtype>::editItemIDIndex(Item &item, int index)
{
	deleteItem(reference[index].id);

	writeItem(item);
}
//////////////////////////////////////////////////////



//deletes the specified item
//**************************************
template<typename Item, typename IDtype>
void Alfy_Database_Indexed<Item, IDtype>::deleteItem(IDtype id)
{
	//find the index
	int deleteIndex = findByID(id);

	if(deleteIndex == -1)
		throw Alfy_Database_Exception("Invalid ID");

	//**********************************
	//decrement count and write it
	//**********************************

	setCount(--_count);

	//**********************************
	//create some variables
	//**********************************

	int refLast;
	Item tempItem;

	//**********************************
	//check if it is not the last item
	//**********************************

	if(reference[deleteIndex].index != _count)
	{
		fstream file(_fileName, ios::out | ios::in | ios::binary);

		//************************************************
		//read the last item
		//************************************************

		file.seekg(ITEM_START + (_count *SIZE_ITEM), ios::beg);
		file.read(reinterpret_cast<char*>(&tempItem),SIZE_ITEM);

		//************************************************
		//write write it to the delete location
		//************************************************
		file.seekp(ITEM_START + (reference[deleteIndex].index *SIZE_ITEM), ios::beg);
		file.write(reinterpret_cast<char*>(&tempItem),SIZE_ITEM);

		file.close();

		//**********************************
		//find the reference pointing to the last item
		//**********************************

		for(int x = 0; x <= _count; x++)
		{
			if(reference[x].index == _count)
			{
				refLast = x;
				break;
			}
		}

		//have it point to the delete index
		reference[refLast].index = reference[deleteIndex].index;
	}

	//////////////////////////
	//fix the reference array
	//////////////////////////

	//create a new array for reference
	Reference *ref = new Reference[_count];

	//copy references up to delete index
	for(int x = 0; x < deleteIndex; x++)
		ref[x] = reference[x];

	//copy references after delete index
	for(int x = deleteIndex; x < _count; x++)
		ref[x] = reference[x+1];

	//delete old reference array
	delete [] reference;

	//point to new array
	reference = ref;

	///////////////////////
	//write the references
	///////////////////////
	fstream file(_refName, ios::out | ios::in | ios::binary);

	//seek to the start of the references
	file.seekp(REFS_START, ios::beg);

	//write all the references
	for(int x = 0; x < _count; x++)
		file.write(reinterpret_cast<char*>(&(reference[x].index)), SIZE_REFS);

	file.close();
}
//////////////////////////////////////////////////////



//////////////////////////////////////////////////////
//				Hidden actions						//
//////////////////////////////////////////////////////




//creates the database file
//*************************************************
template<typename Item, typename IDtype>
void Alfy_Database_Indexed<Item, IDtype>::create()
{
	//initialize _count
	_count = 0;

	fstream file(_fileName, ios::out | ios::binary);
	//write the count
	file.write(reinterpret_cast<char*>(&_count), SIZE_COUNT);
	//write the size of the items to assure it doesn't change
	file.write(reinterpret_cast<char*>(&SIZE_ITEM), SIZE_SIZE);

	file.close();
}
//check for the database file
//*************************************************
template<typename Item, typename IDtype>
bool Alfy_Database_Indexed<Item, IDtype>::exists() const
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




//set the count of items
//*************************************************
template<typename Item, typename IDtype>
void Alfy_Database_Indexed<Item, IDtype>::setCount(int count)
{
	//update count in memory
	_count = count;

	//update count on file
	fstream file(_fileName, ios::out | ios::in | ios::binary);
	file.write(reinterpret_cast<char*>(&_count), SIZE_COUNT);
	file.close();
}
//reads the count from the file and saves it to _count
//**************************************
template<typename Item, typename IDtype>
void Alfy_Database_Indexed<Item, IDtype>::readCount()
{
	//read the count in the file
	fstream file(_fileName, ios::in | ios::binary);
	file.read(reinterpret_cast<char*>(&_count), SIZE_COUNT);
	file.close();
}


#endif

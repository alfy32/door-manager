#include "DoorSize.h"

//default constructor sets all to zero
DoorSize::DoorSize()
{
	width =  height = 0;
	custom = false;
}

//constructor accepts a string in the format *3*6*6*8*
// prefered format 3'6" X 6'8"
// add custom to the end for custom sizes
DoorSize::DoorSize(string size)
{
	int index = 0;
	int width_feet, width_inches, height_feet, height_inches;

	findNextNumberIndex(size,index);
	width_feet = getNextNumber(size,index);
	findNextNumberIndex(size,index);
	width_inches = getNextNumber(size,index);
	findNextNumberIndex(size,index);
	height_feet = getNextNumber(size,index);
	findNextNumberIndex(size,index);
	height_inches = getNextNumber(size,index);

	width = width_feet*12 + width_inches;
	height = height_feet*12 + height_inches;

	int c = size.find("custom");
	custom = c != -1;
}

//same as the string constructor
// accepts a string in the format *3*6*6*8*
// prefered format 3'6" X 6'8"
// add custom to the end for custom sizes
void DoorSize::setDimensions(string size)
{
	int index = 0;
	int width_feet, width_inches, height_feet, height_inches;

	findNextNumberIndex(size,index);
	width_feet = getNextNumber(size,index);
	findNextNumberIndex(size,index);
	width_inches = getNextNumber(size,index);
	findNextNumberIndex(size,index);
	height_feet = getNextNumber(size,index);
	findNextNumberIndex(size,index);
	height_inches = getNextNumber(size,index);

	width = width_feet*12 + width_inches;
	height = height_feet*12 + height_inches;

	int c = size.find("custom");
	custom = c != -1;
}

//sets the dimensions with integer values
void DoorSize::setDimensions(int width_feet, int width_inches, int height_feet, int height_inches, bool cust)
{
	width = width_feet*12 + width_inches;
	height = height_feet*12 + height_inches;
	custom = cust;
}

//puts the full dimensions in a string
string DoorSize::toString()
{
	string str;
	char temp[80];

	itoa(width/12,temp,10);
	str = temp;

	str += "'";

	itoa(width%12,temp,10);
	str += temp;

	str += "\" X ";

	itoa(height/12,temp,10);
	str += temp;

	str += "'";

	itoa(height%12,temp,10);
	str += temp;

	str += "\"";

	if(custom)
		str += " custom";

	return str;
}

//puts the full dimensions in a string that is safe for SQL
string DoorSize::toStringSQL()
{
	string str;
	char temp[80];

	itoa(width/12,temp,10);
	str = temp;

	str += "''";

	itoa(width%12,temp,10);
	str += temp;

	str += "\" X ";

	itoa(height/12,temp,10);
	str += temp;

	str += "''";

	itoa(height%12,temp,10);
	str += temp;

	str += "\"";

	if(custom)
		str += " custom";

	return str;
}

string DoorSize::getWidth()
{
    string str;
	char temp[80];

	itoa(width/12,temp,10);
	str = temp;

	str += "''";

	itoa(width%12,temp,10);
	str += temp;

	str += "\"";

	return str;
}

string DoorSize::getHeight()
{
    string str;
	char temp[80];

	itoa(height/12,temp,10);
	str = temp;

	str += "''";

	itoa(height%12,temp,10);
	str += temp;

	str += "\"";

	return str;
}

bool DoorSize::isNumber(char ch)
{
	return !(ch < '0' || ch > '9');
}

int DoorSize::findNextNumberIndex(string str, int &start)
{
	while(start < int(str.length()) && !isNumber(str[start]))
			start++;

	return start;
}

int DoorSize::getNextNumber(string str, int &start)
{
	string number;

	while(start < int(str.length()) && isNumber(str[start]))
			number += str[start++];

	return atoi(number.c_str());
}

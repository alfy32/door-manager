#include "JambSize.h"

//default constructor sets all to zero
JambSize::JambSize()
{
	width =  height = 0;
	custom = false;
}

//constructor accepts a string in the format *4*9*16*8*0*
// * = wildcard, non digit characters
// prefered format 4 9/16 X 6'8"
// add custom to the end for custom sizes
JambSize::JambSize(string size)
{
	int index = 0;
	int width_inches, width_num, width_den, height_feet, height_inches;

	findNextNumberIndex(size,index);
	width_inches = getNextNumber(size,index);
	findNextNumberIndex(size,index);
	width_num = getNextNumber(size,index);
	findNextNumberIndex(size,index);
	width_den = getNextNumber(size,index);
	findNextNumberIndex(size,index);
	height_feet = getNextNumber(size,index);
	findNextNumberIndex(size,index);
	height_inches = getNextNumber(size,index);

	width = width_inches + width_num / width_den;
	height = height_feet*12 + height_inches;

	int c1 = size.find("custom");
	int c2 = size.find("Custom");
	custom = (c1 + c2) > 0;
}

//same as the string constructor
// accepts a string in the format *4*9*16*8*0*
// prefered format 4 9/16 X 6'8"
// add custom to the end for custom sizes
void JambSize::setDimensions(string size)
{
	int index = 0;
	int width_inches, width_num, width_den, height_feet, height_inches;

	findNextNumberIndex(size,index);
	width_inches = getNextNumber(size,index);
	findNextNumberIndex(size,index);
	width_num = getNextNumber(size,index);
	findNextNumberIndex(size,index);
	width_den = getNextNumber(size,index);
	findNextNumberIndex(size,index);
	height_feet = getNextNumber(size,index);
	findNextNumberIndex(size,index);
	height_inches = getNextNumber(size,index);

	width = width_inches + width_num / width_den;
	height = height_feet*12 + height_inches;

	int c1 = size.find("custom");
	int c2 = size.find("Custom");
	custom = (c1 + c2) > 0;
}

//sets the dimensions with integer values
void JambSize::setDimensions(int width_feet, int width_inches, int height_feet, int height_inches, bool cust)
{
	width = width_feet*12 + width_inches;
	height = height_feet*12 + height_inches;
	custom = cust;
}

//puts the full dimensions in a string
string JambSize::toString()
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
string JambSize::toStringSQL()
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
		str += " Custom";

	return str;
}

string JambSize::getWidth()
{
    string str;
	char temp[80];

	itoa(width/12,temp,10);
	str = temp;

	str += "''";

	itoa(width%12,temp,10);
	str += temp;

	str += "\"";

	if(custom)
		str += " Custom";

	return str;
}

string JambSize::getHeight()
{
    string str;
	char temp[80];

	itoa(height/12,temp,10);
	str = temp;

	str += "''";

	itoa(height%12,temp,10);
	str += temp;

	str += "\"";

	if(custom)
		str += " Custom";

	return str;
}

bool JambSize::isNumber(char ch)
{
	return !(ch < '0' || ch > '9');
}

int JambSize::findNextNumberIndex(string str, int &start)
{
	while(start < str.length() && !isNumber(str[start]))
			start++;

	return start;
}

int JambSize::getNextNumber(string str, int &start)
{
	string number;

	while(start < str.length() && isNumber(str[start]))
			number += str[start++];

	return atoi(number.c_str());
}

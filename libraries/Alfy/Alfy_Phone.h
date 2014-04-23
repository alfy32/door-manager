#ifndef ALFY_PHONE_H
#define ALFY_PHONE_H

#include <string>

class Alfy_Phone
{
	short block[3];
public:
	//constructors
	////////////////////////////////////////////////////////////////////////////

	//default accepts shorts
	Alfy_Phone(short block1 = 0, short block2 = 0, short block3 = 0);
	//accepts "555", "555", "5555" or "555", "5555"
	Alfy_Phone(const char block1[], const char block2[], const char block3[]=0);
	//accepts  "5555"
    //      or "5555555"
    //      or "555-5555"
    //      or "5555555555"
    //      or "555-555-5555"
    //      or "(555)555-5555"
    //default is 435-896-####
    Alfy_Phone(const char number[]);

	/////////////////////////////////////////////////////////////////////////////

	//get Phone Number
	////////////////////////////////////////////////////

	//only allows getting not setting
	short operator[](int index) { return block[index]; }
	short getBlock(int index)	{ return block[index]; }

	//format "(555)555-5555"
	std::string toString();
	//format "555-555-5555"
	std::string toString2();

	////////////////////////////////////////////////////

	//overloaded operators
	bool operator <  (Alfy_Phone& right)		{ if(toString() <  right.toString()) return true; else return false; }
	bool operator <= (Alfy_Phone& right)		{ if(toString() <= right.toString()) return true; else return false; }
	bool operator >  (Alfy_Phone& right)		{ if(toString() >  right.toString()) return true; else return false; }
	bool operator >= (Alfy_Phone& right)		{ if(toString() >= right.toString()) return true; else return false; }
	bool operator == (Alfy_Phone& right)		{ if(toString() == right.toString()) return true; else return false; }
	bool operator != (Alfy_Phone& right)		{ if(toString() != right.toString()) return true; else return false; }
};

#endif

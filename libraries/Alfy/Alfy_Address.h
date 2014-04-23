#ifndef ALFY_ADDRESS_H
#define ALFY_ADDRESS_H

#include <string>
#include "Alfy_Enumerations.h"
#include "Alfy_Strings.h"

class Alfy_Address
{
	char _address[30];
	char _city[15];
	short _state;
	int _zipCode;

public:
    //default constructor
	Alfy_Address(const char address[] = "address", const char city[] = "Richfield", const char state[] = "Utah", const char zip[] = "84701");

	////////////////////////////////////////////////////////////////////

	//get functions
	/////////////////////////////////////////////

    //format 366 Highland Drive Richfield Utah, 84701
	std::string toString();
	const char* address()	{ return _address;	}
	const char* city()		{ return _city;		}
	std::string state();
	std::string stateCode();
	std::string zip();
	int zipInt()			{ return _zipCode;	}

	/////////////////////////////////////////////

	//overloaded operators
	bool operator <  (Alfy_Address& right)		{ if(toString() <  right.toString()) return true; else return false; }
	bool operator <= (Alfy_Address& right)		{ if(toString() <= right.toString()) return true; else return false; }
	bool operator >  (Alfy_Address& right)		{ if(toString() >  right.toString()) return true; else return false; }
	bool operator >= (Alfy_Address& right)		{ if(toString() >= right.toString()) return true; else return false; }
	bool operator == (Alfy_Address& right)		{ if(toString() == right.toString()) return true; else return false; }
	bool operator != (Alfy_Address& right)		{ if(toString() != right.toString()) return true; else return false; }
};

#endif

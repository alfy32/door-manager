#ifndef ALFY_NAME_H
#define ALFY_NAME_H

#include <string>

class Alfy_Name
{
	char _first[15], _middle[15], _last[20];
public:
	//default constructor
	Alfy_Name(const char first[] = "First", const char middle[] = "Middle", const char last[] = "Last");

	//format "First Middle Last"
	std::string toString();
	//format "Last, First"
	std::string toString1();
	//format "Last, First MI"
	std::string toString2();
	//format "Last, First Middle"
	std::string toString3();
	//format "First MI Last"
	std::string toString4();

	const char* first()	    { return _first;    }
	const char* middle()	{ return _middle;   }
	const char* last()	    { return _last;     }

	//overloaded operators
	bool operator <  (Alfy_Name& right)		{ if(toString2() <  right.toString2()) return true; else return false; }
	bool operator >  (Alfy_Name& right)		{ if(toString2() >  right.toString2()) return true; else return false; }
	bool operator == (Alfy_Name& right)		{ if(toString2() == right.toString2()) return true; else return false; }
	bool operator <= (Alfy_Name& right)		{ if(toString2() <= right.toString2()) return true; else return false; }
	bool operator >= (Alfy_Name& right)		{ if(toString2() >= right.toString2()) return true; else return false; }
	bool operator != (Alfy_Name& right)		{ if(toString2() != right.toString2()) return true; else return false; }
};

#endif

#ifndef ALFY_PERSON_H
#define ALFY_PERSON_H

#include "Alfy_Name.h"
#include "Alfy_Phone.h"
#include "Alfy_Address.h"

class Alfy_Person
{
private:
	Alfy_Name _name;
	Alfy_Phone _homePhone;
	Alfy_Phone _cellPhone;
	Alfy_Address _address;
public:
	//default constructor. accepts chars
	Alfy_Person(const char first[] = "FirstName" , const char middle[] = "MiddleName", const char last[] = "LastName",
		        const char homePhone[] = "(555)896-5555", const char cellPhone[] = "(555)896-5555",
		        const char address[] = "Address", const char city[] = "City", const char state[] = "State", const char zip[] = "Zip Code")
	:_name(first,middle,last),_homePhone(homePhone),_cellPhone(cellPhone),_address(address,city,state,zip) {}

	Alfy_Person(Alfy_Name name, Alfy_Phone homePhone, Alfy_Phone cellPhone, Alfy_Address address)
	:_name(name),_homePhone(homePhone),_cellPhone(cellPhone),_address(address) {}

	Alfy_Name name()				{ return _name;						}
	const char* first()             { return _name.first();             }
	const char* middle()            { return _name.middle();            }
	const char* last()              { return _name.last();              }
	std::string nameString()		{ return _name.toString1();			}
	Alfy_Phone homePhone()			{ return _homePhone;				}
	Alfy_Phone cellPhone()			{ return _cellPhone;				}
	std::string homePhoneString()	{ return _homePhone.toString();		}
	std::string cellPhoneString()	{ return _cellPhone.toString();		}
	Alfy_Address address()			{ return _address;					}
};

#endif

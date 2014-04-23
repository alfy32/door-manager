#ifndef ALFY_CLIENT_H
#define ALFY_CLIENT_H

#include "Alfy_Person.h"

class Alfy_Client : public Alfy_Person
{
private:
	int _clientID;
public:
	//default constructor. accepts chars
	Alfy_Client(const char first[] = "FirstName" , const char middle[] = "MiddleName", const char last[] = "LastName",
		        const char homePhone[] = "(555)896-5555", const char cellPhone[] = "(555)896-5555",
                const char address[] = "Address", const char city[] = "City", const char state[] = "State", const char zip[] = "Zip Code");

	Alfy_Client(Alfy_Name name, Alfy_Phone homePhone, Alfy_Phone cellPhone, Alfy_Address address);

	void id(int id)	    { _clientID = id;	}
	int id()			{ return _clientID; }

	Alfy_Name indexer()	{ return name();	}
};

#endif

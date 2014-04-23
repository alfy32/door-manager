#ifndef ALFY_EMPLOYEE_H
#define ALFY_EMPLOYEE_H

#include "Alfy_Person.h"

class Alfy_Employee : public Alfy_Person
{
private:
	int _employeeID;
	short _schedule[6][2];
	short _column;
public:
	//default constructor. accepts chars
	Alfy_Employee(const char first[] = "FirstName" , const char middle[] = "MiddleName", const char last[] = "LastName",
                  const char homePhone[] = "(555)896-5555", const char cellPhone[] = "(555)896-5555",
		          const char address[] = "Address", const char city[] = "City", const char state[] = "State", const char zip[] = "Zip Code");

	Alfy_Employee(Alfy_Name name, Alfy_Phone homePhone, Alfy_Phone cellPhone, Alfy_Address address);

	void schedule(int[6][2]);
	const short* schedule();
	int schedule_start(int day);
	void schedule_start(int day, int hour);
	int schedule_end(int day);
	void schedule_end(int day, int hour);

	void column(int col)    { col > 8 || col < 0 ? _column = 0 : _column = col; }
	int column()            { return _column;                                   }

	void id(int ID)	        { _employeeID = ID;		}
	int id()			    { return _employeeID;	}

	Alfy_Name indexer()		{ return name();		}
};

#endif

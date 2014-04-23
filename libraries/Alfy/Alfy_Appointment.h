#ifndef ALFY_APPOINTMENT_H
#define ALFY_APPOINTMENT_H

#include "Alfy_Date.h"
#include "Alfy_Time.h"

class Alfy_Appointment
{
private:
    int _id;
	Alfy_Date _date;
	Alfy_Time _time;
	short _type;
	char _notes[200];
	int _request;
	int _employee;
	int _clientID;
public:
	//constructors
	//////////////////////////////////////////////////////////////////////////////

	//default constructor. accepts chars
	Alfy_Appointment(const char clientID[] = "000000000001",
                     const char date[] = "01/01/2011", const char time[] = "11:00 AM",
                     const char notes[] = "Notes:", short type = -1,
                     int request = -1, int employee = -1);

	//accepts a date and time and chars
	Alfy_Appointment(int clientID,
                     Alfy_Date date, Alfy_Time time, const char notes[], short type,
                     int request = -1, int employee = -1);

	//////////////////////////////////////////////////////////////////////////////

	void date(Alfy_Date d)      { _date = d;                    }

	//get functions
	/////////////////////////////////////////////////////////////

	int id()                    { return _id;                   }
	void id(int id)             { _id = id;                     }

	Alfy_Date date()			{ return _date;					}
	//format "mm/dd/yyyy"
	std::string dateString()	{ return _date.toStringInt();	}
	Alfy_Time time()			{ return _time;					}
	//format "HH:MM AM"
	std::string timeString()	{ return _time.toString();		}
	short type()				{ return _type;					}
	const char* notes()			{ return _notes;				}
	int request()				{ return _request;				}
	int employee()				{ return _employee;				}
	int client()                { return _clientID;             }

	//id function for the indexed database
	int indexer()               { return _clientID;             }
};

#endif

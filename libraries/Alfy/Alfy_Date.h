#ifndef ALFY_DATE_H
#define ALFY_DATE_H

#include <string>
#include <ctime>

#include "Alfy_Enumerations.h"
#include "Alfy_Strings.h"

class Alfy_Date
{
	static const int daysInMonths[13];
	short _month, _day, _year;
public:
	//Constructors
	/////////////////////////////////////////////////////////////////

	//accepts shorts for each variable
	Alfy_Date(int month = 6, int day = 7, int year = 2011)
	:_month(month),_day(day),_year(year) {}

	//      or  "y"                 example: "2011" or "11"
    //      or  "m/y"               example: "11/2011" or "6/11"
    //      or  "m-y"               example: "11-2011" or "6-11"
    //      or  "m/d/y"             example: "11/5/2011" or "6/12/11"
    //      or  "m-d-y"             example: "11-5-2011" or "6-12-11"
    //      or  "Month dd, yyyy"    example: "June 07, 2011"  to add later
	Alfy_Date(const char date[]);

	//formats accepted "mm", "dd", "yyyy" example: "06", "07", "2011"
	//				or "mm", "dd", "yy"   example: "06", "07", "11" range 1940 to 2040
	//				or "Month","dd","yyy" example: "June", "07", "2011"
	Alfy_Date(const char month_[], const char day_[], const char year_[]);

	/////////////////////////////////////////////////////////////////////////

	//set functions
	/////////////////////////////////////////////////////////////////////////

	void month(int);
	void day(int);
	void year(int);

	/////////////////////////////////////////////////////////////////////////

	//overloaded operator
	/////////////////////////////////////////////////////////////////////////

    bool operator <  (Alfy_Date& right);
	bool operator >  (Alfy_Date& right);
	bool operator == (Alfy_Date& right);
	bool operator <= (Alfy_Date& right);
	bool operator >= (Alfy_Date& right);
	bool operator != (Alfy_Date& right);

	Alfy_Date operator++();
	Alfy_Date operator++(int);
	Alfy_Date operator--();
	Alfy_Date operator--(int);

	void addDay();
	void addMonth();
	void addYear();

	void subtractDay();
	void subtractMonth();
	void subtractYear();

	/////////////////////////////////////////////////////////////////////////

	//get the date
	/////////////////////////////////////////////////////////////////////////

	//"Month dd, yyyy"
	std::string toString()			{ return monthString() + " " + dayStringInt() + ", " + yearStringInt();		}
	//"DayOfWeek, Month dd"
	std::string toString2()			{ return dayOfWeekString() + ", " + monthString() + " " + dayStringInt();			}
	//"mm/dd/yyyy"
	std::string toStringInt()		{ return monthStringInt() + "/" + dayStringInt() + "/" + yearStringInt();	}
	int			month()				{ return _month;						}
	//"mm"
	std::string monthStringInt();
	//"Month"
	std::string monthString()		{ return monthToString((MONTH)_month);	}
	int			day()				{ return _day;							}
	//"dd"
	std::string dayStringInt();
	int			year()				{ return _year;							}
	//"yyyy"
	std::string yearStringInt();
	//"yy"
	std::string yearStringInt2();
	int			dayOfWeek();
	//"Day"
	std::string dayOfWeekString()	{ return dayToString((DAY)dayOfWeek());	}

    ////////////////////////////////////////////////////////////////////////
	//current date functions
	////////////////////////////////////////////////////////////////////////

    //gets todays date
    static Alfy_Date getToday();
    static int getDaysInMonth(Alfy_Date date);
    static int dayOfWeek(Alfy_Date date);

	////////////////////////////////////////////////////////////////////////
	//conversion functions
	////////////////////////////////////////////////////////////////////////

	//Returns the string for the month
	static std::string intToMonthString(int month_);

	//Returns the string for the month
	static std::string monthToString(MONTH month_);

	//returns the month from a char array
	static MONTH charToMonth(const char month_[]);

	//returns the month enum from a string
	static MONTH stringToMonth(std::string month_);

	//returns the day from a char array
	static DAY charToDay(const char day_[]);

	//returns the day from a string
	static DAY stringToDay(std::string day_);

	//returns the day string from the day enum
	static std::string dayToString(DAY day_);

	////////////////////////////////////////////////
};

#endif

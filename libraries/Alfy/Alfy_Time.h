#ifndef ALFY_TIME_H
#define ALFY_TIME_H

#include <string>
#include <ctime>

class Alfy_Time
{
	int _seconds;
public:
	//constructors
	////////////////////////////////////////////////////////////////////

	//accepts militay time example 2100
	Alfy_Time(int military=0);
	//accepts militay hour, min, sec
	Alfy_Time(int hour, int min, int sec);
	//accepts hour, min, sec, pm
    Alfy_Time(int hour, int min, int sec, bool pm);

	//accepts   "7", "12", "7pm", "500", "12pm", "7:30", "0500" or "1700" or "0500 hours" or "1700 hours"
    //      or  "729PM", "12:29", "7:29PM", "1229PM", "7:29 PM", "12:29AM", "12:29 AM", "1:59:25 PM", "11:59:25 AM"
    Alfy_Time(const char time[]);
	//accepts "hh","mm","ss","AM"
	Alfy_Time(const char hour[], const char minute[], const char second[], const char AMPM[]);

	////////////////////////////////////////////////////////////////////

	//set time
	////////////////////////////////////////////////////////////////////

	void hour12(int hour, bool pm);
	void hour24(int hour);
	void minute(int minute);
	void second(int second);

	//accepts hours and minutes
	void military(int military);

	void toNow();

	////////////////////////////////////////////////////////////////////

	//get time
	////////////////////////////////////////////////////////////////////

    int hour12();
    int hour24();
    int minute();
    int second();

    bool am();
	bool pm();

    //hours and seconds
    int military();

    ////////////////////////////////////////////////////////////////////

	//get time strings
	////////////////////////////////////////////////////////////////////

    std::string hour12String();
	std::string hour24String();
	std::string minuteString();
	std::string secondString();
	std::string ampmString();
	std::string toString();             //format "HH:MM AM"
	std::string toString2();            //format "HH:MM:SS AM"
	std::string toStringMilitary();     //format "HHMM"
	std::string toStringMilitary2();    //format "HHMM Hours"

	////////////////////////////////////////////////////////////////////

	//static functions
	////////////////////////////////////////////////////////////////////

    static Alfy_Time now();

	////////////////////////////////////////////////////////////////////

	//overloaded operators
	bool operator <  (Alfy_Time& right)		{ if(toString2() <  right.toString2()) return true; else return false; }
	bool operator <= (Alfy_Time& right)		{ if(toString2() <= right.toString2()) return true; else return false; }
	bool operator >  (Alfy_Time& right)		{ if(toString2() >  right.toString2()) return true; else return false; }
	bool operator >= (Alfy_Time& right)		{ if(toString2() >= right.toString2()) return true; else return false; }
	bool operator == (Alfy_Time& right)		{ if(toString2() == right.toString2()) return true; else return false; }
	bool operator != (Alfy_Time& right)		{ if(toString2() != right.toString2()) return true; else return false; }
};

#endif

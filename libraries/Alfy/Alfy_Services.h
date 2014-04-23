#ifndef ALFY_SERVICES_H
#define ALFY_SERVICES_H

#include <string>

#include "Alfy_Strings.h"

class Alfy_Services
{
	char _name[30];
	char _abrev[10];
	double _basePrice;
public:
	//default constructor
	Alfy_Services(const char name[] = "Service", const char abrev[] = "ser", const char price[] = "0.00");

    void name(const char name[]);
	const char* name()	    { return _name; }

	void abrev(const char abrev[]);
	const char* abrev()	    { return _abrev; }

	void basePrice(double price)    { _basePrice = price;  }
	double basePrice()              { return _basePrice;   }
	std::string basPriceString();
};

#endif

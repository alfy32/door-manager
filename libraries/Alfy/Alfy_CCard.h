#ifndef ALFY_CCARD_H
#define ALFY_CCARD_H

#include "Alfy_Date.h"

class Alfy_CCard
{
private:
	int _clientID;
	char _number[8];
	Alfy_Date _expDate;
	short _cvc;
public:
	//default constructor. accepts chars
	//number formats "1234123412341234" or "1234-1234-1234-1234"
	Alfy_CCard(const char clientID[] = "000000000001",
		       const char number[] = "1234123412341234" , const char date[] = "06/11", const char cvc[] = "100");
	//accepts chars and a date
	Alfy_CCard(int clientID, const char number[], Alfy_Date date, const char cvc[]);

	//constructor with shorts
	Alfy_CCard(int clientID, short num1, short num2, short num3, short num4 , short month, short year, short cvc);

	std::string number();
	Alfy_Date expDate();
	std::string expDateString();
	short cvc();
	std::string CVCchar();

	int indexer() { return _clientID; }
};

#endif

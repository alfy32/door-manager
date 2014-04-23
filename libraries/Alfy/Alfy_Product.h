#ifndef ALFY_PRODUCT_H
#define ALFY_PRODUCT_H

#include <string>
#include <cstdlib>

#include "Alfy_Strings.h"

const int BARCODE = 13;		    //size of the barcode string
const int DESC = 31;			//description lenght
const int BRAND = 21;			//brand length

class Alfy_Product
{
private:
    char _barcode[BARCODE];
	char _description[DESC];
	char _brand[BRAND];
	double _wholeSale;
	double _retail;
public:
	//default constructor with doubles
	Alfy_Product(const char barcode[] = "Barcode",
			const char description[] = "Description",
			const char brand[] = "Brand",
			double wholeSale = 0.0, double retail = 0.0);

	//default constructor with chars
	Alfy_Product(const char barcode[], const char description[],
		    const char brand[],
			const char wholeSale[], const char retail[]);

	//set functions
	void barcode(const char[]);
	void description(const char[]);
	void brand(const char[]);
	void wholeSale(const char[]);
	void wholeSale(double);
	void retail(const char[]);
	void retail(double);

	//get functions
	std::string wholeSaleString(int digits=0) const;
	std::string markupString(int digits=0) const;
	std::string retailString(int digits=0) const;

	const char* barcode() const         { return _barcode;                  }
	const char* description() const     { return _description;	            }
	const char* brand() const           { return _brand;	                }
	double wholeSale() const            { return _wholeSale;	            }
	double markup() const;
	double retail() const               { return _retail;	                }

    std::string indexer()               { return _barcode;                  }
};

#endif

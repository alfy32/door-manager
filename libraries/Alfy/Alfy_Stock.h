#ifndef ALFY_STOCK_H
#define ALFY_STOCK_H

#include <string>
#include <stdlib.h>

#include "Alfy_Strings.h"

const int STOCK_BARCODE = 13;		//size of the ID string

class Alfy_Stock
{

private:
    char _barcode[STOCK_BARCODE];
	short _stock;
	short _restock;
public:
	//default constructor
	Alfy_Stock(const char barcode[] = "Barcode", int stock = 0, int restock = 0);

	//constructor that accepts chars
	Alfy_Stock(const char barcode[], const char stock[], const char restock[]);

	//set functions
	void barcode(const char[]);
	void stock(const char stock[]);
	void stock(int stock);
	void restock(const char restock[]);
	void restock(int restock);

	//get functions
	std::string stockString(int digits=0) const;
	std::string restockString(int digits=0) const;

	const char* barcode() const         { return _barcode;      }
	int stock() const                   { return _stock;	    }
	int restock() const                 { return _restock;      }

    std::string indexer()               { return _barcode;      }
};

#endif

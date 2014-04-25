#ifndef DOORSIZE_H
#define DOORSIZE_H

#include <string>
#include <stdlib.h>
#include <iostream>
using namespace std;

class DoorSize
{
	int width;
	int height;
	bool custom;

public:
	DoorSize();
	DoorSize(string);

	void setDimensions(string);
	void setDimensions(int,int,int,int,bool=false);

	string toString();
	string toStringSQL();
	string getWidth();
	string getHeight();
protected:
	bool isNumber(char);
	int findNextNumberIndex(string, int &);
	int getNextNumber(string, int &);
};

#endif

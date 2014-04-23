#ifndef ALFY_TABLE_ROW_H
#define ALFY_TABLE_ROW_H

#include <string>
//#include "Alfy_Table.h"
class Alfy_Table_Row
{
    std::string* _text;
	void* _data;
    int _size;

	std::string _dummy;
public:
    Alfy_Table_Row(int size=0, std::string text[]=0, void* data=0);

    void add_col(std::string text);
    void insert_col(int col, std::string text);
    void remove_col(int col);
    void swap(int col_a, int col_b);
    void clear();

    void text(int col, std::string text_);
    std::string text(int col);
    std::string& operator [] (int col);

    void setData(void* data)			{ _data = data; }
	void* getData()						{ return _data; }

	int size()  { return _size; }
};

#endif

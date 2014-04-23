#ifndef ALFY_TRANSACTION_H
#define ALFY_TRANSACTION_H

#include <string>
#include <cstdlib>

#include "Alfy_Strings.h"
#include "Alfy_Date.h"
#include "Alfy_Time.h"

const int BARCODE_TRAN = 13;

class Alfy_Transaction
{
private:
   int _id;
   int _employee;
   int _client;
   Alfy_Date _date;
   Alfy_Time _time;
   char _barcode[BARCODE_TRAN];
   double _original_price;
   double _actual_price;

public:
    Alfy_Transaction(int employee, int client, Alfy_Date date, Alfy_Time time,
                     const char barcode[], double original_price, double actual_price);

    void id(int i)                  { _id = i;                                  }
    void employee(int e)            { e > 0 ? _employee = e : _employee = 0;    }
    void client(int c)              { c > 0 ? _client = c : _client = 0;        }
    void date(Alfy_Date d)          { _date = d;                                }
    void time(Alfy_Time t)          { _time = t;                                }
    void barcode(const char b[]);
    void original_price(double o)   { _original_price = o;                      }
    void actual_price(double a)     { _actual_price = a;                        }

    int         id()                { return _id;               }
    int         employee()          { return _employee;         }
    int         client()            { return _client;           }
    Alfy_Date   date()              { return _date;             }
    Alfy_Time   time()              { return _time;             }
    std::string barcode()           { return _barcode;          }
    double      original_price()    { return _original_price;   }
    double      actual_price()      { return _actual_price;     }
};

#endif

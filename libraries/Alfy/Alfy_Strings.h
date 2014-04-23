#ifndef ALFYSTRINGS_H
#define ALFYSTRINGS_H

#include <string>

class Alfy_Strings
{
public:
    //string constants
    static const char* day_name[7];
    static const char* day_abrev[7];
    static const char* day_code[7];
    static const char* month_name[13];
    static const char* month_code[13];
    static const char* state_name[51];
    static const char* state_code[51];

    //////////////////////////////////////////////////////////////
    //static functions
    //////////////////////////////////////////////////////////////

    //conversion functions
    ////////////////////////

    static std::string double_to_string(double number, int digits);
    static std::string double_to_string(double number);
    static std::string int_to_string(int number, int digits);
    static std::string int_to_string(int number);
    static float string_to_float(const char number[]);
    static int char_to_int(char number);

    //char array manipulators
    ///////////////////////////

    //to help in discerning the answer of stringsCompare
	enum compare {LESS_THAN = 1 , GREATER_THAN = 0, EQUAL = -1};

    static bool equal(const char[],const char[]);
    static void copy(char destination[] ,const char source[]);
    static int compare(const char[],const char[]);
    static bool starts_with(const char[],const char[]);

    //change case
    ///////////////

    enum CASE { SENTENCE_CASE,  //I have a dog
                LOWERCASE,      //i have a dog
                UPPERCASE,      //I HAVE A DOG
                TOGGLE_CASE,    //i hAVE a dOG
              };

    static std::string change_case(std::string str, int Case);
    static std::string change_case(const char str[], int Case);
    //static std::string& change_case(std::string& str, int Case);
    static char* change_case(char str[], int Case);

    static std::string sentence_case(std::string str);
    static std::string lower_case(std::string str);
    static std::string upper_case(std::string str);
};

#endif

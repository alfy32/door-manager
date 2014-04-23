//All of the under the hood stuff goes here. You have access to
//all widgets that are named. (see fltkgui.h)
#include "functions.h"

float string_to_float(const char number[])
{
    bool negative = false;

    int decimalIndex = 0;

    if(number[0] == '-')
    {
        decimalIndex = 1;
        negative = true;
    }

    while(number[decimalIndex] != '.')
    {
        if(number[decimalIndex] == 0)
        {
            decimalIndex = 0;
            break;
        }
        decimalIndex++;
    }

    int nullIndex = decimalIndex;

    while(number[nullIndex] != 0)
        nullIndex++;

    int num = 0;
    float decimal = 0;
    int start = 0;

    if(negative)
        start = 1;

    if(decimalIndex == 0)
    {
        if(number[0] == '.')
        {
            for(int x = 1; x < nullIndex; x++)
            {
                decimal += (number[x] - 48);
                decimal /= 10;
            }
        }
        else
        {
            for(int x = 0; x < nullIndex; x++)
            {
                num *= 10;
                num += number[x] - 48;
            }

        }
    }
    else
    {
        for(int x = start; x < decimalIndex; x++)
        {
            num *= 10;
            num += number[x] - 48;
        }

        for(int x = nullIndex - 1; x > decimalIndex; x--)
        {
            decimal += (number[x] - 48);
            decimal /= 10;
        }
    }
    if(negative)
        return 0 - (decimal + num);
    else
        return decimal + num;
}

string double_to_string(double number)
{
    std::string negative = "";

    if(number < 0)
    {
        negative = "-";
        number = -number;
    }

    int temp,
        digits = 3;

    for(int x = 20; x >= 0; x--)
    {
        //make temp equal to 10 to the x power
        temp = 1;
        for(int y = 0; y < x; y++)
            temp *= 10;

        if((int)number/temp != 0)
        {
            digits += x;
            break;
        }
    }

    char* num = new char[digits+2];

    num[digits+1] = 0;                                  //sets the null character toterminte the string
    num[digits]   = ((int)((number+.001)*100)%10) + 48; //sets the hundredths
    num[digits-1] = ((int)((number+.001)*10)%10) + 48;  //sets the tenths
    num[digits-2] = '.';                                //sets the decimal point

    //sets all the rest of the numbers
    for(int x = 0; x < digits-2; x++)
    {
        //make temp equal to 10 to the x power
        temp = 1;
        for(int y = 0; y < x; y++)
            temp *= 10;

        //adds one digit at a time
        num[digits-3-x] = ((int)(number/temp)%10) + 48;
    }

	std::string value = negative + num;

	delete [] num;

    return value;
}

string strip_quotes(string source)
{
    string fixed;
	int end = source.length()-1;

	if(source[0] == '"' && source[end] == '"')
    {
        for(int i = 1; i < end ; i++)
			fixed += source[i];

		return fixed;
    }
	else
		return source;
}

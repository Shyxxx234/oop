#include <iostream>
#include <Windows.h>
#include <string>
#include <cmath>


int CharToDigit(char c) 
{
    if (c >= '0' && c <= '9') 
    {
        return c - '0';
    }
    if (c >= 'A' && c <= 'Z') 
    {
        return c - 'A' + 10;
    }
    if (c >= 'a' && c <= 'z') 
    {
        return c - 'a' + 10;
    }
    return -1;
}

char DigitToChar(int digit)
{
    if (digit >= 0 && digit <= 9) 
    {
        return '0' + digit;
    }
    if (digit >= 10 && digit <= 35) 
    {
        return 'A' + (digit - 10);
    }
    return '?'; 
}

bool ValidateRadix(int radix) //
{
    return radix >= 2 && radix <= 36;
}

bool AddCharToIntWithLimitations(bool isNegative, int& result, char digit, int radix)
{
    if (isNegative) //
    {
        if (result < (INT_MIN + digit) / radix)
        {
            return false;
        }
        result = result * radix - digit;
    }
    else
    {
        if (result > (INT_MAX - digit) / radix)
        {
            return false;
        }
        result = result * radix + digit;
    }
    return true;
}

int StringToInt(const std::string& str, int radix, bool& wasError)
{
    wasError = false;

    if (!ValidateRadix(radix))
    {
        wasError = true;
        return 0;
    }

    bool isNegative = false;
    std::string numberStr = str;

    if (numberStr[0] == '-')
    {
        isNegative = true;
        if (numberStr.length() == 1)
        {
            wasError = true;
            return 0;
        }
    }

    size_t startIndex = 0;

    if (numberStr[0] == '-' || numberStr[0] == '+')
    {
        startIndex = 1;
    }

    int result = 0; //

    for (size_t i = startIndex; i < numberStr.length(); i++)
    {
        int digit = CharToDigit(numberStr[i]);

        if (digit == -1 || digit >= radix || !AddCharToIntWithLimitations(isNegative, result, digit, radix))
        {
            wasError = true;
            return 0;
        }
    }

    return result;
}

std::string IntToString(int n, int radix, bool& wasError)
{
    wasError = false;

    if (!ValidateRadix(radix))
    {
        wasError = true;
        return "";
    }

    if (n == 0)
    {
        return "0";
    }

    std::string result;
    bool isNegative = (n < 0);
    unsigned int un = isNegative ? static_cast<unsigned int>(-n) : static_cast<unsigned int>(n);

    while (un > 0)
    {
        unsigned int digit = un % radix;
        result.push_back(DigitToChar(digit));
        un /= radix;
    }

    if (isNegative)
    {
        result.push_back('-');
    }

    reverse(result.begin(), result.end());

    return result;
}

int main(int argCount, char* argVect[])
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    if (argCount != 4)
    {
        std::cerr << "Usage: radix.exe <source notation> <destination notation> <value>" << std::endl;
        return 1;
    }

    bool wasError = false;
    int sourceRadix = StringToInt(argVect[1], 10, wasError); //use myself func
    int destinationRadix = StringToInt(argVect[2], 10, wasError);
    int number = StringToInt(argVect[3], sourceRadix, wasError);

    if (wasError)
    {
        std::cerr << "Error converting string to int";
        return 1;
    }

    std::string result = IntToString(number, destinationRadix, wasError);

    if (wasError)
    {
        std::cerr << "Error converting int to string";
        return 1;
    }

    std::cout << result << std::endl;
}

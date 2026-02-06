#include <iostream>
#include <Windows.h>
#include <string>
#include <cmath>

using namespace std;

int CharToDigit(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    else if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 10;
    }
    else if (c >= 'a' && c <= 'z') {
        return c - 'a' + 10;
    }
    return -1;
}

char DigitToChar(int digit) {
    if (digit >= 0 && digit <= 9) {
        return '0' + digit;
    }
    else if (digit >= 10 && digit <= 35) {
        return 'A' + (digit - 10);
    }
    return '?'; 
}

int StringToInt(const string& str, int radix, bool& wasError)
{
    wasError = false;

    if (radix < 2 || radix > 36 || str.empty())
    {
        wasError = true;
        return 0;
    }

    bool isNegative = false;
    string numberStr = str;

    if (numberStr[0] == '-')
    {
        isNegative = true;

        if (numberStr.length() == 1)
        {
            wasError = true;
            return 0;
        }
    }

    if (numberStr[0] == '-' || numberStr[0] == '+')
    {
        numberStr.erase(0, 1);
    }

    long long result = 0;
    long long maxBeforeMultiply = (static_cast<long long>(INT_MAX) / radix);

    for (size_t i = 0; i < numberStr.length(); i++)
    {
        int digit = CharToDigit(numberStr[i]);
        if (result >= maxBeforeMultiply)
        {
            wasError = true;
            return 0;
        }
        result = result * radix + digit;
    }
    if (isNegative)
    {
        result *= -1;
    }
    return static_cast<int>(result);
}

string IntToString(int n, int radix, bool& wasError)
{
    wasError = false;

    if (radix < 2 || radix > 36)
    {
        wasError = true;
        return "";
    }

    if (n == 0)
    {
        return "0";
    }

    string result;
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
        cerr << "Usage: radix.exe <source notation> <destination notation> <value>" << endl;
        return 1;
    }

    int sourceRadix = stoi(argVect[1]);
    int destinationRadix = stoi(argVect[2]);
    bool wasError = false;
    string value = argVect[3];

    int number = StringToInt(value, sourceRadix, wasError);

    if (wasError)
    {
        cerr << "Error converting string to int";
        return 1;
    }

    string result = IntToString(number, destinationRadix, wasError);

    if (wasError)
    {
        cerr << "Error converting int to string";
        return 1;
    }

    std::cout << result << endl;
}

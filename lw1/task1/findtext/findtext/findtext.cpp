#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

int main(int argCount, char* argVect[])
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    if (argCount != 3)
    {
        cerr << "Usage: findtext.exe <file name> <text to search>" << endl;
        return 1;
    }

    string filename = argVect[1];
    string searchText = argVect[2];

    if (searchText.empty()) {
        cerr << "Error: Search text cannot be empty" << endl;
        return 1;
    }
    
    ifstream fin;
    fin.open(static_cast<string>(filename));
    if (!fin.is_open())
    {
        cerr << "Can't open the file named " << filename << endl;
        return 1;
    }

    string line;
    bool found = false;
    int lineNumber = 0;

    while (getline(fin, line))
    {
        lineNumber++;
        if (line.find(searchText) != string::npos)
        {
            cout << lineNumber << endl;
            found = true;
        }
    }

    if (!found)
    {
        cout << "Text not found" << endl;
    }
    return 0;
}


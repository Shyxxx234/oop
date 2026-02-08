#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

bool WriteFindTextInStream(std::istream& input, const std::string& searchText) 
{
    std::string line;
    bool found = false;
    int lineNumber = 0;

    while (std::getline(input, line)) 
    {
        lineNumber++;
        if (line.find(searchText) != std::string::npos) 
        {
            std::cout << lineNumber << std::endl;
            found = true;
        }
    }
    return found;
}

int main(int argCount, char* argVect[]) 
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    if (argCount != 3) 
    {
        std::cerr << "Usage: findtext.exe <file name> <text to search>" << std::endl;
        return 1;
    }

    std::string filename = argVect[1];
    std::string searchText = argVect[2];

    if (searchText.empty()) 
    {
        std::cerr << "Error: Search text cannot be empty" << std::endl;
        return 1;
    }

    std::ifstream fin(filename);
    if (!fin.is_open()) 
    {
        std::cerr << "Error: Can't open the file named " << filename << std::endl;
        return 1;
    }

    if (!WriteFindTextInStream(fin, searchText))
    {
        std::cout << "Text not found" << std::endl;
    }

    return 0;
}

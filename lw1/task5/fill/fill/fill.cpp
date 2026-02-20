#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <fstream>
#include <queue>

const char EMPTY = ' ';
const char START = 'O';
const char FILLED = '.';
const int MAX_IMAGE_SIZE = 100;

void PrintHelp()
{
    std::cout << "fill.exe - contour filling program\n"
        << "====================================\n"
        << "\n"
        << "Usage:\n"
        << "  fill.exe <input file> <output file>  - read image from file,\n"
        << "                                         perform filling and save result\n"
        << "  fill.exe -h                          - show this help message\n"
        << "  fill.exe                             - stdin/stdout mode (no parameters)\n"
        << "\n"
        << "Input format:\n"
        << "  Image consists of the following characters:\n"
        << "    '#' - contour border (not filled)\n"
        << "    'O' - start point for filling\n"
        << "    '.' - fill symbol (appears as result of filling)\n"
        << "    ' ' - empty space (gets filled)\n"
        << "\n"
        << "Limitations:\n"
        << "  - Maximum image size: 100x100 pixels\n"
        << "  - Rows and columns beyond 100 are ignored\n"
        << "\n";
}

void ReadImage(std::istream& fin, std::vector<std::vector<char>>& image)
{
    std::string line;
    size_t row = 0;

    while (getline(fin, line) && row < MAX_IMAGE_SIZE) //constant 100
    {
        std::vector<char> rowVec;

        size_t maxCols = (line.length() < MAX_IMAGE_SIZE) ? line.length() : MAX_IMAGE_SIZE;

        for (size_t col = 0; col < maxCols; col++)
        {
            rowVec.push_back(line[col]);
        }

        image.push_back(rowVec);
        row++;
    }
}

bool InitializeQueueWithStartPoints(std::vector<std::vector<char>>& image, std::queue<std::pair<size_t, size_t>>& queue)
{
    bool found = false;
    for (size_t i = 0; i < image.size(); i++)
    {
        for (size_t j = 0; j < image[i].size(); j++)
        {
            if (image[i][j] == START)
            {
                found = true;
                queue.push({ i, j });
            }
        }
    }

    return found;
}

void EnsureSize(std::vector<std::vector<char>>& image, size_t row, size_t col)
{
    if (row >= image.size())
    {
        image.resize(row + 1);
    }
    if (col >= image[row].size())
    {
        image[row].resize(col + 1, EMPTY);
    }
}

void FillContours(std::vector<std::vector<char>>& image, std::queue<std::pair<size_t, size_t>>& queue) //Split in several funcs
{
    while (!queue.empty())
    {
        std::pair<size_t, size_t> point = queue.front();
        size_t row = point.first;
        size_t col = point.second;
        queue.pop();

        if (row >= MAX_IMAGE_SIZE || col >= MAX_IMAGE_SIZE)
        {
            continue;
        }

        EnsureSize(image, row, col);

        if (image[row][col] != EMPTY && image[row][col] != START)
        {
            continue;
        }

        if (image[row][col] == EMPTY)
        {
            image[row][col] = FILLED;
        }

        if (row > 0)
        {
            EnsureSize(image, row - 1, col);
            if (image[row - 1][col] == EMPTY)
            {
                queue.push({ row - 1, col });
            }
        }
        if (row + 1 < MAX_IMAGE_SIZE)
        {
            EnsureSize(image, row + 1, col);
            if (image[row + 1][col] == EMPTY)
            {
                queue.push({ row + 1, col });
            }
        }
        if (col > 0)
        {
            EnsureSize(image, row, col - 1);
            if (image[row][col - 1] == EMPTY)
            {
                queue.push({ row, col - 1 });
            }
        }
        if (col + 1 < MAX_IMAGE_SIZE)
        {
            EnsureSize(image, row, col + 1);
            if (image[row][col + 1] == EMPTY)
            {
                queue.push({ row, col + 1 });
            }
        }
    }
}

void PrintImageToFile(std::ostream& fout, std::vector<std::vector<char>>& image)
{
    for (size_t i = 0; i < image.size(); i++)
    {
        for (size_t j = 0; j < image[i].size(); j++)
        {
            fout << image[i][j];
        }
        fout << std::endl;
    }
}

int main(int argCount, char* argVect[])
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::vector<std::vector<char>> image; //using
    std::ifstream fin;
    std::ofstream fout;
    bool isStdinMode = false;

    if (argCount == 2 && std::string(argVect[1]) == "-h")
    {
        PrintHelp();
        return 0;
    }
    else if (argCount == 1)
    {
        isStdinMode = true;
        ReadImage(std::cin, image);
    }
    else if (argCount == 3)
    {
        std::string filenameIn = argVect[1];
        std::string filenameOut = argVect[2];

        fin.open(filenameIn);
        fout.open(filenameOut);

        if (!fin.is_open() || !fout.is_open())
        {
            std::cout << "ERROR" << std::endl;
            return 1;
        }

        ReadImage(fin, image);
        fin.close();
    }
    else
    {
        std::cout << "ERROR" << std::endl;
        return 1;
    }

    std::queue<std::pair<size_t, size_t>> queue{};

    if (InitializeQueueWithStartPoints(image, queue))
    {
        FillContours(image, queue);
    }

    if (isStdinMode)
    {
        PrintImageToFile(std::cout, image);
        return 0;
    }
    else
    {
        PrintImageToFile(fout, image);
        fout.close();
        return 0;
    }
}
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <iomanip>
#include <cmath>
#include <string>

void PrintHelpMessage()
{
	std::cout << "Usage: invert.exe [filename]\n";
	std::cout << "If [filename] is omitted, the program reads from stdin.\n";
	std::cout << "Options:\n  -h  Show this help message." << std::endl;
}

bool ReadMatrix(std::istream& input, std::vector<std::vector<double>>& matrix)
{
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			if (!(input >> matrix[row][col]))
			{
				std::cout << "Invalid matrix format" << std::endl;
				return false;
			}
		}
	}
	return true;
}

double GetDeterminant(std::vector<std::vector<double>>& matrix)
{
	double positive = matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0]
		+ matrix[0][2] * matrix[1][0] * matrix[2][1];

	double negative = matrix[0][2] * matrix[1][1] * matrix[2][0] + matrix[0][0] * matrix[1][2] * matrix[2][1]
		+ matrix[0][1] * matrix[1][0] * matrix[2][2];

	return positive - negative;
}

bool InvertMatrix(std::vector<std::vector<double>>& matrix) {
	double det = GetDeterminant(matrix);
	if (abs(det) < 1e-9) {
		std::cout << "Non-invertible" << std::endl;
		return false;
	}

	std::vector<std::vector<double>> res(3, std::vector<double>(3));

	double invDet = 1.0 / det;

	res[0][0] = (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) * invDet;
	res[0][1] = (matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2]) * invDet;
	res[0][2] = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) * invDet;

	res[1][0] = (matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2]) * invDet;
	res[1][1] = (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]) * invDet;
	res[1][2] = (matrix[1][0] * matrix[0][2] - matrix[0][0] * matrix[1][2]) * invDet;

	res[2][0] = (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]) * invDet;
	res[2][1] = (matrix[2][0] * matrix[0][1] - matrix[0][0] * matrix[2][1]) * invDet;
	res[2][2] = (matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1]) * invDet;

	matrix = res;
	return true;
}

int main(int argCount, char* argVect[])
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	bool success = false;
	std::vector<std::vector<double>> matrix(3, std::vector<double>(3));

	if (argCount > 1)
	{
		std::string arg = argVect[1];
		if (arg == "-h")
		{
			PrintHelpMessage();
			return 0;
		}
		std::ifstream fin;
		fin.open(arg);
		if (!fin.is_open())
		{
			std::cout << "Can't open file named " << arg << std::endl;
			return 1;
		}
		success = ReadMatrix(fin, matrix);
	}
	else
	{
		success = ReadMatrix(std::cin, matrix);
	}

	if (success)
	{
		if (InvertMatrix(matrix))
		{
			std::cout << std::fixed << std::setprecision(3);
			for (int row = 0; row < 3; row++) 
			{
				for (int col = 0; col < 3; col++) 
				{
					std::cout << (matrix[row][col] == 0.0 ? 0.0 : matrix[row][col]) << (col == 2 ? "" : "\t");
				}
				std::cout << std::endl;
			}
		}
	}
	return 0;
}


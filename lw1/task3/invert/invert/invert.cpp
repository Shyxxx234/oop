#include <iostream>
#include <fstream>
#include <Windows.h>
#include <array>
#include <iomanip>
#include <cmath>
#include <string>

using Matrix = std::array<std::array<double, 3>, 3>;

void PrintHelpMessage()
{
	std::cout << "Usage: invert.exe [filename]\n";
	std::cout << "If [filename] is omitted, the program reads from stdin.\n";
	std::cout << "Options:\n  -h  Show this help message." << std::endl;
}

bool ReadMatrix(std::istream& input, Matrix& matrix)
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

double GetDeterminant(Matrix& matrix)
{
	double positive = matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0]
		+ matrix[0][2] * matrix[1][0] * matrix[2][1];

	double negative = matrix[0][2] * matrix[1][1] * matrix[2][0] + matrix[0][0] * matrix[1][2] * matrix[2][1]
		+ matrix[0][1] * matrix[1][0] * matrix[2][2];

	return positive - negative;
}

Matrix InvertMatrixByMinors(Matrix& matrix, double invDet)
{
	Matrix res;

	res[0][0] = (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) * invDet; 
	res[0][1] = (matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2]) * invDet;
	res[0][2] = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) * invDet;

	res[1][0] = (matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2]) * invDet;
	res[1][1] = (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]) * invDet;
	res[1][2] = (matrix[1][0] * matrix[0][2] - matrix[0][0] * matrix[1][2]) * invDet;

	res[2][0] = (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]) * invDet;
	res[2][1] = (matrix[2][0] * matrix[0][1] - matrix[0][0] * matrix[2][1]) * invDet;
	res[2][2] = (matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1]) * invDet;

	return res;
}

bool InvertMatrix(Matrix& matrix) 
{
	double det = GetDeterminant(matrix);
	if (det == 0) 
	{
		return false;
	}

	Matrix res;

	double invDet = 1.0 / det;

	matrix = InvertMatrixByMinors(matrix, invDet);
	return true;
}

void PrintMatrix(std::ostream& out, Matrix& matrix)
{
	std::cout << std::fixed << std::setprecision(3);
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			out << matrix[row][col] << (col == 2 ? "" : "\t");
		}
		out << std::endl;
	}
}

int main(int argCount, char* argVect[])
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	bool success = false;
	Matrix matrix;

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
			PrintMatrix(std::cout, matrix);
		}
		else
		{
			std::cout << "Non-invertible" << std::endl;
		}
	}
	
	return 0;
}

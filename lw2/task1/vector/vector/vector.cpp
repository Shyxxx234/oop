#include <fstream>
#include <algorithm>
#include <iomanip>
#include <string>
#include "vector.h"

void ReadNumbers(std::istream& fin, std::vector<double>& vect)
{
	std::string number;
	while (fin >> number)
	{
		vect.push_back(std::stod(number));
	}
}

std::vector<double> ProcessNumbers(const std::vector<double>& vectIn)
{
	double minElement = *std::min_element(vectIn.begin(), vectIn.end());
	std::vector<double> vect = vectIn;

	for (size_t i = 0; i < vect.size(); i++)
	{
		vect[i] *= minElement;
	}
	return vect;
}

void PrintSortedNumbers(std::ostream& fout, const std::vector<double>& vect)
{
	std::vector<double> sortedVect = vect;
	std::sort(sortedVect.begin(), sortedVect.end());

	fout << std::fixed << std::setprecision(3);
	for (size_t i = 0; i < sortedVect.size(); i++)
	{
		fout << sortedVect[i] << ' ';
	}
	fout << std::endl;
}

int main()
{
	try 
	{
		std::vector<double> vect;
		ReadNumbers(std::cin, vect);
		vect = ProcessNumbers(vect);
		PrintSortedNumbers(std::cout, vect);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

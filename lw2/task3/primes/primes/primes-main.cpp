#include "primes.h";
#include <string>

int main(int argCount, char* argVect[])
{
	if (argCount != 2)
	{
		throw std::invalid_argument("Usage: prime <upperBound>");
	}

	size_t upperBound = std::stoi(argVect[1]);
	if (upperBound < 0 || upperBound > MAX_BOUND)
	{
		throw std::out_of_range("Upper bound should be in [0, 10^8]");
	}
	PrintPrimeNumbers(std::cout, GeneratePrimeNumbersSet(upperBound));
}
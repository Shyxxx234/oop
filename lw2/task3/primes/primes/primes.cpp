#include <vector>
#include <exception>
#include <cmath>
#include <string>
#include "primes.h"

Sieve ToSieve(size_t upperBound)
{
	if (upperBound < 2)
	{
		return {};
	}

	Sieve sieve(upperBound + 1, true);
	sieve[0] = sieve[1] = false;

	for (size_t i = 4; i <= upperBound; i += 2)
	{
		sieve[i] = false;
	}

	size_t limit = static_cast<size_t>(std::sqrt(upperBound));

	for (size_t i = 3; i <= limit; i += 2)
	{
		if (sieve[i])
		{
			for (size_t j = i * i; j <= upperBound; j += 2 * i)
			{
				sieve[j] = false;
			}
		}
	}
	return sieve;
}


Primes GeneratePrimeNumbersSet(size_t upperBound)
{
	Primes primes;

	if (upperBound < 0 || upperBound > MAX_BOUND)
	{
		throw std::out_of_range("Upper bound should be in [0, 10^8]");
	}

	if (upperBound < 2)
	{
		return primes;
	}

	
	Sieve sieve = ToSieve(upperBound);

	for (size_t i = 0; i <= upperBound; i++)
	{
		if (sieve[i])
		{
			primes.insert(i);
		}
	}

	return primes;
}

void PrintPrimeNumbers(std::ostream& out, Primes primes)
{
	for (auto prime : primes)
	{
		out << prime << std::endl;
	}
}

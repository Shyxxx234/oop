#pragma once
#include <set>
#include <iostream>
#include <vector>

using Primes = std::set<int>;
using Sieve = std::vector<bool>;

const int MAX_BOUND = 100'000'000;

void PrintPrimeNumbers(std::ostream& out, Primes primes);
Primes GeneratePrimeNumbersSet(size_t upperBound);

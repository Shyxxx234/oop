#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "primes.h"
#include <stdexcept>
#include <chrono>



TEST_CASE("Prime numbers generation")
{
	// Basic tests
	SECTION("Basic tests") {
		Primes prime = { 2, 3, 5, 7, 11, 13, 17, 19, 23 };
		REQUIRE(GeneratePrimeNumbersSet(25) == prime);

		prime = { 2 };
		REQUIRE(GeneratePrimeNumbersSet(2) == prime);

		prime = { };
		REQUIRE(GeneratePrimeNumbersSet(1) == prime);
		REQUIRE(GeneratePrimeNumbersSet(0) == prime);
	}
	#ifdef DEBUG_MODE
	// Test for the count of prime numbers up to 100 million
	SECTION("Count primes up to 100 million") {
		auto start = std::chrono::high_resolution_clock::now();
		Primes prime = GeneratePrimeNumbersSet(100'000'000);
		auto end = std::chrono::high_resolution_clock::now();

		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

		REQUIRE(prime.size() == 5'761'455);
		// Performance check (should be less than 12 seconds)
		REQUIRE(duration.count() < 12000);
	}
	#endif

	// Boundary value tests
	SECTION("Boundary tests") {
		REQUIRE_THROWS_AS(GeneratePrimeNumbersSet(-1), std::out_of_range);
		REQUIRE_THROWS_AS(GeneratePrimeNumbersSet(100'000'001), std::out_of_range);
	}

	// Small range tests
	SECTION("Small ranges") {
		Primes primes3 = GeneratePrimeNumbersSet(3);
		REQUIRE(primes3 == Primes({ 2, 3 }));

		Primes primes5 = GeneratePrimeNumbersSet(5);
		REQUIRE(primes5 == Primes({ 2, 3, 5 }));

		Primes primes10 = GeneratePrimeNumbersSet(10);
		REQUIRE(primes10 == Primes({ 2, 3, 5, 7 }));

		Primes primes20 = GeneratePrimeNumbersSet(20);
		REQUIRE(primes20 == Primes({ 2, 3, 5, 7, 11, 13, 17, 19 }));
	}
	//Test for 6, 7, 8
	SECTION("Corner test") {
		Primes primes6 = GeneratePrimeNumbersSet(6);
		REQUIRE(primes6 == Primes({ 2, 3, 5 }));

		Primes primes7 = GeneratePrimeNumbersSet(7);
		REQUIRE(primes7 == Primes({ 2, 3, 5, 7 }));

		Primes primes8 = GeneratePrimeNumbersSet(8);
		REQUIRE(primes8 == Primes({ 2, 3, 5, 7 }));
	}
	
	// Verify that all numbers in the set are actually prime
	SECTION("Verify all numbers are prime") {
		Primes primes = GeneratePrimeNumbersSet(1000);

		for (int prime : primes) {
			bool isPrime = true;
			for (int i = 2; i <= std::sqrt(prime); i++) {
				if (prime % i == 0) {
					isPrime = false;
					break;
				}
			}
			REQUIRE(isPrime);
		}
	}

	// Verify that there are no missing prime numbers
	SECTION("No missing primes") {
		Primes primes = GeneratePrimeNumbersSet(100);
		std::vector<int> knownPrimes = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
										31, 37, 41, 43, 47, 53, 59, 61, 67,
										71, 73, 79, 83, 89, 97 };

		std::vector<int> result(primes.begin(), primes.end());
		REQUIRE(result == knownPrimes);
	}
}

TEST_CASE("Print function tests")
{
	SECTION("Print empty set") {
		std::stringstream ss;
		PrintPrimeNumbers(ss, Primes());
		REQUIRE(ss.str().empty());
	}

	SECTION("Print single prime") {
		std::stringstream ss;
		PrintPrimeNumbers(ss, Primes({ 2 }));
		REQUIRE(ss.str() == "2\n");
	}

	SECTION("Print multiple primes") {
		std::stringstream ss;
		PrintPrimeNumbers(ss, Primes({ 2, 3, 5, 7, 11 }));
		REQUIRE(ss.str() == "2\n3\n5\n7\n11\n");
	}
}
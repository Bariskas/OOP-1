#include "stdafx.h"
#include "PrimeNumbers.h"

using namespace std;

void PrintSet(set<int>& set)
{
	copy(set.begin(), set.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
}

void CheckForArguments(int argc)
{
	if (argc != 2)
	{
		throw invalid_argument("Invalid arguments count!\nUsage: PrimeNumbers.exe <upper bound>");
	}
}

void ValidateUpperBoundValue(size_t value)
{
	const int maxValue = 100000000;

	if (value > maxValue)
	{
		throw invalid_argument("Upper bound must be less or equal than 100 000 000!");
	}
}

int main(int argc, char *argv[])
{
	try
	{
		CheckForArguments(argc);
		size_t value = stoi(argv[1]);
		ValidateUpperBoundValue(value);
		set<int> primeNumbersSet = GeneratePrimeNumbersSet(value);
		PrintSet(primeNumbersSet);
	}
	catch (exception const& e)
	{
		cout << e.what() << endl;
		return 1;
	}
	return 0;
}
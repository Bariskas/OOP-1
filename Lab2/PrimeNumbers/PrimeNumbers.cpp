#include "stdafx.h"
#include "PrimeNumbers.h"

using namespace std;

set<int> ProcessPrimeNumbersToSet(vector<bool>& primeNumbers)
{
	set<int> primeSet;

	for (size_t i = 2; i < primeNumbers.size(); i++)
	{
		if (primeNumbers[i])
		{
			primeSet.insert(primeSet.end(), (int)i);
		}
	}
	return move(primeSet);
}

set<int> GeneratePrimeNumbersSet(size_t upperBound)
{
	vector<bool> primeNumbers(upperBound + 1, true);

	size_t step = 2;
	size_t stepSquared = step * step;
	size_t start = stepSquared;

	while (stepSquared <= upperBound)
	{
		for (size_t i = start; i <= upperBound; i += step)
		{
			primeNumbers[i] = false;
		}
		if (step == 2)
		{
			step = 3;
			stepSquared = step * step;
		}
		while (stepSquared <= upperBound && !primeNumbers[stepSquared])
		{
			step += 2;
			stepSquared = step * step;
		}
		start = stepSquared;
	}

	return ProcessPrimeNumbersToSet(primeNumbers);
}


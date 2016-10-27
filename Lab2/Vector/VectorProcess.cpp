#include "stdafx.h"
#include "VectorProcess.h"

bool CompareNumbers(const double a, const double b)
{
	return a < b;
}

void ProcessVector(vector<double>& numbers)
{
	/* Умножить каждый элемент массива на максимальный элемент исходного массива
	и разделить на минимальный элемент исходного массива */
	if (!numbers.empty())
	{
		const double minNumber = *min_element(numbers.begin(), numbers.end());
		if (minNumber <= DBL_EPSILON)
		{
			throw exception("Can't divide by zero!");
		}
		const double maxNumber = *max_element(numbers.begin(), numbers.end());
		transform(numbers.begin(), numbers.end(), numbers.begin(), [minNumber, maxNumber](double value)
		{
			return value * maxNumber / minNumber;
		});
	}
}
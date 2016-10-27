#include "stdafx.h"
#include "VectorProcess.h"

void ProcessVector(vector<double>& numbers)
{
	/* Умножить каждый элемент массива на максимальный элемент исходного массива
	и разделить на минимальный элемент исходного массива */
	if (!numbers.empty())
	{
		auto minMaxIterators = minmax_element(numbers.begin(), numbers.end());
		double minValue = *minMaxIterators.first;
		double maxValue = *minMaxIterators.second;
		if (abs(minValue) <= DBL_EPSILON)
		{
			throw runtime_error("Can't divide by zero!");
		}
		transform(numbers.begin(), numbers.end(), numbers.begin(), [minValue, maxValue](double value)
		{
			return value / minValue * maxValue;
		});
	}
}
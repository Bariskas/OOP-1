#include <limits>
#include "Radix.h"

using namespace std;

int MultiplyWithOverflowCheck(unsigned const int multiplier1, unsigned const int multiplier2)
{
	if (multiplier2 != 0 && multiplier1 > INT_MAX / multiplier2)
	{
		throw overflow_error("Overflow on calculating value!");
	}
	return multiplier1 * multiplier2;
}

int AddWithOverflowCheck(unsigned const int add1, unsigned const int add2)
{
	if (add1 > INT_MAX - add2)
	{
		throw overflow_error("Overflow on calculating value!");
	}
	return add1 + add2;
}

int CharToNumber(const char ch)
{
	const int DIGIT_NUMBERS_COUNT = 10;
	if (isdigit(ch))
	{
		return static_cast<int>(ch - '0');
	}
	else if (isupper(ch))
	{
		return static_cast<int>(ch - 'A' + DIGIT_NUMBERS_COUNT);
	}
	else if (islower(ch))
	{
		return static_cast<int>(ch - 'a' + DIGIT_NUMBERS_COUNT);
	}
	else if (ch == '-')
	{
		return -1;
	}
	throw invalid_argument("Can't convert char to number");
	return 0;
}

char NumberToChar(const int number)
{
	const int DIGIT_NUMBERS_COUNT = 10;

	if (number >= DIGIT_NUMBERS_COUNT)
	{
		return number + 'A' - DIGIT_NUMBERS_COUNT;
	}
	else
	{
		return number + '0';
	}
}

void ValidateNotation(int notation)
{
	const int MIN_ALLOWED_NOTATION = 2;
	const int MAX_ALLOWED_NOTATION = 36;

	if (notation < MIN_ALLOWED_NOTATION || notation > MAX_ALLOWED_NOTATION)
	{
		throw invalid_argument("Notation must be between 2 and 36 value!");
	}
}

void ValidateStringValue(string const& value)
{
	const string BOUNDARY_VALUE_STR = (value[0] == '-') ? to_string(INT_MIN) : to_string(INT_MAX);
	const size_t BOUNDATRY_VALUE_LENGTH = BOUNDARY_VALUE_STR.length();

	size_t valueLength = value.length();

	if (valueLength > BOUNDATRY_VALUE_LENGTH
		|| (valueLength == BOUNDATRY_VALUE_LENGTH && value > BOUNDARY_VALUE_STR))
	{
		throw overflow_error("Input value overflow!");
	}
}

void ValidateValue(string const& value, const int notation)
{
	const int DECIMAL_RADIX = 10;
	const size_t valueLength = value.length();

	if (notation == DECIMAL_RADIX)
	{
		ValidateStringValue(value);
	}

	for (size_t i = 0; i < valueLength; i++)
	{
		try
		{
			if (CharToNumber(value[i]) >= notation)
			{
				throw invalid_argument("Wrong char in current notation!");
			}
		}
		catch (invalid_argument)
		{
			throw invalid_argument("Value must be a number in specified notation!");
		}
	}
}

int ConvertToDecimal(string const& value, const int sourceNotation)
{
	const int DECIMAL_RADIX = 10;
	int result = 0;
	if (sourceNotation == DECIMAL_RADIX)
	{
		result = stoi(value);
	}
	else
	{
		const size_t valueLength = value.length();
		const bool isNegative = (value[0] == '-');

		int startPos = (isNegative) ? 1 : 0;
		result = CharToNumber(value[startPos]);
		for (size_t i = startPos + 1; i < valueLength; i++)
		{
			result = MultiplyWithOverflowCheck(result, sourceNotation);
			result = AddWithOverflowCheck(result, CharToNumber(value[i]));
		}
		if (isNegative)
		{
			result *= -1;
		}
	}
	return result;
}

string ConvertToDestination(int decimalValue, int destinationNotation)
{
	const int DECIMAL_RADIX = 10;
	if (destinationNotation == DECIMAL_RADIX)
	{
		return to_string(decimalValue);
	}
	else
	{
		string result;
		int balance = abs(decimalValue);
		while (balance >= destinationNotation)
		{
			result.push_back(NumberToChar(balance % destinationNotation));
			balance /= destinationNotation;
		}
		result.push_back(NumberToChar(balance));
		if (decimalValue < 0)
		{
			result.push_back('-');
		}

		return { result.rbegin(), result.rend() };
	}
}

string ConvertRadix(const int sourceNotation, const int destinationNotation, string value)
{
	string result;
	if (sourceNotation == destinationNotation)
	{
		result = value;
	}
	else
	{
		int decimalValue = ConvertToDecimal(value, sourceNotation);
		result = ConvertToDestination(decimalValue, destinationNotation);
	}
	return result;
}
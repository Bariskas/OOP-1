#include "Radix.h"

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

int ExpWithOverflowCheck(unsigned const int number, unsigned const int degree)
{
	if (degree == 0)
	{
		return 1;
	}

	int result = number;
	for (unsigned int i = 1; i < degree; i++)
	{
		result = MultiplyWithOverflowCheck(result, number);
	}
	return result;
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

bool CheckStrNumberValueOverflow(string const& value)
{
	const size_t valueLength = value.length();
	const string INT_MAX_STR = to_string(INT_MAX);
	const size_t INT_MAX_STR_LENGTH = INT_MAX_STR.length();

	return (value[0] != '-' && (valueLength > INT_MAX_STR_LENGTH
		|| (valueLength == INT_MAX_STR_LENGTH && value > INT_MAX_STR)));
}

bool CheckStrNumberValueUnderflow(string const& value)
{
	const size_t valueLength = value.length();
	const string INT_MIN_STR = to_string(INT_MIN);
	const size_t INT_MIN_STR_LENGTH = INT_MIN_STR.length();

	return (value[0] == '-' && (valueLength > INT_MIN_STR_LENGTH
		|| (valueLength == INT_MIN_STR_LENGTH && value > INT_MIN_STR)));
}

void ValidateValue(string const& value, const int notation)
{
	const int DECIMAL_RADIX = 10;
	const size_t valueLength = value.length();

	if (notation == DECIMAL_RADIX)
	{
		if (CheckStrNumberValueOverflow(value))
		{
			throw overflow_error("Input value overflow!");
		}
		if (CheckStrNumberValueUnderflow(value))
		{
			throw underflow_error("Input value underflow!");
		}
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

		for (size_t i = (isNegative) ? 1 : 0; i < valueLength; i++)
		{
			int expResult = ExpWithOverflowCheck(sourceNotation, valueLength - i - 1);
			int multiplyResult = MultiplyWithOverflowCheck(CharToNumber(value[i]), expResult);
			result = AddWithOverflowCheck(result, multiplyResult);
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
			result += NumberToChar(balance % destinationNotation);
			balance /= destinationNotation;
		}
		result += NumberToChar(balance);
		if (decimalValue < 0)
		{
			result += '-';
		}

		return{ result.rbegin(), result.rend() };
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
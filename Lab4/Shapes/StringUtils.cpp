#include "stdafx.h"
#include "StringUtils.h"

using namespace std;

uint8_t StrToUint8(std::string const& str)
{
	uint8_t result = 0;

	try
	{
		if (str.empty())
		{
			throw exception();
		}

		int number = stoi(str);
		if (number >= 0 && number <= 255)
		{
			result = static_cast<uint8_t>(number);
		}
		else
		{
			throw exception();
		}
	}
	catch (exception const&)
	{
		throw runtime_error("Uint8 value must be digit between 0 and 255");
	}

	return result;
}

double StrToDouble(std::string const& str)
{
	double result = 0.;

	try
	{
		if (str.empty())
		{
			throw exception();
		}

		result = stof(str);
	}
	catch (exception const&)
	{
		throw runtime_error("Double value must be floating point number");
	}

	return result;
}

bool CheckNumberOfParams(std::string const& str, int count)
{
	vector<string> param;
	boost::split(param, str, bind2nd(equal_to<char>(), ' '));

	return param.size() == count;
}
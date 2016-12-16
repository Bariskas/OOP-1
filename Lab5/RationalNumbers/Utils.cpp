#include "stdafx.h"
#include "Utils.h"

using namespace std;

int Gcd(int a, int b)
{
	while (b)
	{
		a %= b;
		swap(a, b);
	}

	return a;
}

int Lcm(int a, int b)
{
	return a / Gcd(a, b) * b;
}

int StrToInt(std::string const& str)
{
	int result = 0;

	try
	{
		if (str.empty())
		{
			throw exception();
		}

		result = stoi(str);
	}
	catch (exception const&)
	{
		throw runtime_error("Wrong int value in string!");
	}

	return result;
}
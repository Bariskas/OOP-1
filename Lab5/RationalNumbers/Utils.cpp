#include "stdafx.h"
#include "Utils.h"

int Gcd(int a, int b)
{
	while (b)
	{
		a %= b;
		std::swap(a, b);
	}

	return a;
}

int Lcm(int a, int b)
{
	return a / Gcd(a, b) * b;
}

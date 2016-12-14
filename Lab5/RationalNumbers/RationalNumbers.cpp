#include "stdafx.h"
#include "Rational.h"

using namespace std;

int main()
{
	auto test = CRational(9, -4).ToCompoundFraction();
	cout << test.first << test.second;

    return 0;
}


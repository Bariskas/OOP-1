#include <iostream>
#include <string>
#include "Radix.h"

using namespace std;

int ReadNotationFromString(string const& strNotation)
{
	int  notation = 0;
	try
	{
		notation = stoi(strNotation);
	}
	catch (invalid_argument)
	{
		throw invalid_argument("Arguments <source notation> <destination notation> <value> must be a numbers!");
	}
	return notation;
}

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		cout << "Invalid arguments count\n" << "Usage: radix.exe <source notation> <destination notation> <value>" << endl;
		return 1;
	}

	try
	{
		int sourceNotation = ReadNotationFromString(argv[1]);
		int destinationNotation = ReadNotationFromString(argv[2]);
		ValidateNotation(sourceNotation);
		ValidateNotation(destinationNotation);

		string value = argv[3];
		ValidateValue(value, sourceNotation);

		cout << ConvertRadix(sourceNotation, destinationNotation, value) << endl;
	}
	catch (exception const& error)
	{
		cout << error.what() << endl;
		return 1;
	}
	return 0;
}
#include "stdafx.h"
#include "VectorProcess.h"

using namespace std;

void PrintVectorInSortedOrder(vector<double> numbers)
{
	sort(numbers.begin(), numbers.end());
	copy(numbers.cbegin(), numbers.cend(), ostream_iterator<double>(cout, " "));
	cout << endl;
}

void ReadNumbersFromStream(vector<double>& numbers, istream& istream)
{
	numbers = vector<double>(istream_iterator<double>(istream), istream_iterator<double>());
}

int main()
{
	vector<double> numbers;
	ReadNumbersFromStream(numbers, cin);
	try
	{
		ProcessVector(numbers);
	}
	catch (exception const& e)
	{
		cout << e.what() << endl;
	}
	PrintVectorInSortedOrder(numbers);
}


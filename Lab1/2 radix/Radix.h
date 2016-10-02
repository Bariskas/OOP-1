#include <string>
#include <limits>

using namespace std;

int MultiplyWithOverflowCheck(unsigned const int multiplier1, unsigned const int multiplier2);
int AddWithOverflowCheck(unsigned const int add1, unsigned const int add2);
int ExpWithOverflowCheck(unsigned const int number, unsigned const int degree);
int CharToNumber(const char ch);
char NumberToChar(const int number);
void ValidateNotation(int notation);
bool CheckStrNumberValueOverflow(string const& value);
bool CheckStrNumberValueUnderflow(string const& value);
void ValidateValue(string const& value, const int notation);
int ConvertToDecimal(string const& value, const int sourceNotation);
std::string ConvertToDestination(int decimalValue, int destinationNotation);
std::string ConvertRadix(const int sourceNotation, const int destinationNotation, string value);
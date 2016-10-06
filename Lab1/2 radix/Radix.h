#include <string>

int MultiplyWithOverflowCheck(unsigned const int multiplier1, unsigned const int multiplier2);
int AddWithOverflowCheck(unsigned const int add1, unsigned const int add2);
int CharToNumber(const char ch);
char NumberToChar(const int number);
void ValidateNotation(int notation);
void ValidateStringValue(std::string const& value);
void ValidateValue(std::string const& value, const int notation);
int ConvertToDecimal(std::string const& value, const int sourceNotation);
std::string ConvertToDestination(int decimalValue, int destinationNotation);
std::string ConvertRadix(const int sourceNotation, const int destinationNotation, std::string value);
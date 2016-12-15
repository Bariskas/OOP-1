#include "stdafx.h"
#include "Rational.h"
#include "Utils.h"

using namespace std;

CRational::CRational(int value)
	: m_numerator(value)
{
}

CRational::CRational(int numerator, int denominator)
{
	m_denominator = (denominator == 0) ? 1 : denominator;
	m_numerator = (denominator == 0) ? 0 : numerator;
	
	Normalize();
}

int CRational::GetNumerator()const
{
	return m_numerator;
}

int CRational::GetDenominator()const
{
	return m_denominator;
}

double CRational::ToDouble()const
{
	return m_numerator / (double)m_denominator;
}

std::pair<int, CRational> CRational::ToCompoundFraction()const
{
	auto division = div(m_numerator, m_denominator);

	return make_pair(division.quot, CRational(division.rem, m_denominator));
}

CRational const CRational::operator+()const
{
	return *this;
}

CRational const CRational::operator-()const
{
	return CRational(-this->m_numerator, this->m_denominator);
}

CRational const CRational::operator+(CRational const& rational)const
{
	int lcm = Lcm(m_denominator, rational.m_denominator);
	auto commonNumerators = GetCommonNumerators(*this, rational);

	return CRational(commonNumerators.first + commonNumerators.second, lcm);
}

CRational const CRational::operator+(int number)const
{
	return *this + CRational(number);
}

CRational const operator+(int number, CRational const& rational)
{
	return CRational(number) + rational;
}

CRational const CRational::operator-(CRational const& rational)const
{
	int lcm = Lcm(m_denominator, rational.m_denominator);
	auto commonNumerators = GetCommonNumerators(*this, rational);

	return CRational(commonNumerators.first - commonNumerators.second, lcm);
}

CRational const CRational::operator-(int number)const
{
	return *this - CRational(number);
}

CRational const operator-(int number, CRational const& rational)
{
	return CRational(number) - rational;
}

CRational& CRational::operator+=(CRational const& rational)
{
	*this = *this + rational;

	return *this;
}

CRational& CRational::operator+=(int number)
{
	*this += CRational(number);

	return *this;
}

CRational& CRational::operator-=(CRational const& rational)
{
	*this = *this - rational;

	return *this;
}

CRational& CRational:: operator-=(int number)
{
	*this -= CRational(number);

	return *this;
}

CRational const CRational::operator*(CRational const& rational)const
{
	return CRational(m_numerator * rational.m_numerator, m_denominator * rational.m_denominator);
}

CRational const CRational::operator*(int number)const
{
	return *this * CRational(number);
}

CRational const operator*(int number, CRational const& rational)
{
	return CRational(number) * rational;
}

CRational const CRational::operator/(CRational const& rational)const
{
	return CRational(m_numerator * rational.m_denominator, m_denominator * rational.m_numerator);
}

CRational const CRational::operator/(int number)const
{
	return *this / CRational(number);
}

CRational const operator/(int number, CRational const& rational)
{
	return CRational(number) / rational;
}

CRational& CRational::operator*=(CRational const& rational)
{
	*this = *this * rational;

	return *this;
}

CRational& CRational::operator*=(int number)
{
	*this *= CRational(number);

	return *this;
}

CRational& CRational::operator/=(CRational const& rational)
{
	*this = *this / rational;

	return *this;
}

CRational& CRational:: operator/=(int number)
{
	*this /= CRational(number);

	return *this;
}

bool CRational::operator==(CRational const& rational)const
{
	auto commonNumerators = GetCommonNumerators(*this, rational);

	return commonNumerators.first == commonNumerators.second;
}

bool CRational::operator==(int number)const
{
	return *this == CRational(number);
}

bool operator==(int number, CRational const& rational)
{
	return rational == CRational(number);
}

bool CRational::operator!=(CRational const& rational)const
{
	return !(*this == rational);
}

bool CRational::operator!=(int number)const
{
	return *this != CRational(number);
}

bool operator!=(int number, CRational const& rational)
{
	return rational != CRational(number);
}

bool CRational::operator<(CRational const& rational)const
{
	auto commonNumerators = GetCommonNumerators(*this, rational);

	return commonNumerators.first < commonNumerators.second;
}

bool CRational::operator<(int number)const
{
	return *this < CRational(number);
}

bool operator<(int number, CRational const& rational)
{
	return CRational(number) < rational;
}

bool CRational::operator>(CRational const& rational)const
{
	auto commonNumerators = GetCommonNumerators(*this, rational);

	return commonNumerators.first > commonNumerators.second;
}

bool CRational::operator>(int number)const
{
	return *this > CRational(number);
}

bool operator>(int number, CRational const& rational)
{
	return CRational(number) > rational;
}

bool CRational::operator<=(CRational const& rational)const
{
	return !(*this > rational);
}

bool CRational::operator<=(int number)const
{
	return *this <= CRational(number);
}

bool operator<=(int number, CRational const& rational)
{
	return CRational(number) <= rational;
}

bool CRational::operator>=(CRational const& rational)const
{
	return !(*this < rational);
}

bool CRational::operator>=(int number)const
{
	return *this >= CRational(number);
}

bool operator>=(int number, CRational const& rational)
{
	return CRational(number) >= rational;
}

std::ostream& operator<<(std::ostream& output, CRational const& rational)
{
	output << rational.GetNumerator() << '/' << rational.GetDenominator();

	return output;
}

std::istream& operator>> (std::istream& input, CRational& rational)
{
	string rationalNumberStr;
	input >> rationalNumberStr;
	vector<string> values;

	boost::split(values, rationalNumberStr, bind2nd(equal_to<char>(), '/'));
	if (values.size() != 2)
	{
		throw runtime_error("Must be numerator/denominator in string!");
	}

	try
	{
		int numenator = StrToInt(values[0]);
		int denominator = StrToInt(values[1]);

		CRational number(numenator, denominator);
		swap(rational, number);
	}
	catch (exception const&)
	{
		throw runtime_error("Wrong rational number!");
	}

	return input;
}

void CRational::Normalize()
{
	int gcd = Gcd(m_numerator, m_denominator);
	if (gcd != 0 && m_numerator != 0)
	{
		m_numerator /= gcd;
		m_denominator /= gcd;
	}

	if (m_denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}
}

std::pair<int, int> CRational::GetCommonNumerators(CRational const& rational1, CRational const& rational2)
{
	int lcm = Lcm(rational1.m_denominator, rational2.m_denominator);
	int numerator1 = rational1.m_numerator * (lcm / rational1.m_denominator);
	int numerator2 = rational2.m_numerator * (lcm / rational2.m_denominator);

	return make_pair(numerator1, numerator2);
}
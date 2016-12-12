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

CRational const CRational::operator-()const
{
	CRational number(-this->m_numerator, this->m_denominator);
	
	return number;
}

CRational const CRational::operator+(CRational const& rational)const
{
	int lcm = Lcm(m_denominator, rational.m_denominator);
	int numerator1 = m_numerator * (lcm / m_denominator);
	int numerator2 = rational.m_numerator * (lcm / rational.m_denominator);

	CRational result(numerator1 + numerator2, lcm);

	return result;
}

CRational const CRational::operator+(int number)const
{
	return *this + CRational(number);
}

CRational const operator+(int number, CRational rational)
{
	return rational + CRational(number);
}

void CRational::Normalize()
{
	int gcd = Gcd(m_numerator, m_denominator);
	if (gcd != 0)
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
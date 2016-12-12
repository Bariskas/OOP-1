#pragma once
class CRational final
{
public:
	CRational() = default;
	CRational(int value);
	CRational(int numerator, int denominator);

	int GetNumerator()const;
	int GetDenominator()const;
	double ToDouble()const;

	CRational const operator-()const;
	CRational const operator+(CRational const& rational)const;
	CRational const operator+(int number)const;

private :
	void Normalize();

	int m_numerator = 0;
	int m_denominator = 1;
};

CRational const operator+(int number, CRational rational);
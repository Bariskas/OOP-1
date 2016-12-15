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
	std::pair<int, CRational> ToCompoundFraction()const;

	CRational const operator+()const;
	CRational const operator-()const;

	CRational const operator+(CRational const& rational)const;
	CRational const operator+(int number)const;

	CRational const operator-(CRational const& rational)const;
	CRational const operator-(int number)const;

	CRational const operator*(CRational const& rational)const;
	CRational const operator*(int number)const;

	CRational const operator/(CRational const& rational)const;
	CRational const operator/(int number)const;

	CRational& operator+=(CRational const& rational);
	CRational& operator+=(int number);

	CRational& operator-=(CRational const& rational);
	CRational& operator-=(int number);

	CRational& operator*=(CRational const& rational);
	CRational& operator*=(int number);

	CRational& operator/=(CRational const& rational);
	CRational& operator/=(int number);

	bool operator==(CRational const& rational)const;
	bool operator==(int number)const;

	bool operator!=(CRational const& rational)const;
	bool operator!=(int number)const;

	bool operator<(CRational const& rational)const;
	bool operator<(int number)const;
	bool operator>(CRational const& rational)const;
	bool operator>(int number)const;

	bool operator<=(CRational const& rational)const;
	bool operator<=(int number)const;
	bool operator>=(CRational const& rational)const;
	bool operator>=(int number)const;

private :
	void Normalize();
	static std::pair<int, int> GetCommonNumerators(CRational const& rational1, CRational const& rational2);

	int m_numerator = 0;
	int m_denominator = 1;
};

CRational const operator+(int number, CRational const& rational);
CRational const operator-(int number, CRational const& rational);
CRational const operator*(int number, CRational const& rational);
CRational const operator/(int number, CRational const& rational);
bool operator==(int number, CRational const& rational);
bool operator!=(int number, CRational const& rational);
bool operator<(int number, CRational const& rational);
bool operator>(int number, CRational const& rational);
bool operator<=(int number, CRational const& rational);
bool operator>=(int number, CRational const& rational);

std::ostream& operator<<(std::ostream& output, CRational const& rational); //todo tests
std::istream& operator>>(std::istream& input, CRational& rational); //todo tests
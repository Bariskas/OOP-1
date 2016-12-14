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

	CRational const operator-(CRational const& rational)const; //todo: tests
	CRational const operator-(int number)const; //todo: tests

	CRational const operator*(CRational const& rational)const; //todo tests
	CRational const operator*(int number)const; //todo tests

	CRational const operator/(CRational const& rational)const; //todo tests
	CRational const operator/(int number)const; //todo tests

	CRational& operator+=(CRational const& rational); //todo tests
	CRational& operator+=(int number); //todo tests

	CRational& operator-=(CRational const& rational); //todo tests
	CRational& operator-=(int number); //todo tests

	CRational& operator*=(CRational const& rational); //todo tests
	CRational& operator*=(int number); //todo tests

	CRational& operator/=(CRational const& rational); //todo tests
	CRational& operator/=(int number); //todo tests

	bool operator==(CRational const& rational)const; //todo tests
	bool operator==(int number)const; //todo tests

	bool operator!=(CRational const& rational)const; //todo tests
	bool operator!=(int number)const; //todo tests

	bool operator<(CRational const& rational)const; //todo tests
	bool operator<(int number)const; //todo tests
	bool operator>(CRational const& rational)const; //todo tests
	bool operator>(int number)const; //todo tests

	bool operator<=(CRational const& rational)const; //todo tests
	bool operator<=(int number)const; //todo tests
	bool operator>=(CRational const& rational)const; //todo tests
	bool operator>=(int number)const; //todo tests

	std::ostream& operator<<(std::ostream& output)const; //todo tests
	std::istream& operator>>(std::istream& input); //todo tests

private :
	void Normalize();
	static std::pair<int, int> GetCommonNumerators(CRational const& rational1, CRational const& rational2);

	int m_numerator = 0;
	int m_denominator = 1;
};

CRational const operator+(int number, CRational const& rational);
CRational const operator-(int number, CRational const& rational); //todo: tests
CRational const operator*(int number, CRational const& rational); //todo tests
CRational const operator/(int number, CRational const& rational); //todo tests
bool operator==(int number, CRational const& rational); //todo tests
bool operator!=(int number, CRational const& rational); //todo tests
bool operator<(int number, CRational const& rational); //todo tests
bool operator>(int number, CRational const& rational); //todo tests
bool operator<=(int number, CRational const& rational); //todo tests
bool operator>=(int number, CRational const& rational); //todo tests
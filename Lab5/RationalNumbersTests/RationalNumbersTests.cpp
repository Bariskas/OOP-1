#include "stdafx.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>
#include "../RationalNumbers/Rational.h"

using namespace std;

void CheckRationalNumberEqual(CRational const& number, int numerator, int denominator)
{
	BOOST_CHECK_EQUAL(number.GetNumerator(), numerator);
	BOOST_CHECK_EQUAL(number.GetDenominator(), denominator);
}

void CheckRationalNumberEqual(std::pair<int, CRational> number, int integerPart, int numerator, int denominator)
{
	BOOST_CHECK_EQUAL(integerPart, number.first);
	BOOST_CHECK_EQUAL(number.second.GetNumerator(), numerator);
	BOOST_CHECK_EQUAL(number.second.GetDenominator(), denominator);
}

BOOST_AUTO_TEST_SUITE(RationalNumber)
	
	BOOST_AUTO_TEST_CASE(equals_zero_by_default)
	{
		CRational number;
		CheckRationalNumberEqual(number, 0, 1);
	}

	BOOST_AUTO_TEST_CASE(can_be_specified_by_integer)
	{
		CRational number(7);
		CheckRationalNumberEqual(number, 7, 1);
	}

	BOOST_AUTO_TEST_CASE(can_be_specified_by_numerator_and_denominator)
	{
		CRational number(37, 3);
		CheckRationalNumberEqual(number, 37, 3);

		CRational number2(0, 42);
		CheckRationalNumberEqual(number2, 0, 42);
	}

	BOOST_AUTO_TEST_CASE(returns_zero_number_when_zero_denominator_specified)
	{
		CRational number(42, 0);
		CheckRationalNumberEqual(number, 0, 1);
	}

	BOOST_AUTO_TEST_CASE(returns_normalized_when_created)
	{
		CRational number(100, 8);
		CheckRationalNumberEqual(number, 25, 2);
	}

	BOOST_AUTO_TEST_CASE(returns_correct_normalized_number)
	{
		CRational number(-100, 8);
		CheckRationalNumberEqual(number, -25, 2);

		CRational number1(100, -8);
		CheckRationalNumberEqual(number1, -25, 2);

		CRational number2(-24, -4);
		CheckRationalNumberEqual(number2, 6, 1);

		CRational number3(0, -1);
		CheckRationalNumberEqual(number3, 0, 1);

		CRational number4(-7);
		CheckRationalNumberEqual(number4, -7, 1);
	}

	BOOST_AUTO_TEST_CASE(returns_double_value)
	{
		const double expectedResult = 19. / 7.;

		CRational number(19, 7);
		BOOST_CHECK_EQUAL(number.ToDouble(), expectedResult);
	}

	BOOST_AUTO_TEST_CASE(returns_compound_fraction)
	{
		CheckRationalNumberEqual(CRational(-9, 4).ToCompoundFraction(), -2, -1, 4);
		CheckRationalNumberEqual(CRational(0, 7).ToCompoundFraction(), 0, 0, 7);
		CheckRationalNumberEqual(CRational(0, 0).ToCompoundFraction(), 0, 0, 1);
		CheckRationalNumberEqual(CRational(17, 197).ToCompoundFraction(), 0, 17, 197);
	}

	struct RationalFixture
	{
		CRational number = CRational(25, 4);
	};

	BOOST_FIXTURE_TEST_CASE(returns_negative_number, RationalFixture)
	{
		CheckRationalNumberEqual(-number, -25, 4);
		CheckRationalNumberEqual(-(-number), 25, 4);
	}

	BOOST_FIXTURE_TEST_SUITE(summarizes, RationalFixture)

		BOOST_AUTO_TEST_CASE(two_rational_numbers)
		{
			CheckRationalNumberEqual(number + CRational(-1, 6), 73, 12);
		}

		BOOST_AUTO_TEST_CASE(rational_with_int)
		{
			CheckRationalNumberEqual(number + 25, 125, 4);
		}

		BOOST_AUTO_TEST_CASE(int_with_rational)
		{
			CheckRationalNumberEqual(8 + number, 57, 4);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(adds_by_shorthand_operator, RationalFixture)

		BOOST_AUTO_TEST_CASE(rational_number)
		{
			CheckRationalNumberEqual(number += CRational(-1, 6), 73, 12);
		}

		BOOST_AUTO_TEST_CASE(int_number)
		{
			CheckRationalNumberEqual(number += 25, 125, 4);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(calculates_difference_of, RationalFixture)

		BOOST_AUTO_TEST_CASE(two_rational_numbers)
		{
			CheckRationalNumberEqual(number - CRational(13, 2), -1, 4);
		}

		BOOST_AUTO_TEST_CASE(rational_with_int)
		{
			CheckRationalNumberEqual(number - 3, 13, 4);
		}

		BOOST_AUTO_TEST_CASE(int_with_rational)
		{
			CheckRationalNumberEqual(8 - number, 7, 4);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(calculates_multiplication_of, RationalFixture)

		BOOST_AUTO_TEST_CASE(two_rational_numbers)
		{
			CheckRationalNumberEqual(number - CRational(13, 2), -1, 4);
		}

		BOOST_AUTO_TEST_CASE(rational_with_int)
		{
			CheckRationalNumberEqual(number - 3, 13, 4);
		}

		BOOST_AUTO_TEST_CASE(int_with_rational)
		{
			CheckRationalNumberEqual(8 - number, 7, 4);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

/*
������ ����� ��������� ��������������� ������� ������� ������
��� ����, ����� ������� ���������, ���������� ������ ���� �������� � ������ --log_level=test_suite (��. Post-build event � ���������� �������)
*/
class SpecLogFormatter:
	public boost::unit_test::output::compiler_log_formatter
{
	virtual void test_unit_start(std::ostream &os, boost::unit_test::test_unit const& tu) override
	{
		// ����� �������� test unit-� ������� ��� test unit-�, ������� ������ ������������� �� ������
		os << std::string(m_indent, ' ') << boost::replace_all_copy(tu.p_name.get(), "_", " ") << std::endl;
		// ����������� ������ ��� ������ ���� ����������� test unit-�� � ���� ������
		m_indent += 2;
	}

	virtual void test_unit_finish(std::ostream &/*os*/, boost::unit_test::test_unit const& /*tu*/, unsigned long /*elapsed*/) override
	{
		// �� ��������� test unit-� ��������� ������
		m_indent -= 2;
	}

	int m_indent = 0;
};

boost::unit_test::test_suite* init_unit_test_suite(int /*argc*/, char* /*argv*/[])
{
	// �������� ��� log formatter �� ����������������
	boost::unit_test::unit_test_log.set_formatter(new SpecLogFormatter);
	// ��� ��������� ������ ������ - All tests
	boost::unit_test::framework::master_test_suite().p_name.value = "All tests";
	return 0;
}


int main(int argc, char* argv[])
{
	// ��������� �����, ��������� ��������� ��������� ������ � ��������� ������� ������������� ������
	return boost::unit_test::unit_test_main(&init_unit_test_suite, argc, argv);
}
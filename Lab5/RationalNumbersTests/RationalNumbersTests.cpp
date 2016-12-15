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

		BOOST_FIXTURE_TEST_SUITE(substracts_by_shorthand_operator, RationalFixture)
		
			BOOST_AUTO_TEST_CASE(rational_number)
			{
				CheckRationalNumberEqual(number -= CRational(13, 2), -1, 4);
			}

			BOOST_AUTO_TEST_CASE(int_number)
			{
				CheckRationalNumberEqual(number -= 3, 13, 4);
			}

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(calculates_multiplication_of, RationalFixture)

		BOOST_AUTO_TEST_CASE(two_rational_numbers)
		{
			CheckRationalNumberEqual(number * CRational(4, 25), 1, 1);
		}

		BOOST_AUTO_TEST_CASE(rational_with_int)
		{
			CheckRationalNumberEqual(number * 3, 75, 4);
		}

		BOOST_AUTO_TEST_CASE(int_with_rational)
		{
			CheckRationalNumberEqual(3 * number, 75, 4);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(multiplies_by_shorthand_operator, RationalFixture)

		BOOST_AUTO_TEST_CASE(rational_number)
		{
			CheckRationalNumberEqual(number *= CRational(-2, 3), -25, 6);
		}

		BOOST_AUTO_TEST_CASE(int_number)
		{
			CheckRationalNumberEqual(number *= -3, -75, 4);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(calculates_division_of, RationalFixture)

		BOOST_AUTO_TEST_CASE(two_rational_numbers)
		{
			CheckRationalNumberEqual(number / CRational(25, 4), 1, 1);
		}

		BOOST_AUTO_TEST_CASE(rational_with_int)
		{
			CheckRationalNumberEqual(number / 5, 5, 4);
		}

		BOOST_AUTO_TEST_CASE(int_with_rational)
		{
			CheckRationalNumberEqual(3 / number, 12, 25);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(divided_by_shorthand_operator, RationalFixture)

		BOOST_AUTO_TEST_CASE(rational_number)
		{
			CheckRationalNumberEqual(number /= CRational(25, 4), 1, 1);
		}

		BOOST_AUTO_TEST_CASE(int_number)
		{
			CheckRationalNumberEqual(number /= -5, -5, 4);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(checks_equal, RationalFixture)
		
		BOOST_AUTO_TEST_CASE(two_rational_numbers)
		{
			BOOST_CHECK_EQUAL(CRational(24, 4), CRational(30, 5));
			BOOST_CHECK(!(CRational(-24, 4) == CRational(30, 5)));
		}

		BOOST_AUTO_TEST_CASE(rational_with_int)
		{
			BOOST_CHECK_EQUAL(CRational(40, 8), 5);
			BOOST_CHECK(!(CRational(40, 8) == -5));
		}

		BOOST_AUTO_TEST_CASE(int_with_rational)
		{
			BOOST_CHECK_EQUAL(3, CRational(90, 30));
			BOOST_CHECK(!(3 == CRational(90, 33)));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(checks_not_equal, RationalFixture)

		BOOST_AUTO_TEST_CASE(two_rational_numbers)
		{
			BOOST_CHECK(CRational(25, 4) != CRational(30, 5));
			BOOST_CHECK(!(CRational(24, 4) != CRational(30, 5)));
		}

		BOOST_AUTO_TEST_CASE(rational_with_int)
		{
			BOOST_CHECK(CRational(40, 8) != 6);
			BOOST_CHECK(!(CRational(40, 8) != 5));
		}

		BOOST_AUTO_TEST_CASE(int_with_rational)
		{
			BOOST_CHECK(-3 != CRational(90, 30));
			BOOST_CHECK(!(-3 != CRational(90, -30)));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(checks_is_less, RationalFixture)

		BOOST_AUTO_TEST_CASE(two_rational_numbers)
		{
			BOOST_CHECK(CRational(25, 4) < CRational(26, 4));
			BOOST_CHECK(!(CRational(25, 4) < CRational(25, 4)));
			BOOST_CHECK(!(CRational(25, 4) < CRational(23, 4)));

			BOOST_CHECK(CRational(-26, 4) < CRational(25, 4));
		}

		BOOST_AUTO_TEST_CASE(rational_with_int)
		{
			BOOST_CHECK(CRational(39, 5) < 8);
			BOOST_CHECK(!(CRational(40, 5) < 8));
			BOOST_CHECK(!(CRational(42, 5) < 8));
		}

		BOOST_AUTO_TEST_CASE(int_with_rational)
		{
			BOOST_CHECK(7 < CRational(39, 5));
			BOOST_CHECK(!(8 < CRational(40, 5)));
			BOOST_CHECK(!(9 < CRational(42, 5)));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(checks_is_greater, RationalFixture)

		BOOST_AUTO_TEST_CASE(two_rational_numbers)
		{
			BOOST_CHECK(CRational(25, 4) > CRational(24, 4));
			BOOST_CHECK(!(CRational(25, 4) > CRational(25, 4)));
			BOOST_CHECK(!(CRational(24, 4) > CRational(25, 4)));
		}

		BOOST_AUTO_TEST_CASE(rational_with_int)
		{
			BOOST_CHECK(CRational(41, 5) > 8);
			BOOST_CHECK(!(CRational(40, 5) > 8));
			BOOST_CHECK(!(CRational(39, 5) > 8));
		}

		BOOST_AUTO_TEST_CASE(int_with_rational)
		{
			BOOST_CHECK(8 > CRational(39, 5));
			BOOST_CHECK(!(8 > CRational(40, 5)));
			BOOST_CHECK(!(8 > CRational(42, 5)));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(checks_is_less_equal, RationalFixture)

		BOOST_AUTO_TEST_CASE(two_rational_numbers)
		{
			BOOST_CHECK(CRational(25, 4) <= CRational(26, 4));
			BOOST_CHECK(CRational(25, 4) <= CRational(25, 4));
			BOOST_CHECK(!(CRational(25, 4) <= CRational(23, 4)));

			BOOST_CHECK(CRational(-26, 4) < CRational(25, 4));
		}

		BOOST_AUTO_TEST_CASE(rational_with_int)
		{
			BOOST_CHECK(CRational(39, 5) <= 8);
			BOOST_CHECK(CRational(40, 5) <= 8);
			BOOST_CHECK(!(CRational(42, 5) <= 8));
		}

		BOOST_AUTO_TEST_CASE(int_with_rational)
		{
			BOOST_CHECK(7 <= CRational(39, 5));
			BOOST_CHECK(8 <= CRational(40, 5));
			BOOST_CHECK(!(9 <= CRational(42, 5)));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(checks_is_great_equal, RationalFixture)

		BOOST_AUTO_TEST_CASE(two_rational_numbers)
		{
			BOOST_CHECK(CRational(25, 4) >= CRational(24, 4));
			BOOST_CHECK(CRational(25, 4) >= CRational(25, 4));
			BOOST_CHECK(!(CRational(24, 4) >= CRational(25, 4)));
		}

		BOOST_AUTO_TEST_CASE(rational_with_int)
		{
			BOOST_CHECK(CRational(41, 5) >= 8);
			BOOST_CHECK(CRational(40, 5) >= 8);
			BOOST_CHECK(!(CRational(39, 5) >= 8));
		}

		BOOST_AUTO_TEST_CASE(int_with_rational)
		{
			BOOST_CHECK(8 >= CRational(39, 5));
			BOOST_CHECK(8 >= CRational(40, 5));
			BOOST_CHECK(!(8 >= CRational(42, 5)));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_CASE(prints_in_stream, RationalFixture)
	{
		ostringstream test;

		test << CRational(-42, 17) << ' ' << CRational(0, 123);

		BOOST_CHECK(test.str() == "-42/17 0/123");
	}

	BOOST_AUTO_TEST_CASE(gets_from_stream)
	{
		istringstream test("42/17 -4/13 0/0 te/st 12/  /34 test");

		CRational rational1;
		CRational rational2;
		CRational rational3;
		test >> rational1 >> rational2 >> rational3;

		CheckRationalNumberEqual(rational1, 42, 17);
		CheckRationalNumberEqual(rational2, -4, 13);
		CheckRationalNumberEqual(rational3, 0, 1);

		BOOST_CHECK_THROW(test >> CRational(), runtime_error);
		BOOST_CHECK_THROW(test >> CRational(), runtime_error);
		BOOST_CHECK_THROW(test >> CRational(), runtime_error);
		BOOST_CHECK_THROW(test >> CRational(), runtime_error);
	}

BOOST_AUTO_TEST_SUITE_END()

/*
Данный класс управляет форматированием журнала запуска тестов
Для того, чтобы увидеть результат, приложение должно быть запущено с ключём --log_level=test_suite (см. Post-build event в настройках проекта)
*/
class SpecLogFormatter:
	public boost::unit_test::output::compiler_log_formatter
{
	virtual void test_unit_start(std::ostream &os, boost::unit_test::test_unit const& tu) override
	{
		// перед запуском test unit-а выводим имя test unit-а, заменяя символ подчеркивания на пробел
		os << std::string(m_indent, ' ') << boost::replace_all_copy(tu.p_name.get(), "_", " ") << std::endl;
		// увеличиваем отступ для вывода имен последующих test unit-ов в виде дерева
		m_indent += 2;
	}

	virtual void test_unit_finish(std::ostream &/*os*/, boost::unit_test::test_unit const& /*tu*/, unsigned long /*elapsed*/) override
	{
		// по окончании test unit-а уменьшаем отступ
		m_indent -= 2;
	}

	int m_indent = 0;
};

boost::unit_test::test_suite* init_unit_test_suite(int /*argc*/, char* /*argv*/[])
{
	// Заменили имя log formatter на пользовательский
	boost::unit_test::unit_test_log.set_formatter(new SpecLogFormatter);
	// Имя корневого набора тестов - All tests
	boost::unit_test::framework::master_test_suite().p_name.value = "All tests";
	return 0;
}


int main(int argc, char* argv[])
{
	// Запускаем тесты, передавая параметры командной строки и кастомную функцию инициализации тестов
	return boost::unit_test::unit_test_main(&init_unit_test_suite, argc, argv);
}
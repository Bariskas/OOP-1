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

		CRational number(-7);
		CheckRationalNumberEqual(number, -7, 1);
	}

	BOOST_AUTO_TEST_CASE(returns_double_value)
	{
		const double expectedResult = 19. / 7.;

		CRational number(19, 7);
		BOOST_CHECK_EQUAL(number.ToDouble(), expectedResult);
	}

	struct RationalFixture
	{
		CRational number = CRational(25, 4);
	};

	BOOST_FIXTURE_TEST_SUITE(unary_minus, RationalFixture)

		BOOST_AUTO_TEST_CASE(returns_negative_number)
		{
			CheckRationalNumberEqual(-number, -25, 4);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(binary_plus, RationalFixture)

		BOOST_AUTO_TEST_CASE(summarizes_two_rational_numbers)
		{
			CheckRationalNumberEqual(number + CRational(1, 6), 77, 12);
			CheckRationalNumberEqual(number + CRational(-1, 6), 73, 12);
		}

		BOOST_AUTO_TEST_CASE(summarizes_rational_with_int)
		{
			CheckRationalNumberEqual(number + 25, 125, 4);
		}

		BOOST_AUTO_TEST_CASE(summarizes_int_with_rational)
		{
			CheckRationalNumberEqual(8 + number, 57, 4);
		}

	BOOST_AUTO_TEST_SUITE_END()

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
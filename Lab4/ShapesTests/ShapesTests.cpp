#include "stdafx.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>
#include "../Shapes/Point.h"
#include "../Shapes/Color.h"
#include "../Shapes/LineSegment.h"

using namespace std;

struct LineFixture
{
	CPoint start = CPoint(13., 21.);
	CPoint end = CPoint(29., 3.);
	CColor color = CColor(255, 128, 128);

	CLineSegment line = CLineSegment(start, end, color);
};

bool IsPointEqual(CPoint p1, CPoint p2)
{
	return (p1.x - p2.x <= DBL_EPSILON && p1.y - p2.y <= DBL_EPSILON);
}

bool IsColorEqual(CColor c1, CColor c2)
{
	return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b);
}

BOOST_AUTO_TEST_SUITE(Point)

	BOOST_AUTO_TEST_CASE(can_be_created)
	{
		CPoint point(11, 12);
		BOOST_CHECK(point.x == 11);
		BOOST_CHECK(point.y == 12);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Color)

	BOOST_AUTO_TEST_CASE(can_be_created_by_numbers)
	{
		CColor color(64, 128, 255);
		BOOST_CHECK(color.r == 64);
		BOOST_CHECK(color.g == 128);
		BOOST_CHECK(color.b == 255);
	}

	BOOST_AUTO_TEST_CASE(can_be_created_by_string)
	{
		CColor color("64:128:255");
		BOOST_CHECK(color.r == 64);
		BOOST_CHECK(color.g == 128);
		BOOST_CHECK(color.b == 255);
	}

	BOOST_AUTO_TEST_CASE(cant_be_created_by_incorrect_string_value)
	{
		BOOST_CHECK_THROW(CColor color(""), runtime_error);
		BOOST_CHECK_THROW(CColor color("64"), runtime_error);
		BOOST_CHECK_THROW(CColor color(":128:255"), runtime_error);
		BOOST_CHECK_THROW(CColor color("64:128255"), runtime_error);
		BOOST_CHECK_THROW(CColor color("64:b128:255"), runtime_error);
		BOOST_CHECK_THROW(CColor color("64:128:256"), runtime_error);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(LineSegment, LineFixture)

	BOOST_AUTO_TEST_CASE(has_zero_area)
	{
		BOOST_CHECK(line.GetArea() == 0);
	}

	BOOST_AUTO_TEST_CASE(can_calculate_its_perimeter)
	{
		double expectedResult = 24.083189157584592;
		BOOST_CHECK(line.GetPerimeter() - expectedResult <= DBL_EPSILON);
	}

	BOOST_AUTO_TEST_CASE(can_return_its_start_point)
	{
		BOOST_CHECK(IsPointEqual(line.GetStartPoint(), start));
	}

	BOOST_AUTO_TEST_CASE(can_return_its_end_point)
	{
		BOOST_CHECK(IsPointEqual(line.GetEndPoint(), end));
	}

	BOOST_AUTO_TEST_CASE(can_return_its_outline_color)
	{
		BOOST_CHECK(IsColorEqual(line.GetOutlineColor(), color));
	}

BOOST_AUTO_TEST_SUITE_END()

/*
Данный класс управляет форматированием журнала запуска тестов
Для того, чтобы увидеть результат, приложение должно быть запущено с ключём --log_level=test_suite (см. Post-build event в настройках проекта)
*/
class SpecLogFormatter :
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
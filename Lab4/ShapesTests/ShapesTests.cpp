#include "stdafx.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>
#include "../Shapes/Point.h"
#include "../Shapes/Color.h"
#include "../Shapes/LineSegment.h"
#include "../Shapes/Triangle.h"
#include "../Shapes/Rectangle.h"
#include "../Shapes/Circle.h"

using namespace std;

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
		CColor color;
		stringstream("64:128:255") >> color;

		BOOST_CHECK(color.r == 64);
		BOOST_CHECK(color.g == 128);
		BOOST_CHECK(color.b == 255);
	}

	BOOST_AUTO_TEST_CASE(cant_be_created_by_incorrect_string_value)
	{
		CColor color;

		BOOST_CHECK_THROW(stringstream("") >> color, runtime_error);
		BOOST_CHECK_THROW(stringstream("64") >> color, runtime_error);
		BOOST_CHECK_THROW(stringstream(":128:255") >> color, runtime_error);
		BOOST_CHECK_THROW(stringstream("64:128255") >> color, runtime_error);
		BOOST_CHECK_THROW(stringstream("64:b128:255") >> color, runtime_error);
		BOOST_CHECK_THROW(stringstream("64:128:256") >> color, runtime_error);
	}

BOOST_AUTO_TEST_SUITE_END()

struct LineFixture
{
	CPoint start = CPoint(13., 21.);
	CPoint end = CPoint(29., 3.);
	CColor color = CColor(255, 128, 128);

	CLineSegment line = CLineSegment(start, end, color);
};

BOOST_FIXTURE_TEST_SUITE(LineSegment, LineFixture)

	BOOST_AUTO_TEST_CASE(has_zero_area)
	{
		BOOST_CHECK(line.GetArea() == 0);
	}

	BOOST_AUTO_TEST_CASE(can_calculate_its_perimeter)
	{
		double expectedResult = 24.083189157584592;
		BOOST_CHECK_EQUAL(line.GetPerimeter(), expectedResult);
	}

	BOOST_AUTO_TEST_CASE(can_return_its_start_point)
	{
		BOOST_CHECK(line.GetStartPoint() == start);
	}

	BOOST_AUTO_TEST_CASE(can_return_its_end_point)
	{
		BOOST_CHECK(line.GetEndPoint() == end);
	}

	BOOST_AUTO_TEST_CASE(can_return_its_outline_color)
	{
		BOOST_CHECK(line.GetOutlineColor() == color);
	}

	BOOST_AUTO_TEST_CASE(two_points_must_be_different)
	{
		BOOST_CHECK_THROW(CLineSegment(start, start, color), logic_error);
	}

BOOST_AUTO_TEST_SUITE_END()

struct TriangleFixture
{
	CPoint p1 = CPoint(13., 17.);
	CPoint p2 = CPoint(29., 3.);
	CPoint p3 = CPoint(7., 43.);
	CColor outlineColor = CColor(64, 128, 255);
	CColor fillColor = CColor(42, 84, 168);

	CTriangle triangle = CTriangle(p1, p2, p3, outlineColor, fillColor);
};

BOOST_FIXTURE_TEST_SUITE(Triangle, TriangleFixture)
	
	BOOST_AUTO_TEST_CASE(can_calculate_its_area)
	{
		double expectedResult = 166.00000000000045;
		BOOST_CHECK_EQUAL(triangle.GetArea(), expectedResult);
	}

	BOOST_AUTO_TEST_CASE(can_calculate_its_perimeter)
	{
		double expectedResult = 46.797234297887641;
		BOOST_CHECK_EQUAL(triangle.GetPerimeter(), expectedResult);
	}

	BOOST_AUTO_TEST_CASE(can_return_its_first_point)
	{
		BOOST_CHECK(triangle.GetVertex1() == p1);
	}

	BOOST_AUTO_TEST_CASE(can_return_its_second_point)
	{
		BOOST_CHECK(triangle.GetVertex2() == p2);
	}

	BOOST_AUTO_TEST_CASE(can_return_its_third_point)
	{
		BOOST_CHECK(triangle.GetVertex3() == p3);
	}

	BOOST_AUTO_TEST_CASE(can_return_its_outline_color)
	{
		BOOST_CHECK(triangle.GetOutlineColor() == outlineColor);
	}

	BOOST_AUTO_TEST_CASE(can_return_its_fill_color)
	{
		BOOST_CHECK(triangle.GetFillColor() == fillColor);
	}

	BOOST_AUTO_TEST_CASE(three_points_must_be_different)
	{
		BOOST_CHECK_THROW(CTriangle(p1, p1, p3, outlineColor, fillColor), logic_error);
	}

BOOST_AUTO_TEST_SUITE_END()

struct RectangleFixture
{
	CPoint leftTop = CPoint(13., 17.);
	double width = 200.;
	double height = 100.;
	CColor outlineColor = CColor(64, 128, 255);
	CColor fillColor = CColor(42, 84, 168);

	CRectangle rect = CRectangle(leftTop, width, height, outlineColor, fillColor);
};

BOOST_FIXTURE_TEST_SUITE(Rectangle, RectangleFixture)

	BOOST_AUTO_TEST_CASE(can_calculate_its_area)
	{
		double expectedResult = 20000.000000000000;
		BOOST_CHECK_EQUAL(rect.GetArea(), expectedResult);
	}

	BOOST_AUTO_TEST_CASE(can_calculate_its_perimeter)
	{
		double expectedResult = 600.00000000000000;
		BOOST_CHECK_EQUAL(rect.GetPerimeter(), expectedResult);
	}

	BOOST_AUTO_TEST_CASE(can_return_its_left_top_point)
	{
		BOOST_CHECK(rect.GetLeftTop() == leftTop);
	}

	BOOST_AUTO_TEST_CASE(can_return_its_second_point)
	{
		CPoint expectedPoint(213., -83.);
		BOOST_CHECK(rect.GetRightBottom() == expectedPoint);
	}

	BOOST_AUTO_TEST_CASE(can_return_its_width)
	{
		BOOST_CHECK_EQUAL(rect.GetWidth(), width);
	}

	BOOST_AUTO_TEST_CASE(can_return_its_height)
	{
		BOOST_CHECK_EQUAL(rect.GetHeight(), height);
	}

	BOOST_AUTO_TEST_CASE(can_return_its_outline_color)
	{
		BOOST_CHECK(rect.GetOutlineColor() == outlineColor);
	}

	BOOST_AUTO_TEST_CASE(can_return_its_fill_color)
	{
		BOOST_CHECK(rect.GetFillColor() == fillColor);
	}

	BOOST_AUTO_TEST_CASE(width_and_height_must_be_more_than_0)
	{
		BOOST_CHECK_THROW(CRectangle(leftTop, 0., height, outlineColor, fillColor), logic_error);
		BOOST_CHECK_THROW(CRectangle(leftTop, width, 0., outlineColor, fillColor), logic_error);
	}

BOOST_AUTO_TEST_SUITE_END()

struct CicleFixture
{
	CPoint center = CPoint(130., 170.);
	double radius = 50.;
	CColor outlineColor = CColor(64, 128, 255);
	CColor fillColor = CColor(42, 84, 168);

	CCircle circle = CCircle(center, radius, outlineColor, fillColor);
};

BOOST_FIXTURE_TEST_SUITE(Circle, CicleFixture)

	BOOST_AUTO_TEST_CASE(can_calculate_its_area)
	{
		double expectedResult = 7853.9816339744830;
		BOOST_CHECK_EQUAL(circle.GetArea(), expectedResult);
	}

	BOOST_AUTO_TEST_CASE(can_calculate_its_perimeter)
	{
		double expectedResult = 314.15926535897933;
		BOOST_CHECK_EQUAL(circle.GetPerimeter(), expectedResult);
	}

	BOOST_AUTO_TEST_CASE(can_return_its_center_point)
	{
		BOOST_CHECK(circle.GetCenter() == center);
	}

	BOOST_AUTO_TEST_CASE(can_return_its_radius)
	{
		BOOST_CHECK_EQUAL(circle.GetRadius(), radius);
	}

	BOOST_AUTO_TEST_CASE(can_return_its_outline_color)
	{
		BOOST_CHECK(circle.GetOutlineColor() == outlineColor);
	}

	BOOST_AUTO_TEST_CASE(can_return_its_fill_color)
	{
		BOOST_CHECK(circle.GetFillColor() == fillColor);
	}

	BOOST_AUTO_TEST_CASE(radius_must_be_more_than_0)
	{
		BOOST_CHECK_THROW(CCircle(center, -5., outlineColor, fillColor), logic_error);
		BOOST_CHECK_THROW(CCircle(center, 0., outlineColor, fillColor), logic_error);
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
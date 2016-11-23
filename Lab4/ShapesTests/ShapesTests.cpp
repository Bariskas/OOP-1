#include "stdafx.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>
#include "../Shapes/Point.h"
#include "../Shapes/Color.h"
#include "../Shapes/LineSegment.h"
#include "../Shapes/Triangle.h"
#include "../Shapes/Rectangle.h"

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
		BOOST_CHECK(triangle.GetArea() - expectedResult <= DBL_EPSILON);
	}

	BOOST_AUTO_TEST_CASE(can_calculate_its_perimeter)
	{
		double expectedResult = 46.797234297887641;
		BOOST_CHECK(triangle.GetPerimeter() - expectedResult <= DBL_EPSILON);
	}

	BOOST_AUTO_TEST_CASE(can_return_its_first_point)
	{
		BOOST_CHECK(IsPointEqual(triangle.GetVertex1(), p1));
	}

	BOOST_AUTO_TEST_CASE(can_return_its_second_point)
	{
		BOOST_CHECK(IsPointEqual(triangle.GetVertex2(), p2));
	}

	BOOST_AUTO_TEST_CASE(can_return_its_third_point)
	{
		BOOST_CHECK(IsPointEqual(triangle.GetVertex3(), p3));
	}

	BOOST_AUTO_TEST_CASE(can_return_its_outline_color)
	{
		BOOST_CHECK(IsColorEqual(triangle.GetOutlineColor(), outlineColor));
	}

	BOOST_AUTO_TEST_CASE(can_return_its_fill_color)
	{
		BOOST_CHECK(IsColorEqual(triangle.GetFillColor(), fillColor));
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
		BOOST_CHECK(rect.GetArea() - expectedResult <= DBL_EPSILON);
	}

	BOOST_AUTO_TEST_CASE(can_calculate_its_perimeter)
	{
		double expectedResult = 600.00000000000000;
		double test = rect.GetPerimeter();
		BOOST_CHECK(rect.GetPerimeter() - expectedResult <= DBL_EPSILON);
	}

	BOOST_AUTO_TEST_CASE(can_return_its_left_top_point)
	{
		BOOST_CHECK(IsPointEqual(rect.GetLeftTop(), leftTop));
	}

	BOOST_AUTO_TEST_CASE(can_return_its_second_point)
	{
		CPoint expectedPoint(213., 83.);
		BOOST_CHECK(IsPointEqual(rect.GetRightBottom(), expectedPoint));
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
		BOOST_CHECK(IsColorEqual(rect.GetOutlineColor(), outlineColor));
	}

	BOOST_AUTO_TEST_CASE(can_return_its_fill_color)
	{
		BOOST_CHECK(IsColorEqual(rect.GetFillColor(), fillColor));
	}

BOOST_AUTO_TEST_SUITE_END()

/*
������ ����� ��������� ��������������� ������� ������� ������
��� ����, ����� ������� ���������, ���������� ������ ���� �������� � ������ --log_level=test_suite (��. Post-build event � ���������� �������)
*/
class SpecLogFormatter :
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
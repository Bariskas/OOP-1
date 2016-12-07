#include "stdafx.h"
#include "Triangle.h"
#include "LineSegment.h"

using namespace std;

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, CColor outlineColor, CColor fillColor)
	: m_vertex1(vertex1), m_vertex2(vertex2), m_vertex3(vertex3)
	, m_outlineColor(outlineColor), m_fillColor(fillColor)
{
	if (vertex1 == vertex2 || vertex2 == vertex3 || vertex3 == vertex1)
	{
		throw logic_error("Points must be different");
	}

	double line12Length = CLineSegment::CalculateLineLength(vertex1, vertex2);
	double line23Length = CLineSegment::CalculateLineLength(vertex2, vertex3);
	double line31Length = CLineSegment::CalculateLineLength(vertex3, vertex1);

	m_perimeter = CalculatePerimeter(line12Length, line23Length, line31Length);
	m_area = CalculateArea(line12Length, line23Length, line31Length);
}

double CTriangle::GetArea() const
{
	return m_area;
}

double CTriangle::GetPerimeter() const
{
	return m_perimeter;
}

std::string CTriangle::ToString() const
{
	stringstream stream;

	stream << fixed << setprecision(2);

	stream << "Triangle: vertex1" << m_vertex1.ToString()
		<< " vertex2" << m_vertex2.ToString()
		<< " vertex3" << m_vertex3.ToString()
		<< " area=" << m_area << " perimeter=" << m_perimeter
		<< " outlineColor(" << m_outlineColor.ToString() << ")"
		<< " fillColor(" << m_fillColor.ToString() << ")";

	return stream.str();
}

CColor CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

CColor CTriangle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

double CTriangle::CalculateArea(double a, double b, double c)
{
	double p_number = (a + b + c) / 2;
	return sqrt(p_number * (p_number - a) * (p_number - b) * (p_number - c));
}

double CTriangle::CalculatePerimeter(double a, double b, double c)
{
	return a + b + c;
}
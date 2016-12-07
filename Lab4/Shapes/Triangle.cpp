#include "stdafx.h"
#include "Triangle.h"
#include "LineSegment.h"

using namespace std;

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, CColor outlineColor, CColor fillColor)
	: m_vertex1(vertex1), m_vertex2(vertex2), m_vertex3(vertex3)
	, CSolidShape(outlineColor, fillColor)
{
	if (vertex1 == vertex2 || vertex2 == vertex3 || vertex3 == vertex1)
	{
		throw logic_error("Points must be different");
	}
}

double CTriangle::GetArea() const
{
	double line1;
	double line2;
	double line3;

	GetEdgeLength(line1, line2, line3);

	return CalculateArea(line1, line2, line3);
}

double CTriangle::GetPerimeter() const
{
	double line1;
	double line2;
	double line3;

	GetEdgeLength(line1, line2, line3);

	return CalculatePerimeter(line1, line2, line3);
}

std::string CTriangle::ToString() const
{
	stringstream stream;

	stream << fixed << setprecision(2);

	stream << "Triangle: vertex1" << m_vertex1.ToString()
		<< " vertex2" << m_vertex2.ToString()
		<< " vertex3" << m_vertex3.ToString()
		<< CSolidShape::ToString();

	return stream.str();
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

void CTriangle::GetEdgeLength(double& line1, double& line2, double& line3) const
{
	line1 = CLineSegment::CalculateLineLength(m_vertex1, m_vertex2);
	line2 = CLineSegment::CalculateLineLength(m_vertex2, m_vertex3);
	line3 = CLineSegment::CalculateLineLength(m_vertex3, m_vertex1);
}
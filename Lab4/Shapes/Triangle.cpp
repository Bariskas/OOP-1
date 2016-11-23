#include "stdafx.h"
#include "Triangle.h"

using namespace std;

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, CColor outlineColor, CColor fillColor)
	: m_line12(vertex1, vertex2, outlineColor)
	, m_line23(vertex2, vertex3, outlineColor)
	, m_line31(vertex3, vertex1, outlineColor)
	, m_outlineColor(outlineColor), m_fillColor(fillColor)
{
	double line12Length = m_line12.GetPerimeter();
	double line23Length = m_line23.GetPerimeter();
	double line31Length = m_line31.GetPerimeter();

	m_perimeter = CalculatePerimeter(line12Length, line23Length, line31Length);
	m_area = CalculateArea(line12Length, line23Length, line31Length);
}

double CTriangle::GetArea()
{
	return m_area;
}

double CTriangle::GetPerimeter()
{
	return m_perimeter;
}

std::string CTriangle::ToString()
{
	stringstream stream;

	stream << fixed << setprecision(2);

	stream << "vertex1(" << m_line12.GetStartPoint().x << ", " << m_line12.GetStartPoint().y << ") "
		<< "vertex2(" << m_line23.GetStartPoint().x << ", " << m_line23.GetStartPoint().y << ") "
		<< "vertex3(" << m_line31.GetStartPoint().x << ", " << m_line31.GetStartPoint().y << ") "
		<< "area=" << m_area << " perimeter=" << m_perimeter << " "
		<< "outlineColor(" << m_outlineColor.ToString() << ") "
		<< "fillColor(" << m_fillColor.ToString() << ")";

	return stream.str();
}

CColor CTriangle::GetOutlineColor()
{
	return m_outlineColor;
}

CColor CTriangle::GetFillColor()
{
	return m_fillColor;
}

CPoint CTriangle::GetVertex1()
{
	return m_line12.GetStartPoint();
}

CPoint CTriangle::GetVertex2()
{
	return m_line23.GetStartPoint();
}

CPoint CTriangle::GetVertex3()
{
	return m_line31.GetStartPoint();
}

double CTriangle::CalculateArea(double a, double b, double c)
{
	double perimeter = CalculatePerimeter(a, b, c);
	return sqrt(perimeter * (perimeter - a) * (perimeter - b) * (perimeter - c));
}

double CTriangle::CalculatePerimeter(double a, double b, double c)
{
	return (a + b + c) / 2;
}
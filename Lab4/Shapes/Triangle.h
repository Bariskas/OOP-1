#pragma once
#include "SolidShape.h"
#include "Point.h"
#include "Color.h"
#include "LineSegment.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, CColor outlineColor, CColor fillColor);
	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	CColor GetOutlineColor() override;
	CColor GetFillColor() override;
	CPoint GetVertex1();
	CPoint GetVertex2();
	CPoint GetVertex3();

private:
	static double CalculateArea(double a, double b, double c);
	static double CalculatePerimeter(double a, double b, double c);

	CColor m_outlineColor;
	CColor m_fillColor;
	CLineSegment m_line12;
	CLineSegment m_line23;
	CLineSegment m_line31;
	double m_area;
	double m_perimeter;
};


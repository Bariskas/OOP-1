#pragma once
#include "ISolidShape.h"
#include "Point.h"
#include "Color.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, CColor outlineColor, CColor fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CColor GetOutlineColor() const override;
	CColor GetFillColor() const override;
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

	static double CalculateArea(double a, double b, double c);
	static double CalculatePerimeter(double a, double b, double c);

private:
	CColor m_outlineColor;
	CColor m_fillColor;
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
	double m_area;
	double m_perimeter;
};


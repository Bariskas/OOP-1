#pragma once
#include "SolidShape.h"
#include "Point.h"
#include "Color.h"

class CCircle :	public ISolidShape
{
public:
	CCircle(CPoint center, double radius, CColor outlineColor, CColor fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CColor GetOutlineColor() const override;
	CColor GetFillColor() const override;
	CPoint GetCenter() const;
	double GetRadius() const;

private:
	CPoint m_center;
	double m_radius;
	CColor m_outlineColor;
	CColor m_fillColor;
};


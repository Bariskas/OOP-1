#pragma once
#include "Shape.h"
#include "SolidShape.h"
#include "Point.h"
#include "Color.h"

class CCircle :	public CSolidShape
{
public:
	CCircle(CPoint center, double radius, CColor outlineColor, CColor fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CPoint GetCenter() const;
	double GetRadius() const;

private:
	CPoint m_center;
	double m_radius;
};


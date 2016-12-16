#pragma once
#include "Shape.h"
#include "SolidShape.h"
#include "Point.h"
#include "Color.h"

class CCircle :	public CSolidShape
{
public:
	CCircle(CPoint const& center, double radius, CColor const& outlineColor, CColor const& fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	CPoint GetCenter() const;
	double GetRadius() const;

protected:
	void AppendProperties(std::stringstream& stream) const override;

private:
	CPoint m_center;
	double m_radius;
};


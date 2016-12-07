#pragma once
#include "Shape.h"
#include "Point.h"
#include "Color.h"

class CLineSegment final : public CShape
{
public:
	CLineSegment(CPoint startPoint, CPoint endPoint, CColor outlineColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

	static double CalculateLineLength(CPoint point1, CPoint point2);

private:
	CPoint m_startPoint;
	CPoint m_endPoint;
};


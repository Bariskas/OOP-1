#pragma once
#include "Shape.h"
#include "Point.h"
#include "Color.h"

class CLineSegment final : public IShape
{
public:
	CLineSegment(CPoint startPoint, CPoint endPoint, CColor outlineColor);
	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	CColor GetOutlineColor() override;
	CPoint GetStartPoint();
	CPoint GetEndPoint();

private:
	static double CalculateLineLength(CPoint point1, CPoint point2);

	CColor m_outlineColor;
	CPoint m_startPoint;
	CPoint m_endPoint;
	double m_length;
};


#pragma once
#include "Shape.h"
#include "Point.h"
#include "Color.h"

class CLineSegment final : public IShape
{
public:
	CLineSegment(CPoint startPoint, CPoint endPoint, CColor color);
	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	CColor GetOutlineColor() override;
	CPoint GetStartPoint();
	CPoint GetEndPoint();

private:
	CColor m_outlineColor;
	CPoint m_startPoint;
	CPoint m_endPoint;
	double m_length;
};


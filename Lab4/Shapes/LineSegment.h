#pragma once
#include "Shape.h"
#include "Point.h"
#include "Color.h"

class CLineSegment final : public CShape
{
public:
	CLineSegment(CPoint const& startPoint, CPoint const& endPoint, CColor const& outlineColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

	static double CalculateLineLength(CPoint const& point1, CPoint const& point2);

protected:
	void AppendProperties(std::stringstream& stream) const override;

private:
	CPoint m_startPoint;
	CPoint m_endPoint;
};


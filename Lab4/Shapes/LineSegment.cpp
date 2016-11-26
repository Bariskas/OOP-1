#include "stdafx.h"
#include "LineSegment.h"

using namespace std;

CLineSegment::CLineSegment(CPoint startPoint, CPoint endPoint, CColor outlineColor)
	: m_startPoint(startPoint), m_endPoint(endPoint), m_outlineColor(outlineColor)
{
	if (startPoint == endPoint)
	{
		throw logic_error("Points must be different");
	}
}

double CLineSegment::GetArea() const
{
	return 0.;
}

double CLineSegment::GetPerimeter() const
{
	return CalculateLineLength(m_startPoint, m_endPoint);
}

std::string CLineSegment::ToString() const
{
	stringstream stream;

	stream << fixed << setprecision(2);

	stream << "Line: start" << m_startPoint.ToString()
		<< " end" << m_endPoint.ToString()
		<< " area=" << GetArea()	<< " perimeter=" << GetPerimeter()
		<< " outlineColor("	<< m_outlineColor.ToString() << ')';

	return stream.str();
}

CColor CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

double CLineSegment::CalculateLineLength(CPoint point1, CPoint point2)
{
	return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}
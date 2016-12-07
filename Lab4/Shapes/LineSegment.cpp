#include "stdafx.h"
#include "LineSegment.h"

using namespace std;

CLineSegment::CLineSegment(CPoint startPoint, CPoint endPoint, CColor outlineColor)
	: CShape(outlineColor), m_startPoint(startPoint), m_endPoint(endPoint)
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

	stream << "Line: start" << m_startPoint.ToString()
		<< " end" << m_endPoint.ToString()
		<< CShape::ToString();

	return stream.str();
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
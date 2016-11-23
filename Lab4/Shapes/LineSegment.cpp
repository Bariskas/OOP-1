#include "stdafx.h"
#include "LineSegment.h"

using namespace std;

CLineSegment::CLineSegment(CPoint startPoint, CPoint endPoint, CColor outlineColor)
	: m_startPoint(startPoint), m_endPoint(endPoint), m_outlineColor(outlineColor)
{
	m_length = CalculateLineLength(m_startPoint, m_endPoint);
}

double CLineSegment::GetArea()
{
	return 0.;
}

double CLineSegment::GetPerimeter()
{
	return m_length;
}

std::string CLineSegment::ToString()
{
	stringstream stream;

	stream << fixed << setprecision(2);

	stream << "start(" << m_startPoint.x << ", " << m_startPoint.y << ") "
		<< "end(" << m_endPoint.x << ", " << m_endPoint.y << ") "
		<< "area=" << GetArea()	<< " perimeter=" << m_length
		<< " outlineColor("	<< m_outlineColor.ToString() << ')';

	return stream.str();
}

CColor CLineSegment::GetOutlineColor()
{
	return m_outlineColor;
}

CPoint CLineSegment::GetStartPoint()
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint()
{
	return m_endPoint;
}

double CLineSegment::CalculateLineLength(CPoint point1, CPoint point2)
{
	return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}
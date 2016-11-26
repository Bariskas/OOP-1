#include "stdafx.h"
#include "Circle.h"

using namespace std;

CCircle::CCircle(CPoint center, double radius, CColor outlineColor, CColor fillColor)
	: m_center(center), m_radius(radius)
	, m_outlineColor(outlineColor), m_fillColor(fillColor)
{
	if (m_radius <= DBL_EPSILON)
	{
		throw logic_error("Radius of circle must be more than zero");
	}
}

double CCircle::GetArea() const
{
	return M_PI * pow(m_radius, 2);
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}


std::string CCircle::ToString() const
{
	stringstream stream;

	stream << fixed << setprecision(2);

	stream << "Circle: center" << m_center.ToString()
		<< " radius=" << m_radius << " "
		<< " area=" << GetArea() << " perimeter=" << GetPerimeter()
		<< " outlineColor(" << m_outlineColor.ToString() << ")"
		<< " fillColor(" << m_fillColor.ToString() << ")";

	return stream.str();
}

CColor CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

CColor CCircle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}
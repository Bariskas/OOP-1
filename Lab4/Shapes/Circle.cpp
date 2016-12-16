#include "stdafx.h"
#include "Circle.h"

using namespace std;

CCircle::CCircle(CPoint const& center, double radius, CColor const& outlineColor, CColor const& fillColor)
	: m_center(center), m_radius(radius)
	, CSolidShape(outlineColor, fillColor)
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


void CCircle::AppendProperties(std::stringstream& stream) const
{
	stream << "Circle: center" << m_center.ToString()
		<< " radius=" << m_radius;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}
#include "stdafx.h"
#include "Rectangle.h"

using namespace std;

CRectangle::CRectangle(CPoint const& leftTop, double width, double height, CColor const& outlineColor, CColor const& fillColor)
	: m_leftTop(leftTop), m_width(width), m_height(height)
	, CSolidShape(outlineColor, fillColor)
{
	if (width <= DBL_EPSILON || height <= DBL_EPSILON)
	{
		throw logic_error("Width and height must be more than 0");
	}
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return (m_width + m_height) * 2;
}

void CRectangle::AppendProperties(std::stringstream& stream) const
{
	stream << "Rectangle: leftTop" << m_leftTop.ToString()
		<< " rightBottom" << GetRightBottom().ToString()
		<< " width=" << m_width << " heigth=" << m_height;
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	return CPoint(m_leftTop.x + m_width, m_leftTop.y - m_height);
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}
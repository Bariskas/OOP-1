#include "stdafx.h"
#include "Rectangle.h"

using namespace std;

CRectangle::CRectangle(CPoint leftTop, double width, double height, CColor outlineColor, CColor fillColor)
	: m_leftTop(leftTop), m_width(width), m_height(height)
	, m_outlineColor(outlineColor), m_fillColor(fillColor)
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

std::string CRectangle::ToString() const
{
	stringstream stream;

	stream << fixed << setprecision(2);

	stream << "Rectangle: leftTop" << m_leftTop.ToString()
		<< "rightBottom" << GetRightBottom().ToString()
		<< "width=" << m_width << " heigth=" << m_height
		<< "area=" << GetArea() << " perimeter=" << GetPerimeter() << " "
		<< "outlineColor(" << m_outlineColor.ToString() << ") "
		<< "fillColor(" << m_fillColor.ToString() << ")";
	return stream.str();
}

CColor CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

CColor CRectangle::GetFillColor() const
{
	return m_fillColor;
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
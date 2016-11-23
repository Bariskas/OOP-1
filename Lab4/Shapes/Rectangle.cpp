#include "stdafx.h"
#include "Rectangle.h"

using namespace std;

CRectangle::CRectangle(CPoint leftTop, double width, double height, CColor outlineColor, CColor fillColor)
	: m_leftTop(leftTop), m_width(width), m_height(height)
	, m_outlineColor(outlineColor), m_fillColor(fillColor)
{
}

double CRectangle::GetArea()
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter()
{
	return (m_width + m_height) * 2;
}

std::string CRectangle::ToString()
{
	stringstream stream;

	stream << fixed << setprecision(2);

	stream << "Rectangle leftTop(" << m_leftTop.x << ", " << m_leftTop.y << ") "
		<< "rightBottom(" << GetRightBottom().x << ", " << GetRightBottom().y << ") "
		<< "width=" << m_width << " heigth=" << m_height
		<< "area=" << GetArea() << " perimeter=" << GetPerimeter() << " "
		<< "outlineColor(" << m_outlineColor.ToString() << ") "
		<< "fillColor(" << m_fillColor.ToString() << ")";
	return stream.str();
}

CColor CRectangle::GetOutlineColor()
{
	return m_outlineColor;
}

CColor CRectangle::GetFillColor()
{
	return m_fillColor;
}

CPoint CRectangle::GetLeftTop()
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom()
{
	return CPoint(m_leftTop.x + m_width, m_leftTop.y - m_height);
}

double CRectangle::GetWidth()
{
	return m_width;
}

double CRectangle::GetHeight()
{
	return m_height;
}
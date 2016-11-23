#pragma once
#include "SolidShape.h"
#include "Point.h"
#include "Color.h"

class CRectangle : public ISolidShape
{
public:
	CRectangle(CPoint leftTop, double width, double height, CColor outlineColor, CColor fillColor);
	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	CColor GetOutlineColor() override;
	CColor GetFillColor() override;
	CPoint GetLeftTop();
	CPoint GetRightBottom();
	double GetWidth();
	double GetHeight();

private:
	CPoint m_leftTop;
	double m_width;
	double m_height;
	CColor m_outlineColor;
	CColor m_fillColor;
};


#pragma once
#include "SolidShape.h"
#include "Point.h"
#include "Color.h"

class CRectangle : public ISolidShape
{
public:
	CRectangle(CPoint leftTop, double width, double height, CColor outlineColor, CColor fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CColor GetOutlineColor() const override;
	CColor GetFillColor() const override;
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	CPoint m_leftTop;
	double m_width;
	double m_height;
	CColor m_outlineColor;
	CColor m_fillColor;
};


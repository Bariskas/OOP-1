#pragma once
#include "SolidShape.h"
#include "Point.h"
#include "Color.h"

class CRectangle : public CSolidShape
{
public:
	CRectangle(CPoint const& leftTop, double width, double height, CColor const& outlineColor, CColor const& fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

protected:
	void AppendProperties(std::stringstream& stream) const override;

private:
	CPoint m_leftTop;
	double m_width;
	double m_height;
};


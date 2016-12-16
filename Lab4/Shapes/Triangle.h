#pragma once
#include "SolidShape.h"
#include "Point.h"
#include "Color.h"

class CTriangle : public CSolidShape
{
public:
	CTriangle(CPoint const& vertex1, CPoint const& vertex2, CPoint const& vertex3, CColor const& outlineColor, CColor const& fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

	static double CalculateArea(double a, double b, double c);
	static double CalculatePerimeter(double a, double b, double c);

protected:
	void AppendProperties(std::stringstream& stream) const override;

private:
	void GetEdgeLength(double& line1, double& line2, double& line3) const;

	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
};


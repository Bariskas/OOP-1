#include "stdafx.h"
#include "Shape.h"

using namespace std;

CShape::CShape(CColor outlineColor)
	: m_outlineColor(outlineColor)
{
}

CColor CShape::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CShape::ToString() const
{
	stringstream stream;
	stream << fixed << setprecision(2);

	stream << " area=" << GetArea() << " perimeter=" << GetPerimeter()
		<< " outlineColor(" << m_outlineColor.ToString() << ')';

	return stream.str();
}
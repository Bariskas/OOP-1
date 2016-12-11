#include "stdafx.h"
#include "SolidShape.h"
#include "Point.h"
#include "Color.h"

using namespace std;

CSolidShape::CSolidShape(CColor outlineColor, CColor fillColor)
	: CShape(outlineColor), m_fillColor(fillColor)
{
}

CColor CSolidShape::GetFillColor() const
{
	return m_fillColor;
}

std::string CSolidShape::ToString() const
{
	stringstream stream;

	stream << CShape::ToString() << " fillColor(" << m_fillColor.ToString() << ')';

	return stream.str();
}
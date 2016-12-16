#pragma once
#include "IShape.h"
#include "ISolidShape.h"
#include "Shape.h"

class CSolidShape :	public virtual ISolidShape, public CShape
{
public:
	CSolidShape(CColor const& outlineColor, CColor const& fillColor);
	virtual ~CSolidShape() = default;
	CColor GetOutlineColor() const override;
	CColor GetFillColor() const override;
	std::string ToString() const final override;

private:
	CColor m_fillColor;
};


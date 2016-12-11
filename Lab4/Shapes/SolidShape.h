#pragma once
#include "IShape.h"
#include "ISolidShape.h"
#include "Shape.h"

class CSolidShape :	public virtual ISolidShape, public CShape
{
public:
	CSolidShape(CColor outlineColor, CColor fillColor);
	virtual ~CSolidShape() = default;
	CColor GetFillColor() const override;
	std::string ToString() const final override;

private:
	CColor m_fillColor;
};


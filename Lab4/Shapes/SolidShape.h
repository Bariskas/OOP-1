#pragma once
#include "IShape.h"
#include "ISolidShape.h"
#include "Shape.h"

class CSolidShape :	public virtual ISolidShape, CShape
{
public:
	CSolidShape(CColor outlineColor, CColor fillColor);
	virtual ~CSolidShape() = default;
	CColor GetOutlineColor() const override;
	CColor GetFillColor() const override;

protected:
	std::string ToString() const override;

private:
	CColor m_fillColor;
};


#pragma once
#include "IShape.h"
#include "Point.h"
#include "Color.h"

class CShape : public virtual IShape
{
public:
	CShape(CColor outlineColor);
	virtual ~CShape() = default;
	CColor GetOutlineColor() const override;

protected:
	std::string ToString() const override;

private:
	CColor m_outlineColor;
};


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
	std::string ToString() const override;

protected:
	void AppendProperties(std::stringstream& sstream) const = 0;

private:
	CColor m_outlineColor;
};


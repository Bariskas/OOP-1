#pragma once
#include "IShape.h"

class CColor;

class ISolidShape : public virtual IShape
{
public:
	virtual ~ISolidShape() = default;
	virtual CColor GetFillColor() const = 0;
};


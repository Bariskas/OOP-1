#pragma once
#include "Shape.h"

class CColor;

class ISolidShape : public IShape
{
public:
	virtual ~ISolidShape() = default;
	virtual CColor GetFillColor() = 0;
};


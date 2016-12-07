#pragma once
#include "IShape.h"

class IShapeFactory
{
public:
	virtual ~IShapeFactory() = default;
	virtual IShapePtr CreateShape(std::string const& info) = 0;
};


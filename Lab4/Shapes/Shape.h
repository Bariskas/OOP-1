#pragma once

class CColor;

class IShape
{
public:
	virtual ~IShape() = default;
	virtual double GetArea() = 0;
	virtual double GetPerimeter() = 0;
	virtual std::string ToString() = 0;
	virtual CColor GetOutlineColor() = 0;
};
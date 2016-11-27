#pragma once

class CColor;

class IShape
{
public:
	virtual ~IShape() = default;
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual CColor GetOutlineColor() const = 0;
};

typedef std::unique_ptr<IShape> ShapePtr;
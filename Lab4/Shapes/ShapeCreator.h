#pragma once
#include "Shape.h"
#include "Point.h"
#include "Color.h"
#include "Rectangle.h"

class IShapeCreator
{
public:
	virtual ShapePtr CreateShape(std::string const& info) = 0;
	virtual ~IShapeCreator() = default;
};

class CShapeCreator : public IShapeCreator
{
public:
	CShapeCreator();
	ShapePtr CreateShape(std::string const& info) override;

private:
	ShapePtr CreateLine(std::stringstream& info);
	ShapePtr CreateTriangle(std::stringstream& info);
	ShapePtr CreateRectangle(std::stringstream& info);
	ShapePtr CreateCircle(std::stringstream& info);

	typedef std::map<std::string, std::function<ShapePtr(std::stringstream&)>> ShapeCreatorActionMap;
	const ShapeCreatorActionMap m_shapeCreatorActionMap;
};
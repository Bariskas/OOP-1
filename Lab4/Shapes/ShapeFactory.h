#pragma once
#include "IShape.h"

class CShapeFactory
{
public:
	CShapeFactory();
	IShapePtr CreateShape(std::string const& info);

private:
	IShapePtr CreateLine(std::stringstream& info);
	IShapePtr CreateTriangle(std::stringstream& info);
	IShapePtr CreateRectangle(std::stringstream& info);
	IShapePtr CreateCircle(std::stringstream& info);

	typedef std::map<std::string, std::function<IShapePtr(std::stringstream&)>> ShapeCreatorActionMap;
	const ShapeCreatorActionMap m_shapeCreatorActionMap;
};
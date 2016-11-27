#pragma once
#include "Shape.h"
#include "Point.h"
#include "Color.h"
#include "Rectangle.h"

class IShapeCreator
{
public:
	virtual std::unique_ptr<IShape> CreateShape(std::string const& info) = 0;
	virtual ~IShapeCreator() = default;
};

class CShapeCreator : public IShapeCreator
{
public:
	CShapeCreator();
	std::unique_ptr<IShape> CreateShape(std::string const& info) override;

private:
	std::unique_ptr<IShape> CreateLine(std::stringstream& info);
	std::unique_ptr<IShape> CreateTriangle(std::stringstream& info);
	std::unique_ptr<IShape> CreateRectangle(std::stringstream& info);
	std::unique_ptr<IShape> CreateCircle(std::stringstream& info);

	typedef std::map<std::string, std::function<std::unique_ptr<IShape>(std::stringstream&)>> ShapeCreatorActionMap;
	const ShapeCreatorActionMap m_shapeCreatorActionMap;
};
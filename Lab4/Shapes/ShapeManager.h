#pragma once
#include "Shape.h"
#include "ShapeCreator.h"

class CShapeManager
{
public:
	CShapeManager(std::ostream& output);
	void AddShapesFromStream(std::istream& input);
	void PrintShapes();
	ShapePtr& GetShapeWithMaxArea();
	ShapePtr& GetShapeWithMinPerimeter();

private:
	void AddShape(std::string const& shapeInfo);

	typedef std::vector<ShapePtr> ShapeList;
	
	std::ostream& m_output;
	CShapeCreator m_shapeCreator;
	ShapeList m_shapeList;
};


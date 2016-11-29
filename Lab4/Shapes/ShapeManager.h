#pragma once
#include "Shape.h"
#include "ShapeCreator.h"

class CShapeManager
{
public:
	CShapeManager();
	CShapeManager(CShapeManager const& copy) = delete;
	void AddShapesFromStream(std::istream& input, std::ostream& output);
	void AddShape(std::string const& shapeInfo, std::ostream& output);
	void PrintShapes(std::ostream& output);
	ShapePtr& GetShapeWithMaxArea();
	ShapePtr& GetShapeWithMinPerimeter();

private:
	void PrintCursor(std::ostream& output);

	typedef std::vector<ShapePtr> ShapeList;
	
	CShapeCreator m_shapeCreator;
	ShapeList m_shapeList;
};


#pragma once
#include "ShapeFactory.h"

class CShapeManager
{
public:
	CShapeManager(IShapeFactory& factory);
	void AddShapesFromStream(std::istream& input, std::ostream& output);
	void AddShape(std::string const& shapeInfo, std::ostream& output);
	void PrintShapes(std::ostream& output);
	IShape* GetShapeWithMaxArea();
	IShape* GetShapeWithMinPerimeter();

private:
	void PrintCursor(std::ostream& output);

	typedef std::vector<IShapePtr> ShapeList;
	
	IShapeFactory& m_shapeFactory;
	ShapeList m_shapeList;
};


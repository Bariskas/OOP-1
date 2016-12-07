#pragma once
#include "ShapeFactory.h"

class CShapeManager
{
public:
	CShapeManager();
	CShapeManager(CShapeManager const& copy) = delete;
	void AddShapesFromStream(std::istream& input, std::ostream& output);
	void AddShape(std::string const& shapeInfo, std::ostream& output);
	void PrintShapes(std::ostream& output);
	IShape* GetShapeWithMaxArea();
	IShape* GetShapeWithMinPerimeter();

private:
	void PrintCursor(std::ostream& output);

	typedef std::vector<IShapePtr> ShapeList;
	
	CShapeFactory m_shapeCreator;
	ShapeList m_shapeList;
};


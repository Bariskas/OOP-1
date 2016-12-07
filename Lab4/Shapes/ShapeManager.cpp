#include "stdafx.h"
#include "ShapeManager.h"
#include "IShape.h"

using namespace std;

CShapeManager::CShapeManager()
	: m_shapeCreator(std::move(CShapeFactory()))
{
}

void CShapeManager::AddShapesFromStream(istream& input, std::ostream& output)
{
	string shapeInfo;

	PrintCursor(output);
	while (getline(input, shapeInfo))
	{
		AddShape(shapeInfo, output);
		PrintCursor(output);
	}
}

void CShapeManager::PrintShapes(ostream& output)
{
	transform(m_shapeList.begin(), m_shapeList.end(), ostream_iterator<string>(output, "\n"),
		[](IShapePtr const& shape) { return std::move(shape->ToString()); });
}

IShape* CShapeManager::GetShapeWithMaxArea()
{
	if (m_shapeList.empty())
	{
		throw logic_error("Shapes list is empty");
	}

	auto it = max_element(m_shapeList.begin(), m_shapeList.end(), [](IShapePtr const& shape1, IShapePtr const& shape2) {
		return shape1->GetArea() < shape2->GetArea();
	});

	return it->get();
}

IShape* CShapeManager::GetShapeWithMinPerimeter()
{
	if (m_shapeList.empty())
	{
		throw logic_error("Shapes list is empty");
	}

	auto it = min_element(m_shapeList.begin(), m_shapeList.end(), [](IShapePtr const& shape1, IShapePtr const& shape2) {
		return shape1->GetPerimeter() < shape2->GetPerimeter();
	});

	return it->get();
}

void CShapeManager::AddShape(std::string const& shapeInfo, std::ostream& output)
{
	try
	{
		IShapePtr shape = m_shapeCreator.CreateShape(shapeInfo);
		m_shapeList.push_back(std::move(shape));
		output << "ok";
	}
	catch (exception const& e)
	{
		output << "Error: " << e.what();
	}
	output << endl << endl;
}

void CShapeManager::PrintCursor(std::ostream& output)
{
	output << '>';
}
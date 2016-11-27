#include "stdafx.h"
#include "ShapeManager.h"

using namespace std;

CShapeManager::CShapeManager(ostream& output)
	: m_output(output)
	, m_shapeCreator(std::move(CShapeCreator()))
{
}

void CShapeManager::AddShapesFromStream(istream& input)
{
	string shapeInfo;
	
	while (getline(input, shapeInfo))
	{
		AddShape(shapeInfo);
	}
}

void CShapeManager::PrintShapes()
{
	transform(m_shapeList.begin(), m_shapeList.end(), ostream_iterator<string>(m_output, "\n"),
		[](ShapePtr const& shape) { return std::move(shape->ToString()); });
}

ShapePtr& CShapeManager::GetShapeWithMaxArea()
{
	if (m_shapeList.empty())
	{
		throw logic_error("Shapes list is empty");
	}

	auto it = max_element(m_shapeList.begin(), m_shapeList.end(), [](ShapePtr const& shape1, ShapePtr const& shape2) {
		return shape1->GetArea() < shape2->GetArea();
	});

	return *it;
}

ShapePtr& CShapeManager::GetShapeWithMinPerimeter()
{
	if (m_shapeList.empty())
	{
		throw logic_error("Shapes list is empty");
	}

	auto it = min_element(m_shapeList.begin(), m_shapeList.end(), [](ShapePtr const& shape1, ShapePtr const& shape2) {
		return shape1->GetPerimeter() > shape2->GetPerimeter();
	});

	return *it;
}

void CShapeManager::AddShape(std::string const& shapeInfo)
{
	try
	{
		ShapePtr shape = m_shapeCreator.CreateShape(shapeInfo);
		m_shapeList.push_back(std::move(shape));
		m_output << "ok";
	}
	catch (exception const& e)
	{
		m_output << "Error: " << e.what();
	}
	m_output << endl << endl;
}
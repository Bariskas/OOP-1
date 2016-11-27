#include "stdafx.h"
#include "ShapeCreator.h"
#include "StringUtils.h"
#include "Point.h"
#include "Color.h"
#include "LineSegment.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"

using namespace std;
using namespace std::placeholders;

CShapeCreator::CShapeCreator()
	: m_shapeCreatorActionMap({
		{ "Line", bind(&CShapeCreator::CreateLine, this, _1) },
		{ "Triangle", bind(&CShapeCreator::CreateTriangle, this, _1) },
		{ "Rectangle", bind(&CShapeCreator::CreateRectangle, this, _1) },
		{ "Circle", bind(&CShapeCreator::CreateCircle, this, _1) }
	})
{
}

std::unique_ptr<IShape> CShapeCreator::CreateShape(std::string const& info)
{
	stringstream infoStream(info);
	string shapeName;
	infoStream >> shapeName;

	auto it = m_shapeCreatorActionMap.find(shapeName);
	if (it == m_shapeCreatorActionMap.end())
	{
		throw runtime_error("Invalid shape type!");
	}

	return it->second(infoStream);
}

std::unique_ptr<IShape> CShapeCreator::CreateLine(std::stringstream& info)
{
	CPoint startPoint;
	CPoint endPoint;
	CColor outlineColor;

	info >> startPoint >> endPoint >> outlineColor;

	return make_unique<CLineSegment>(std::move(CLineSegment(startPoint, endPoint, outlineColor)));
}

std::unique_ptr<IShape> CShapeCreator::CreateTriangle(std::stringstream& info)
{
	CPoint vertex1;
	CPoint vertex2;
	CPoint vertex3;
	CColor outlineColor;
	CColor fillColor;

	info >> vertex1 >> vertex2 >> vertex3 >> outlineColor >> fillColor;

	return make_unique<CTriangle>(std::move(CTriangle(vertex1, vertex2, vertex3, outlineColor, fillColor)));
}

std::unique_ptr<IShape> CShapeCreator::CreateRectangle(std::stringstream& info)
{
	CPoint leftTop;
	CColor outlineColor;
	CColor fillColor;

	info >> leftTop;

	std::string widthStr;
	info >> widthStr;
	double width = StrToDouble(widthStr);

	std::string heightStr;
	info >> heightStr;
	double height = StrToDouble(heightStr);

	info >> outlineColor >> fillColor;

	return make_unique<CRectangle>(std::move(CRectangle(leftTop, width, height, outlineColor, fillColor)));
}

std::unique_ptr<IShape> CShapeCreator::CreateCircle(std::stringstream& info)
{
	CPoint center;
	CColor outlineColor;
	CColor fillColor;

	info >> center;

	std::string radiusStr;
	info >> radiusStr;
	double radius = StrToDouble(radiusStr);

	info >> outlineColor >> fillColor;

	return make_unique<CCircle>(std::move(CCircle(center, radius, outlineColor, fillColor)));
}
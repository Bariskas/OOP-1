#include "stdafx.h"
#include "ShapeFactory.h"
#include "StringUtils.h"
#include "Point.h"
#include "Color.h"
#include "LineSegment.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"

using namespace std;
using namespace std::placeholders;

CShapeFactory::CShapeFactory()
	: m_shapeCreatorActionMap({
		{ "Line", bind(&CShapeFactory::CreateLine, this, _1) },
		{ "Triangle", bind(&CShapeFactory::CreateTriangle, this, _1) },
		{ "Rectangle", bind(&CShapeFactory::CreateRectangle, this, _1) },
		{ "Circle", bind(&CShapeFactory::CreateCircle, this, _1) }
	})
{
}

IShapePtr CShapeFactory::CreateShape(std::string const& info)
{
	if (info.empty())
	{
		throw runtime_error("Empty shapeInfo entered!");
	}

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

IShapePtr CShapeFactory::CreateLine(std::stringstream& info)
{
	if (!CheckNumberOfParams(info.str(), 4))
	{
		throw runtime_error("Wrong parameters count!\nUsage: Line <startPoint> <endPoint> <outlineColor>");
	}

	CPoint startPoint;
	CPoint endPoint;
	CColor outlineColor;

	info >> startPoint >> endPoint >> outlineColor;

	return make_unique<CLineSegment>(std::move(CLineSegment(startPoint, endPoint, outlineColor)));
}

IShapePtr CShapeFactory::CreateTriangle(std::stringstream& info)
{
	if (!CheckNumberOfParams(info.str(), 6))
	{
		throw runtime_error("Wrong parameters count!\nUsage: Triangle <vertex1> <vertex2> <vertex3> <outlineColor> <fillColor>");
	}

	CPoint vertex1;
	CPoint vertex2;
	CPoint vertex3;
	CColor outlineColor;
	CColor fillColor;

	info >> vertex1 >> vertex2 >> vertex3 >> outlineColor >> fillColor;

	return make_unique<CTriangle>(std::move(CTriangle(vertex1, vertex2, vertex3, outlineColor, fillColor)));
}

IShapePtr CShapeFactory::CreateRectangle(std::stringstream& info)
{
	if (!CheckNumberOfParams(info.str(), 6))
	{
		throw runtime_error("Wrong parameters count!\nUsage: Rectangle <leftTopPoint> <width> <height> <outlineColor> <fillColor>");
	}

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

IShapePtr CShapeFactory::CreateCircle(std::stringstream& info)
{
	if (!CheckNumberOfParams(info.str(), 5))
	{
		throw runtime_error("Wrong parameters count!\nUsage: Circle <centerPoint> <radius> <outlineColor> <fillColor>");
	}

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
#include "stdafx.h"
#include "ShapeCreator.h"
#include "LineSegment.h"
#include "Point.h"
#include "Color.h"

using namespace std;
using namespace std::placeholders;

CShapeCreator::CShapeCreator()
	: m_shapeCreatorActionMap({
		{ "Line", bind(&CShapeCreator::CreateLine, this, _1) }
	})
{
}

std::unique_ptr<IShape> CShapeCreator::CreateShape(std::string const& info)
{
	stringstream infoStream(info);
	string shapeName;
	infoStream >> shapeName;

	auto it = m_shapeCreatorActionMap.find(shapeName);
	if (it != m_shapeCreatorActionMap.end())
	{
		return it->second(infoStream);
	}
}

std::unique_ptr<IShape> CShapeCreator::CreateLine(std::stringstream& info)
{
	CPoint startPoint;
	CPoint endPoint;
	CColor outlineColor;

	info >> startPoint >> endPoint >> outlineColor;

	return make_unique<CLineSegment>(std::move(CLineSegment(startPoint, endPoint, outlineColor)));
}
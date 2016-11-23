#include "stdafx.h"
#include "Point.h"

using namespace std;

CPoint::CPoint(double x, double y)
	: x(x), y(y)
{

}

std::string CPoint::ToString() const
{
	string str;

	str.append("(");
	str.append(to_string(x));
	str.append(", ");
	str.append(to_string(y));
	str.append(")");

	return str;
}

bool CPoint::operator ==(CPoint other) const
{
	return (x - other.x <= DBL_EPSILON && y - other.y <= DBL_EPSILON);
}
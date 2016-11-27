#include "stdafx.h"
#include "Point.h"
#include "StringUtils.h"

using namespace std;

CPoint::CPoint(double x, double y)
	: x(x), y(y)
{

}

std::string CPoint::ToString() const
{
	stringstream stream;

	stream << fixed << setprecision(2);

	stream << '(' << x << ", " << y << ')';

	return stream.str();
}

bool CPoint::operator ==(CPoint other) const
{
	return (abs(x - other.x) <= DBL_EPSILON && abs(y - other.y) <= DBL_EPSILON);
}

std::istream& operator >>(std::istream& stream, CPoint& point)
{
	string pointStr;
	stream >> pointStr;

	vector<string> pointArr;
	boost::split(pointArr, pointStr, bind2nd(equal_to<char>(), ':'));

	if (pointArr.size() != 2)
	{
		throw runtime_error("Must be two double values in point!");
	}

	try
	{
		CPoint newPoint;
		newPoint.x = StrToDouble(pointArr[0]);
		newPoint.y = StrToDouble(pointArr[1]);
		swap(point, newPoint);
	}
	catch (exception const&)
	{
		throw runtime_error("Point value must be floating point number");
	}

	return stream;
}
#include "stdafx.h"
#include "Color.h"
#include "StringUtils.h"

using namespace std;

CColor::CColor(uint8_t r, uint8_t g, uint8_t b)
	: r(r), g(g), b(b)
{
}

string CColor::ToString() const
{
	string str;

	str.append(to_string(r));
	str.append(":");
	str.append(to_string(g));
	str.append(":");
	str.append(to_string(b));

	return str;
}

bool CColor::operator ==(CColor const& other) const
{
	return (r == other.r && g == other.g && b == other.b);
}

std::istream& operator >> (std::istream& stream, CColor& color)
{
	string colorStr;
	stream >> colorStr;

	vector<string> colorArr;
	boost::split(colorArr, colorStr, bind2nd(equal_to<char>(), ':'));
	if (colorArr.size() != 3)
	{
		throw runtime_error("Must be three 0-255 values in color!");
	}

	try
	{
		CColor newColor;
		newColor.r = StrToUint8(colorArr[0]);
		newColor.g = StrToUint8(colorArr[1]);
		newColor.b = StrToUint8(colorArr[2]);
		swap(color, newColor);
	}
	catch (exception const&)
	{
		throw runtime_error("Color value must be digit between 0 and 255");
	}

	return stream;
}
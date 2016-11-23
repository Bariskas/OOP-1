#include "stdafx.h"
#include "Color.h"

using namespace std;

CColor::CColor(std::string colorStr)
{
	vector<string> color;
	boost::split(color, colorStr, bind2nd(equal_to<char>(), ':'));
	if (color.size() != 3)
	{
		throw runtime_error("Must be three color values!");
	}
	r = StrToUint8(color[0]);
	g = StrToUint8(color[1]);
	b = StrToUint8(color[2]);
}

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

bool CColor::operator ==(CColor other) const
{
	return (r == other.r && g == other.g && b == other.b);
}

uint8_t CColor::StrToUint8(std::string str)
{
	uint8_t result = 0;

	try
	{
		if (str.empty())
		{
			throw exception();
		}
		int number = stoi(str);
		if (number >= 0 && number <= 255)
		{
			result = static_cast<uint8_t>(number);
		}
		else
		{
			throw exception();
		}
	}
	catch (exception const&)
	{
		throw runtime_error("Color value must be digit between 0 and 255");
	}

	return result;
}
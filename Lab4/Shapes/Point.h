#pragma once

class CPoint final
{
public:
	CPoint() = default;
	CPoint(double x, double y);
	std::string ToString() const;
	bool operator ==(CPoint const& other) const;

	double x = 0;
	double y = 0;
};

std::istream& operator >> (std::istream& stream, CPoint& point);
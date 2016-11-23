#pragma once

class CPoint final
{
public:
	CPoint(double x, double y);
	std::string ToString() const;
	bool operator ==(CPoint other) const;

	double x;
	double y;
};
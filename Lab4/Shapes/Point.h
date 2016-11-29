#pragma once

class CPoint final
{
public:
	CPoint() = default;
	CPoint(double x, double y);
	std::string ToString() const;
	bool operator ==(CPoint other) const;
	friend std::istream& operator >>(std::istream& stream, CPoint& point);

	double x = 0;
	double y = 0;
};
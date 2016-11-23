#include "stdafx.h"
#include "Point.h"
#include "LineSegment.h"

using namespace std;

int main()
{
	CPoint start(13., 21.);
	CPoint end(29., 3.);
	CColor color(255, 128, 128);

	CLineSegment line(start, end, color);

	cout << setprecision(3) << line.ToString() << endl;

	return 0;
}
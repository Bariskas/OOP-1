#include "stdafx.h"
#include "ShapeManager.h"

using namespace std;

int main()
{
	CShapeManager shapeManager;

	shapeManager.AddShapesFromStream(cin, cout);

	try
	{
		ShapePtr& shapeWithMaxArea = shapeManager.GetShapeWithMaxArea();
		ShapePtr& shapeWithMinPerimeter = shapeManager.GetShapeWithMinPerimeter();
		cout << "Shape with Max area: " << shapeWithMaxArea->ToString() << endl
			<< "Shape with Min perimeter: " << shapeWithMinPerimeter->ToString() << endl;
	}
	catch (logic_error const& e)
	{
		cout << e.what() << endl;
	}
}
#include "stdafx.h"
#include "IShape.h"
#include "ShapeManager.h"

using namespace std;

int main()
{
	CShapeFactory shapeFactory;
	CShapeManager shapeManager(shapeFactory);

	shapeManager.AddShapesFromStream(cin, cout);

	try
	{
		IShape* shapeWithMaxArea = shapeManager.GetShapeWithMaxArea();
		IShape* shapeWithMinPerimeter = shapeManager.GetShapeWithMinPerimeter();
		cout << "Shape with Max area: " << shapeWithMaxArea->ToString() << endl
			<< "Shape with Min perimeter: " << shapeWithMinPerimeter->ToString() << endl;
	}
	catch (logic_error const& e)
	{
		cout << e.what() << endl;
	}
	return 0;
}
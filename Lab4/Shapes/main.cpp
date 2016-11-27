#include "stdafx.h"
#include "ShapeCreator.h"

using namespace std;

int main()
{
	CShapeCreator creator;

	auto shape1 = creator.CreateShape("Line 200:200 100:200 64:128:255");
	cout << shape1->ToString() << endl;

	auto shape2 = creator.CreateShape("Triangle 0:0 0:100 100:100 64:128:255 64:128:255");
	cout << shape2->ToString() << endl;

	auto shape3 = creator.CreateShape("Rectangle 100:100 200 300 64:128:255 64:128:255");
	cout << shape3->ToString() << endl;

	auto shape4 = creator.CreateShape("Circle 100:100 50 64:128:255 64:128:255");
	cout << shape4->ToString() << endl;
}
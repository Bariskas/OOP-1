#include "stdafx.h"
#include "ShapeCreator.h"

using namespace std;

int main()
{
	CShapeCreator creator;
	auto shape = creator.CreateShape("Line 100.:200. 101.:200. 64:128:255");

	cout << shape->ToString() << endl;
}
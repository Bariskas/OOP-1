#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include "InvertMatrix.h"

using namespace std;

void PrintMatrix(const float (&sourceMatrix)[3][3])
{
	const int FLOAT_PRECISION = 3;
	const int NUMBER_WIDTH = 10;

	cout << fixed << setprecision(FLOAT_PRECISION);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << setw(NUMBER_WIDTH) << sourceMatrix[i][j];
		}
		cout << endl;
	}
}

float ReadFloatNumberFromString(const string& str)
{
	float number = 0.0;
	try
	{
		number = stof(str);
	}
	catch (exception const&)
	{
		throw exception("Matrix value must be float number!");
	}
	return number;
}

void ReadMatrixFromStream(ifstream& matrixStream, matrix3x3& matrix)
{
	string matrixRowString, numberString;
	stringstream matrixRowStream;
	int rowIndex = 0;

	while (getline(matrixStream, matrixRowString))
	{
		if (rowIndex >= 3)
		{
			throw exception("Matrix must have 3 rows!");
		}
		matrixRowStream.str(matrixRowString);
		matrixRowStream.clear();
		int colIndex = 0;

		while (matrixRowStream.good())
		{
			if (colIndex >= 3)
			{
				throw exception("Matrix must have 3 columns!");
			}
			matrixRowStream >> numberString;
			matrix[rowIndex][colIndex] = ReadFloatNumberFromString(numberString);
			++colIndex;
		}
		if (colIndex != 3)
		{
			throw exception("Matrix must have 3 columns!");
		}
		++rowIndex;
	}

	if (rowIndex != 3)
	{
		throw exception("Matrix must have 3 rows!");
	}
}

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		cout << "Must be one argument: <matrix>" << endl;
		return 1;
	}

	ifstream inputFile(argv[1]);
	if (!inputFile.is_open())
	{
		cout << "Failed to open file " << argv[1] << '!' << endl;
	}

	try
	{
		matrix3x3 sourceMatrix;
		ReadMatrixFromStream(inputFile, sourceMatrix);

		matrix3x3 invertedMatrix;
		InvertMatrix(sourceMatrix, invertedMatrix);

		PrintMatrix(invertedMatrix);
	}
	catch (exception const& error)
	{
		cout << error.what() << endl;
		return 1;
	}
	return 0;
}
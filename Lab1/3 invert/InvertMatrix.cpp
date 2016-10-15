#include "InvertMatrix.h"

float GetDeterminant(const matrix3x3& matrix)
{
	return matrix[0][0] * matrix[1][1] * matrix[2][2]
		+ matrix[0][1] * matrix[1][2] * matrix[2][0]
		+ matrix[1][0] * matrix[2][1] * matrix[0][2]
		- matrix[0][2] * matrix[1][1] * matrix[2][0]
		- matrix[0][1] * matrix[1][0] * matrix[2][2]
		- matrix[1][2] * matrix[2][1] * matrix[0][0];
}

float GetMinor(const matrix3x3& matrix, const int colNumber, const int rowNumber)
{
	return matrix[(colNumber + 1) % 3][(rowNumber + 1) % 3]
		* matrix[(colNumber + 2) % 3][(rowNumber + 2) % 3]
		- matrix[(colNumber + 1) % 3][(rowNumber + 2) % 3]
		* matrix[(colNumber + 2) % 3][(rowNumber + 1) % 3];
}

void GetMinorMatrix(const matrix3x3& sourceMatrix, matrix3x3& minorMatrix)
{
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			minorMatrix[col][row] = GetMinor(sourceMatrix, col, row);
		}
	}
}

void TransposeMatrix(matrix3x3& sourceMatrix)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = i; j < 3; j++)
		{
			swap(sourceMatrix[i][j], sourceMatrix[j][i]);
		}
	}
}

void DivideMatrixByNumber(matrix3x3& sourceMatrix, const float number)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			sourceMatrix[i][j] /= number;
		}
	}
}

void InvertMatrix(const matrix3x3& sourceMatrix, matrix3x3& invertedMatrix)
{
	float determinant = GetDeterminant(sourceMatrix);
	if (determinant == 0)
	{
		throw exception("Determinant equals zero. The matrix is singular!");
	}
	else
	{
		GetMinorMatrix(sourceMatrix, invertedMatrix);
		TransposeMatrix(invertedMatrix);
		DivideMatrixByNumber(invertedMatrix, determinant);
	}
}
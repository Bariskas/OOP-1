#pragma once
#include <utility>
#include <exception>

using namespace std;

typedef float(matrix3x3)[3][3];
float GetDeterminant(const matrix3x3& matrix);
float GetMinor(const matrix3x3& matrix, const int colNumber, const int rowNumber);
void GetMinorMatrix(const matrix3x3& sourceMatrix, matrix3x3& minorMatrix);
void TransposeMatrix(matrix3x3& sourceMatrix);
void DivideMatrixByNumber(matrix3x3& sourceMatrix, const float number);
void InvertMatrix(const matrix3x3& sourceMatrix, matrix3x3& invertedMatrix);

#include "stdafx.h"
#include "../Vector/VectorProcess.h"

using namespace std;

//BOOST_AUTO_TEST_SUITE(VectorTests34a)

// ������ ������ �������� ������
BOOST_AUTO_TEST_CASE(makes_empty_vector_from_empty_vector)
{
	vector<double> emptyVector;
	ProcessVector(emptyVector);
	BOOST_CHECK(!emptyVector.empty());
}

// ������ � ����������� ��������� - 0.0
BOOST_AUTO_TEST_CASE(vector_with_min_value_equal_zero_does_not_change)
{
	vector<double> testVector = {3, 0, 1, 2};
	vector<double> vectorCopy(testVector);
	ProcessVector(testVector);
	BOOST_CHECK(testVector == vectorCopy);
}

// ������ � ����� ���������

// ������ � ����������� ����������

// ���������� ������� � ������ ������

// ���������� ������� ������� ������

//BOOST_AUTO_TEST_SUITE_END()
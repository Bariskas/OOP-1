#include "stdafx.h"
#include "../Vector/VectorProcess.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>


using namespace std;

BOOST_AUTO_TEST_SUITE(An_apple)
	BOOST_AUTO_TEST_CASE(is_round)
	{
		// TODO: check that apple is round
		BOOST_CHECK(true);
	}
	BOOST_AUTO_TEST_SUITE(when_bitten)
		BOOST_AUTO_TEST_CASE(produces_its_juice)
		{
			BOOST_CHECK(true);

		}
		BOOST_AUTO_TEST_CASE(becomes_lighter)
		{
			BOOST_CHECK(true);

		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()


//BOOST_AUTO_TEST_SUITE(VectorTests34a)

// ������ ������ �������� ������
BOOST_AUTO_TEST_CASE(makes_empty_vector_from_empty_vector)
{
	vector<double> emptyVector;
	ProcessVector(emptyVector);
	BOOST_CHECK(emptyVector.empty());
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



/*
������ ����� ��������� ��������������� ������� ������� ������
��� ����, ����� ������� ���������, ���������� ������ ���� �������� � ������ --log_level=test_suite (��. Post-build event � ���������� �������)
*/
class SpecLogFormatter :
	public boost::unit_test::output::compiler_log_formatter
{
	virtual void test_unit_start(std::ostream &os, boost::unit_test::test_unit const& tu) override
	{
		// ����� �������� test unit-� ������� ��� test unit-�, ������� ������ ������������� �� ������
		os << std::string(m_indent, ' ') << boost::replace_all_copy(tu.p_name.get(), "_", " ") << std::endl;
		// ����������� ������ ��� ������ ���� ����������� test unit-�� � ���� ������
		m_indent += 2;
	}

	virtual void test_unit_finish(std::ostream &/*os*/, boost::unit_test::test_unit const& /*tu*/, unsigned long /*elapsed*/) override
	{
		// �� ��������� test unit-� ��������� ������
		m_indent -= 2;
	}

	int m_indent = 0;
};

boost::unit_test::test_suite* init_unit_test_suite(int /*argc*/, char* /*argv*/[])
{
	// �������� ��� log formatter �� ����������������
	boost::unit_test::unit_test_log.set_formatter(new SpecLogFormatter);
	// ��� ��������� ������ ������ - All tests
	boost::unit_test::framework::master_test_suite().p_name.value = "All tests";
	return 0;
}


int main(int argc, char* argv[])
{
	// ��������� �����, ��������� ��������� ��������� ������ � ��������� ������� ������������� ������
	return boost::unit_test::unit_test_main(&init_unit_test_suite, argc, argv);
}

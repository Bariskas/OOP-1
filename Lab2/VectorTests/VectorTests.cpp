#include "stdafx.h"
#include "../Vector/VectorProcess.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(Processed_vector)

	BOOST_AUTO_TEST_CASE(remains_empty_from_empty_vector)
	{
		vector<double> emptyVector;
		ProcessVector(emptyVector);
		BOOST_CHECK(emptyVector.empty());
	}

	BOOST_AUTO_TEST_CASE(with_zero_min_value_does_not_change)
	{
		vector<double> resultVector = {3, 0, 1, 2};
		vector<double> testVector(resultVector);
		BOOST_CHECK_THROW(ProcessVector(testVector), runtime_error);
		BOOST_CHECK(testVector == resultVector);
	}

	BOOST_AUTO_TEST_CASE(with_one_value_does_not_change)
	{
		vector<double> resultVector = {42};
		vector<double> testVector(resultVector);
		BOOST_CHECK(testVector == resultVector);
	}

	BOOST_AUTO_TEST_CASE(returns_correct_results)
	{
		vector<double> resultVector = {50, 100, 200, 300, 500};
		vector<double> testVector = {5, 10, 20, 30, 50};
		ProcessVector(testVector);
		BOOST_CHECK(testVector == resultVector);
	}

BOOST_AUTO_TEST_SUITE_END()



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

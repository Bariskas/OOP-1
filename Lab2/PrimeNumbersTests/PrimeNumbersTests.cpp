#include "stdafx.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(PrimeNumbersTest)

	BOOST_AUTO_TEST_CASE(generates_empty_set_when_the_value_is_less_than_min_prime_number)
	{
		set<int> emptySet = GeneratePrimeNumbersSet(1);
		BOOST_CHECK(emptySet.empty());
	}

	BOOST_AUTO_TEST_CASE(generates_correct_results_from_the_value_which_equals_min_prime_number)
	{
		set<int> expectedSet = set<int>{ 2 };
		set<int> primeSet = GeneratePrimeNumbersSet(2);
		BOOST_CHECK(primeSet == expectedSet);
	}

	BOOST_AUTO_TEST_CASE(generates_correct_results_if_the_value_is_a_prime_number)
	{
		set<int> expectedSet = set<int>{ 2, 3, 5, 7, 11 };
		set<int> primeSet = GeneratePrimeNumbersSet(11);
		BOOST_CHECK(primeSet == expectedSet);
	}

	BOOST_AUTO_TEST_CASE(generates_correct_results_if_bound_the_value_is_not_a_prime_number)
	{
		set<int> expectedSet = set<int>{ 2, 3, 5, 7, 11, 13 };
		set<int> primeSet = GeneratePrimeNumbersSet(14);
		BOOST_CHECK(primeSet == expectedSet);
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
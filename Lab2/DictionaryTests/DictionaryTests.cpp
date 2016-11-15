#include "stdafx.h"
#include "../Dictionary/DictionaryProcess.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(The_Dictionary)
	
	BOOST_AUTO_TEST_SUITE(_reads)

		BOOST_AUTO_TEST_CASE(empty_file_and_returns_empty_map)
		{
			ifstream emptyFile;
			dict dic;
			BOOST_CHECK_NO_THROW(dic = CreateDictionaryFromStream(emptyFile));
			BOOST_CHECK(dic.size() == 0);
		}

		BOOST_AUTO_TEST_CASE(wrong_file_and_returns_an_error)
		{
			istringstream wrongFile1("dog:������\ncat:�����:���");
			istringstream wrongFile2("dog:������\ncat:\n");
			istringstream wrongFile3("dog:������\n:�����\n");
			istringstream wrongFile4("dog:������\ncat�����");
			istringstream wrongFile5("dog:������\n\ncat:�����");

			BOOST_CHECK_THROW(CreateDictionaryFromStream(wrongFile1), invalid_argument);
			BOOST_CHECK_THROW(CreateDictionaryFromStream(wrongFile2), invalid_argument);
			BOOST_CHECK_THROW(CreateDictionaryFromStream(wrongFile3), invalid_argument);
			BOOST_CHECK_THROW(CreateDictionaryFromStream(wrongFile4), invalid_argument);
			BOOST_CHECK_THROW(CreateDictionaryFromStream(wrongFile5), invalid_argument);
		}

		BOOST_AUTO_TEST_CASE(correct_file_and_returns_filled_dictionary)
		{
			dict dic;
			stringstream dicFile("cat:�����\ndog:������\n������:hotdog\n");
			dict dicResult{ {"cat", "�����"}, {"dog", "������"}, {"������", "hotdog"} };
			BOOST_CHECK_NO_THROW(dic = CreateDictionaryFromStream(dicFile));
			BOOST_CHECK(dic == dicResult);
		}

	BOOST_AUTO_TEST_SUITE_END()

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
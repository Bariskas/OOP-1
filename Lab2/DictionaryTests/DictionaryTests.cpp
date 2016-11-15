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
			ifstream wrongFile1("dictionaries\\wrong1.txt");
			ifstream wrongFile2("dictionaries\\wrong2.txt");
			ifstream wrongFile3("dictionaries\\wrong3.txt");

			BOOST_CHECK_THROW(CreateDictionaryFromStream(wrongFile1), invalid_argument);
			BOOST_CHECK_THROW(CreateDictionaryFromStream(wrongFile2), invalid_argument);
			BOOST_CHECK_THROW(CreateDictionaryFromStream(wrongFile3), invalid_argument);
		}

		BOOST_AUTO_TEST_CASE(correct_file_and_returns_filled_dictionary)
		{
			dict dic;
			dict dicResult{ {"cat", "кошка"}, {"dog", "собака"}, {"хотдог", "hotdog"} };
			ifstream correctFile1("dictionaries\\correct1.txt");
			BOOST_CHECK_NO_THROW(dic = CreateDictionaryFromStream(correctFile1));
			BOOST_CHECK(dic == dicResult);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

/*
Данный класс управляет форматированием журнала запуска тестов
Для того, чтобы увидеть результат, приложение должно быть запущено с ключём --log_level=test_suite (см. Post-build event в настройках проекта)
*/
class SpecLogFormatter :
	public boost::unit_test::output::compiler_log_formatter
{
	virtual void test_unit_start(std::ostream &os, boost::unit_test::test_unit const& tu) override
	{
		// перед запуском test unit-а выводим имя test unit-а, заменяя символ подчеркивания на пробел
		os << std::string(m_indent, ' ') << boost::replace_all_copy(tu.p_name.get(), "_", " ") << std::endl;
		// увеличиваем отступ для вывода имен последующих test unit-ов в виде дерева
		m_indent += 2;
	}

	virtual void test_unit_finish(std::ostream &/*os*/, boost::unit_test::test_unit const& /*tu*/, unsigned long /*elapsed*/) override
	{
		// по окончании test unit-а уменьшаем отступ
		m_indent -= 2;
	}

	int m_indent = 0;
};

boost::unit_test::test_suite* init_unit_test_suite(int /*argc*/, char* /*argv*/[])
{
	// Заменили имя log formatter на пользовательский
	boost::unit_test::unit_test_log.set_formatter(new SpecLogFormatter);
	// Имя корневого набора тестов - All tests
	boost::unit_test::framework::master_test_suite().p_name.value = "All tests";
	return 0;
}


int main(int argc, char* argv[])
{
	// Запускаем тесты, передавая параметры командной строки и кастомную функцию инициализации тестов
	return boost::unit_test::unit_test_main(&init_unit_test_suite, argc, argv);
}
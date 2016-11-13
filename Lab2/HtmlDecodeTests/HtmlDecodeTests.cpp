#include "stdafx.h"
#include "../HtmlDecode/HtmlDecode.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(HtmlDecode_returns)

	BOOST_AUTO_TEST_CASE(empty_string_from_empty_string)
	{
		string emptyStr;
		BOOST_CHECK(HtmlDecode(emptyStr).empty());
	}

	BOOST_AUTO_TEST_CASE(the_same_result_from_string_without_html_entities)
	{
		string str = "Hello, yes, this is dog!";
		BOOST_CHECK(str == HtmlDecode(str));
	}

	BOOST_AUTO_TEST_CASE(correct_result_from_string_containing_only_html_entities)
	{
		string str = "&quot;&apos;&lt;&gt;&amp;";
		string expectedResult = "\"'<>&";
		BOOST_CHECK(expectedResult == HtmlDecode(str));
	}

	BOOST_AUTO_TEST_CASE(correct_result_from_string_containing_html_entites_inside_text)
	{
		string str = "This is a &lt;test&gt; &amp;string";
		string expectedResult = "This is a <test> &string";
		BOOST_CHECK(expectedResult == HtmlDecode(str));
	}

	BOOST_AUTO_TEST_CASE(correct_result_from_string_containing_fake_html_entity)
	{
		string str = "This is a &amp;quot;fake&quot; two html-entities!";
		string expectedResult = "This is a &quot;fake\" two html-entities!";
		BOOST_CHECK(expectedResult == HtmlDecode(str));
	}

BOOST_AUTO_TEST_SUITE_END()

/*
Данный класс управляет формаитрованием журнала запуска тестов
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
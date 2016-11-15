#include "stdafx.h"
#include "../Dictionary/DictionaryProcess.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace std;

struct ModifiedDictionaryFixture
{
	dictionaryMap oldMap;
	dictionaryMap newMap{ { "cat", "кошка" },{ "dog", "собака" } };
	Dict dict = Dict(oldMap, newMap);
};

BOOST_AUTO_TEST_SUITE(Dictionary_reads)

	BOOST_AUTO_TEST_CASE(empty_file_and_returns_empty_map)
	{
		ifstream emptyFile;
		dictionaryMap dic;
		BOOST_CHECK_NO_THROW(dic = LoadDictionaryFromStream(emptyFile));
		BOOST_CHECK(dic.size() == 0);
	}

	BOOST_AUTO_TEST_CASE(wrong_file_and_returns_an_error)
	{
		istringstream wrongFile1("dog:собака\ncat:кошка:кот");
		istringstream wrongFile2("dog:собака\ncat:\n");
		istringstream wrongFile3("dog:собака\n:кошка\n");
		istringstream wrongFile4("dog:собака\ncatкошка");
		istringstream wrongFile5("dog:собака\n\ncat:кошка");

		BOOST_CHECK_THROW(LoadDictionaryFromStream(wrongFile1), invalid_argument);
		BOOST_CHECK_THROW(LoadDictionaryFromStream(wrongFile2), invalid_argument);
		BOOST_CHECK_THROW(LoadDictionaryFromStream(wrongFile3), invalid_argument);
		BOOST_CHECK_THROW(LoadDictionaryFromStream(wrongFile4), invalid_argument);
		BOOST_CHECK_THROW(LoadDictionaryFromStream(wrongFile5), invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(correct_file_and_returns_filled_dictionary)
	{
		dictionaryMap dic;
		stringstream dicFile("cat:кошка\ndog:собака\nхотдог:hotdog\n");
		dictionaryMap dicResult{ {"cat", "кошка"}, {"dog", "собака"}, {"хотдог", "hotdog"} };
		BOOST_CHECK_NO_THROW(dic = LoadDictionaryFromStream(dicFile));
		BOOST_CHECK(dic == dicResult);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(Dictionary_that_contains_new_words, ModifiedDictionaryFixture)

	BOOST_AUTO_TEST_CASE(can_check_is_dictionary_modified)
	{
		BOOST_CHECK(CheckIsDictionaryModified(dict));
		Dict notModifiedDict;
		BOOST_CHECK(!CheckIsDictionaryModified(notModifiedDict));
	}

	BOOST_AUTO_TEST_CASE(can_check_is_user_wants_to_save_modified_dictionary)
	{
		stringstream positiveResponse("y");
		stringstream negativeResponse("test");
		stringstream emptyResponse("");

		BOOST_CHECK(GetUserResponseForSavingFile(positiveResponse));
		BOOST_CHECK(!GetUserResponseForSavingFile(negativeResponse));
		BOOST_CHECK(!GetUserResponseForSavingFile(emptyResponse));
	}
	
	BOOST_AUTO_TEST_CASE(can_append_new_words_to_existed_dictionary_file)
	{
		char* testFile = "test.txt";
		dict.fileName = testFile;
		ifstream file(testFile);
		dict.oldWordMap = LoadDictionaryFromStream(file);
		SaveDictionaryToFile(dict);

		dictionaryMap expectedMap(dict.oldWordMap);
		expectedMap.insert(dict.newWordMap.begin(), dict.newWordMap.end());
	
		PrepareFileForRead(testFile, file);
		dictionaryMap loadedMap = LoadDictionaryFromStream(file);
		BOOST_CHECK(loadedMap == expectedMap);
	}

	BOOST_AUTO_TEST_CASE(can_save_words_to_non_existed_file)
	{
		char* nonExistentFile = "nonExistentFile.txt";

		remove(nonExistentFile);
		dict.fileName = nonExistentFile;
		SaveDictionaryToFile(dict);

		ifstream file(nonExistentFile);
		dictionaryMap loadedMap = LoadDictionaryFromStream(file);
		BOOST_CHECK(dict.newWordMap == loadedMap);
	}

BOOST_AUTO_TEST_SUITE_END()
//

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
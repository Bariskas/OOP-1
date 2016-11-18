#include "stdafx.h"
#include "../Dictionary/DictionaryProcess.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace std;

struct ModifiedDictionaryFixture
{
	DictionaryMap oldMap{ { "cat", "кошка" },{ "cat", "кот" },{ "dog", "собака" }, { "The Bolshoi Theatre", "Большой театр"} };
	DictionaryMap newMap{ { "cat", "кошка" }, {"cat", "кот"}, { "dog", "собака" } };
	Dict dict = Dict(oldMap, newMap);
};

BOOST_AUTO_TEST_SUITE(Dictionary)

	BOOST_AUTO_TEST_CASE(reads_empty_file_and_returns_empty_map)
	{
		ifstream emptyFile;
		DictionaryMap dic;
		BOOST_CHECK_NO_THROW(dic = LoadDictionaryFromStream(emptyFile));
		BOOST_CHECK(dic.empty());
	}

	BOOST_AUTO_TEST_CASE(reads_wrong_file_and_returns_an_error)
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

	BOOST_AUTO_TEST_CASE(reads_correct_file_and_returns_filled_dictionary)
	{
		DictionaryMap dic;
		stringstream dicFile("cat:кошка\ndog:собака\nхотдог:hotdog\n");
		DictionaryMap dicResult{ {"cat", "кошка"}, {"dog", "собака"}, {"хотдог", "hotdog"} };
		BOOST_CHECK_NO_THROW(dic = LoadDictionaryFromStream(dicFile));
		BOOST_CHECK(dic == dicResult);
	}

	BOOST_AUTO_TEST_CASE(can_get_translation_of_new_word_from_input)
	{
		string word("test");
		string translatedWord;

		stringstream userResponse("Тест");
		BOOST_CHECK(GetUserResponseForTranslationOfWord(userResponse, word, translatedWord));
		BOOST_CHECK(translatedWord == userResponse.str());

		stringstream emptyResponse("");
		BOOST_CHECK(!GetUserResponseForTranslationOfWord(emptyResponse, word, translatedWord));
		BOOST_CHECK(translatedWord == emptyResponse.str());
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(Dictionary_that_contains_new_words, ModifiedDictionaryFixture)

	BOOST_AUTO_TEST_CASE(translates_in_both_directions)
	{
		vector<string> translations;

		vector<string> expectedResult{"кошка", "кот"};
		GetTranslationsOfWord("cat", dict, translations);
		BOOST_CHECK(translations == expectedResult);

		translations.clear();
		vector<string> expectedResult1{ "Большой театр" };
		GetTranslationsOfWord("the bolshoi theatre", dict, translations);
		BOOST_CHECK(translations == expectedResult1);

		translations.clear();
		vector<string> expectedResult2{ "The Bolshoi Theatre" };
		GetTranslationsOfWord("большой Театр", dict, translations);
		BOOST_CHECK(translations == expectedResult2);
	}
	
	BOOST_AUTO_TEST_CASE(can_insert_new_pair_of_words_in_dictionary)
	{
		AddWordsPairToDictionary(make_pair("foreign", "иностранный"), dict);
		AddWordsPairToDictionary(make_pair("foreign", "чужой"), dict);
		
		vector<string> translations;
		vector<string> expectedResult{ "иностранный", "чужой" };
		GetTranslationsOfWord("foreign", dict, translations);
		BOOST_CHECK(translations == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(can_check_is_dictionary_modified)
	{
		BOOST_CHECK(IsDictionaryModified(dict));
		Dict notModifiedDict;
		BOOST_CHECK(!IsDictionaryModified(notModifiedDict));
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
	
	BOOST_AUTO_TEST_CASE(can_write_new_words_to_existed_dictionary_file)
	{
		char* testFile = "test.txt";
		dict.fileName = testFile;
		ifstream file(testFile);
		dict.oldWordMap = LoadDictionaryFromStream(file);
		SaveDictionaryToFile(dict);

		DictionaryMap expectedMap(dict.oldWordMap);
		expectedMap.insert(dict.newWordMap.begin(), dict.newWordMap.end());
	
		PrepareFileForRead(testFile, file);
		DictionaryMap loadedMap = LoadDictionaryFromStream(file);
		BOOST_CHECK(loadedMap == expectedMap);
	}

	BOOST_AUTO_TEST_CASE(can_save_words_to_non_existed_file)
	{
		char* nonExistentFile = "nonExistentFile.txt";

		remove(nonExistentFile);
		dict.fileName = nonExistentFile;
		SaveDictionaryToFile(dict);

		ifstream file(nonExistentFile);
		DictionaryMap loadedMap = LoadDictionaryFromStream(file);
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
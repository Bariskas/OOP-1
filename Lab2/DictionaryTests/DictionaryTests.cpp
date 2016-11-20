#include "stdafx.h"
#include "../Dictionary/DictionaryProcess.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace std;

struct ModifiedDictionaryFixture
{
	DictionaryMap oldMap{ { "cat", "�����" },{ "cat", "���" },{ "dog", "������" }, { "The Bolshoi Theatre", "������� �����"} };
	DictionaryMap newMap{ { "cat", "�����" }, {"cat", "���"}, { "Dog", "������" } };
	Dict dict = Dict(oldMap, newMap);
};

BOOST_AUTO_TEST_SUITE(Dictionary)

	BOOST_AUTO_TEST_CASE(reads_empty_file_and_returns_empty_map)
	{
		ifstream emptyFile;
		Dict dic;
		BOOST_CHECK_NO_THROW(dic = CreateDictionaryFromStream(emptyFile));
		BOOST_CHECK(dic.wordMap.empty());
	}

	BOOST_AUTO_TEST_CASE(reads_wrong_file_and_returns_an_error)
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

	BOOST_AUTO_TEST_CASE(reads_correct_file_and_returns_filled_dictionary)
	{
		Dict dic;
		stringstream dicFile("cat:�����\ndog:������\n������:hotdog\n");
		DictionaryMap dicResult{ {"cat", "�����"}, {"dog", "������"}, {"������", "hotdog"} };
		BOOST_CHECK_NO_THROW(dic = CreateDictionaryFromStream(dicFile));
		BOOST_CHECK(dic.wordMap == dicResult);
	}

	BOOST_AUTO_TEST_CASE(can_get_translation_of_new_word_from_input)
	{
		string word("test");
		string translatedWord;

		stringstream userResponse("����");
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

		istringstream file("cat:�����\ncat:���\ndog:������\nThe Bolshoi Theatre:������� �����\n");
		dict.wordMap.clear();
		dict = CreateDictionaryFromStream(file);

		vector<string> translations;
		vector<string> expectedResult1{ "������� �����" };
		GetTranslationsOfWord("the bolshoi theatre", dict, translations);
		BOOST_CHECK(translations == expectedResult1);

		translations.clear();
		vector<string> expectedResult2{ "The Bolshoi Theatre" };
		GetTranslationsOfWord("������� �����", dict, translations);
		BOOST_CHECK(translations == expectedResult2);
	}
	
	BOOST_AUTO_TEST_CASE(can_insert_new_pair_of_words_in_dictionary)
	{
		AddWordsPairToDictionary(make_pair("foreign", "�����������"), dict);
		AddWordsPairToDictionary(make_pair("foreign", "�����"), dict);
		
		vector<string> translations;
		vector<string> expectedResult{ "�����������", "�����" };
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
		ifstream file(testFile);
		dict = CreateDictionaryFromStream(file);
		dict.fileName = testFile;
		SaveDictionaryToFile(dict);

		DictionaryMap expectedMap(dict.wordMap);
		expectedMap.insert(dict.newWordMap.begin(), dict.newWordMap.end());
	
		PrepareFileForRead(testFile, file);
		Dict loadedDict = CreateDictionaryFromStream(file);
		BOOST_CHECK(loadedDict.wordMap == expectedMap);
	}

	BOOST_AUTO_TEST_CASE(can_save_words_to_non_existed_file)
	{
		char* nonExistentFile = "nonExistentFile.txt";
		remove(nonExistentFile);
		dict.fileName = nonExistentFile;
		SaveDictionaryToFile(dict);

		ifstream file(nonExistentFile);
		Dict loadedDict = CreateDictionaryFromStream(file);
		BOOST_CHECK(dict.newWordMap == loadedDict.wordMap);
	}

BOOST_AUTO_TEST_SUITE_END()
//

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
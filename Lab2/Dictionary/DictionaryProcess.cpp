#include "stdafx.h"
#include "DictionaryProcess.h"
#include "GetlineIterator.h"

using namespace std;

Dict::Dict(DictionaryMap& oldMap, DictionaryMap& newMap)
	: oldWordMap(move(oldMap)), newWordMap(move(newMap))
{

}

void PrintCursor()
{
	cout << '>';
}

void PrintWelcomeMessage()
{
	cout << "������� ����� ��� �������������� ��� ��������/���������� ������ ����� � �������." << endl;
	PrintCursor();
}

void PrintTranslations(vector<string> const& translations)
{
	copy(translations.begin(), translations.end(), ostream_iterator<string>(cout, " "));
	cout << endl;
}

void RequestAddingNewWordToDictionary(string const& word, Dict& dictionary)
{
	cout << "����������� ����� \"" << word << "\". ������� ������� ��� ������ ������ ��� ������." << endl;
	PrintCursor();
	string translatedWord;
	if (GetUserResponseForTranslationOfWord(cin, word, translatedWord))
	{
		AddWordsPairToDictionary(make_pair(word, translatedWord), dictionary);
		cout << "����� \"" << word << "\" ��������� � ������� ��� \"" << translatedWord << "\"." << endl;
	}
	else
	{
		cout << "����� \"" << word << "\" ���������������." << endl;
	}
}

bool PromptToSave(istream& input)
{
	cout << "� ������� ���� ������� ���������. ������� y ��� ���������� ����� �������." << endl;
	PrintCursor();
	return GetUserResponseForSavingFile(input);
}

bool GetUserResponseForTranslationOfWord(istream& input, string const& word, string& translatedWord)
{
	return (getline(input, translatedWord) && translatedWord.size() != 0);
}

bool GetUserResponseForSavingFile(istream& input)
{
	const char POSITIVE_RESPONSE = 'y';

	string response;
	return (getline(input, response) && response.size() == 1 && response[0] == POSITIVE_RESPONSE);
}

bool GetTranslationsOfWord(string const& word, Dict& dictionary, vector<string>& translations)
{
	bool isFound = false;

	auto it = dictionary.oldWordMap.begin();
	while (it != dictionary.oldWordMap.end())
	{
		bool isFoundByKey = false;
		string wordLowered = StrToLowerCase(word);
		it = find_if(it, dictionary.oldWordMap.end(), [&](pair<string, string> const& pair) {
			if (StrToLowerCase(pair.first) == wordLowered)
			{
				isFoundByKey = true;
				return true;
			}
			return (StrToLowerCase(pair.second) == wordLowered);
		});
		if (it != dictionary.oldWordMap.end())
		{
			translations.push_back((isFoundByKey) ? it->second : it->first);
			isFound = true;
			++it;
		}
	}
	return isFound;
}

bool IsDictionaryModified(Dict& dictionary)
{
	return (!dictionary.newWordMap.empty());
}

void AddWordsPairToDictionary(pair<string, string> pair, Dict& dictionary)
{
	dictionary.oldWordMap.insert(pair);
	dictionary.newWordMap.insert(pair);
}

void SaveDictionaryToFileIfNeeded(Dict& dictionary)
{
	if (IsDictionaryModified(dictionary) && PromptToSave(cin))
	{
		try
		{
			SaveDictionaryToFile(dictionary);
			cout << "��������� ���������." << endl;
		}
		catch (exception const& e)
		{
			cout << "������ ������ � �������: " << e.what() << endl;
		}
	}
}

void SaveDictionaryToFile(Dict& dictionary)
{
	ofstream outputFile;
	PrepareFileForWrite(dictionary.fileName, outputFile);
	SaveMapToStream(dictionary.newWordMap, outputFile);
}

DictionaryMap LoadDictionaryFromStream(istream& dictFile)
{
	DictionaryMap dictionary;
	for_each(CGetlineIterator(dictFile), CGetlineIterator(), [&](string const& pairStr) {
		vector<string> pair;
		boost::split(pair, pairStr, bind2nd(equal_to<char>(), ':'));
		if (pair.size() != 2)
		{
			throw invalid_argument("Error in file structure: Symbol ':' is not allowed in words! Fie format: <word>:<word> line by line.");
		}
		else if (pair[0].empty() || pair[1].empty())
		{
			throw invalid_argument("Error in file structure: Words must be non empty! File format: <word>:<word> line by line.");
		}
		dictionary.emplace(move(pair[0]), move(pair[1]));
	});
	return dictionary;
}

void SaveMapToStream(DictionaryMap& map, ostream& outputStream)
{
	for_each(map.begin(), map.end(), [&](pair<string, string> const& pair)
	{
		outputStream << pair.first << ':' << pair.second << endl;
	});
}

void ProcessEnteredWord(string const& word, Dict& dictionary)
{
	vector<string> translations;
	if (GetTranslationsOfWord(word, dictionary, translations))
	{
		PrintTranslations(translations);
	}
	else
	{
		RequestAddingNewWordToDictionary(word, dictionary);
	}
}

bool ProcessCommand(string const& cmd, Dict& dictionary)
{
	const string EXIT_CMD = "...";

	bool result = true;
	if (cmd == EXIT_CMD)
	{
		SaveDictionaryToFileIfNeeded(dictionary);
		result = false;
	}
	else
	{
		ProcessEnteredWord(cmd, dictionary);
	}
	return result;
}

void ProcessInput(istream& input, Dict& dictionary)
{
	auto it = CGetlineIterator(input);
	while (it != CGetlineIterator())
	{
		string const& cmdStr = *it;
		if (!ProcessCommand(cmdStr, dictionary))
		{
			break;
		}
		PrintCursor();
		++it;
	}
}
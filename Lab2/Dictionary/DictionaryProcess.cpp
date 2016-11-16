#include "stdafx.h"
#include "DictionaryProcess.h"
#include "GetlineIterator.h"

using namespace std;

Dict::Dict(dictionaryMap oldMap, dictionaryMap newMap)
	: oldWordMap(move(oldMap)), newWordMap(move(newMap))
{

}

Dict::Dict()
{

}

void PrintCursor()
{
	cout << '>';
}

void PrintWelcomeMessage()
{
	cout << "Введите слово или словосочетание для перевода/добавления нового слова в словарь." << endl;
	PrintCursor();
}

void PrintTranslations(vector<string> const& translations)
{
	copy(translations.begin(), translations.end(), ostream_iterator<string>(cout, " "));
	cout << endl;
}

void AskForAddToDictionary(string const& word, Dict& dictionary)
{
	cout << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа." << endl;
	PrintCursor();
	string translatedWord;
	if (GetUserResponseForTranslationOfWord(cin, word, translatedWord))
	{
		AddWordsPairToDictionary(make_pair(word, translatedWord), dictionary);
		cout << "Слово \"" << word << "\" сохранено в словаре как \"" << translatedWord << "\"." << endl;
	}
	else
	{
		cout << "Слово \"" << word << "\" проигнорировано." << endl;
	}
}

bool AskForSaveBeforeExit(istream& input)
{
	cout << "В словарь были внесены изменения. Введите y для сохранения перед выходом." << endl;
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

bool CheckIsDictionaryModified(Dict& dictionary)
{
	return (dictionary.newWordMap.size() != 0);
}

void AddWordsPairToDictionary(pair<string, string> pair, Dict& dictionary)
{
	dictionary.oldWordMap.insert(pair);
	dictionary.newWordMap.insert(pair);
}

void SaveDictionaryToFileIfNeeded(Dict& dictionary)
{
	if (CheckIsDictionaryModified(dictionary) && AskForSaveBeforeExit(cin))
	{
		try
		{
			SaveDictionaryToFile(dictionary);
			cout << "Изменения сохранены." << endl;
		}
		catch (exception const& e)
		{
			cout << "Ошибка записи в словарь: " << e.what() << endl;
		}
	}
}

void SaveDictionaryToFile(Dict& dictionary)
{
	ofstream outputFile;
	PrepareFileForWrite(dictionary.fileName, outputFile);
	SaveMapToStream(dictionary.newWordMap, outputFile);
}

dictionaryMap LoadDictionaryFromStream(istream& dictFile)
{
	dictionaryMap dictionary;
	for_each(CGetlineIterator(dictFile), CGetlineIterator(), [&](string const& pairStr) {
		vector<string> pair;
		boost::split(pair, pairStr, bind2nd(equal_to<char>(), ':'));
		if (pair.size() != 2 || pair[0].empty() || pair[1].empty())
		{
			throw invalid_argument("Invalid dictionary structure!");
		}
		dictionary.emplace(move(pair[0]), move(pair[1]));
	});
	return dictionary;
}

void SaveMapToStream(dictionaryMap& map, ostream& outputStream)
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
		AskForAddToDictionary(word, dictionary);
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
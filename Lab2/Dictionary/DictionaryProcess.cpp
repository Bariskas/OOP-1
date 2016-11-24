#include "stdafx.h"
#include "DictionaryProcess.h"
#include "GetlineIterator.h"

using namespace std;

Dict::Dict(DictionaryMap const& oldMap, DictionaryMap const& newMap)
	: wordMap(move(oldMap)), newWordMap(move(newMap))
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

void RequestAddingNewWordToDictionary(string const& word, Dict& dictionary)
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

bool PromptToSave(istream& input)
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

	ValidateWord(word);
	string wordLowered = StrToLowerCase(word);

	GetTranslationsFromMap(wordLowered, dictionary.wordMap, translations);
	GetTranslationsFromMap(wordLowered, dictionary.reversedWordMap, translations);

	return (!translations.empty());
}

void GetTranslationsFromMap(string const& word, DictionaryMap& map, vector<string>& translations)
{
	auto range = map.equal_range(word);
	copy(range | boost::adaptors::map_values, back_inserter(translations));
}

bool IsDictionaryModified(Dict& dictionary)
{
	return (!dictionary.newWordMap.empty());
}

void AddWordsPairToDictionary(pair<string, string> const& pair, Dict& dictionary)
{
	string wordLowered = StrToLowerCase(pair.first);
	dictionary.wordMap.emplace(wordLowered, pair.second);
	dictionary.newWordMap.emplace(wordLowered, pair.second);

	dictionary.reversedWordMap.emplace(StrToLowerCase(pair.second), pair.first);
}

void SaveDictionaryToFileIfNeeded(Dict& dictionary)
{
	if (IsDictionaryModified(dictionary) && PromptToSave(cin))
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

Dict CreateDictionaryFromStream(istream& dictFile)
{
	Dict dictionary;
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
		dictionary.wordMap.emplace(move(StrToLowerCase(pair[0])), pair[1]);
		dictionary.reversedWordMap.emplace(move(StrToLowerCase(pair[1])), move(pair[0]));
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

	try
	{
		if (GetTranslationsOfWord(word, dictionary, translations))
		{
			PrintTranslations(translations);
		}
		else
		{
			RequestAddingNewWordToDictionary(word, dictionary);
		}
	}
	catch (exception const& e)
	{
		cout << e.what() << endl;
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

void ValidateWord(std::string const& word)
{
	char WORD_SEPARATOR = ':';
	const string EMPTY_WORD_MSG = "Слово не может быть пустым.";
	const string SEPARATOR_IN_WORD_MSG = "Использование символа ':' запрещено в словах.";

	if (word.empty())
	{
		throw logic_error(EMPTY_WORD_MSG);
	}
	else if (word.find(WORD_SEPARATOR) != string::npos)
	{
		throw logic_error(SEPARATOR_IN_WORD_MSG);
	}
}
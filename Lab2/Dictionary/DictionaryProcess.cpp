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

bool AskForSaveBeforeExit(istream& input)
{
	cout << "В словарь были внесены изменения. Введите y для сохранения перед выходом." << endl;
	PrintCursor();
	return CheckForUserWantsToSave(input);
}

bool CheckForUserWantsToSave(istream& input)
{
	const char POSITIVE_RESPONSE = 'y';

	string response;
	return (getline(input, response) && response.size() == 1 && response[0] == POSITIVE_RESPONSE);
}

bool CheckIsDictionaryModified(Dict& dictionary)
{
	return (dictionary.newWordMap.size() != 0);
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
		boost::split(pair, pairStr, boost::is_any_of(":"));
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
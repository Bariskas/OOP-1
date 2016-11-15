#include "stdafx.h"
#include "DictionaryProcess.h"

using namespace std;

void PrintWelcomeMessage()
{
	cout << "Введите слово или словосочетание для перевода/добавления нового слова в словарь." << endl;
}

dict CreateDictionaryFromStream(ifstream& dictFile)
{
	dict dictionary;
	string pairStr;
	while (getline(dictFile, pairStr)) //TODO: заменить на итератор
	{
		vector<string> pair;
		boost::split(pair, pairStr, boost::is_any_of(":"));
		if (pair.size() != 2 || pair[0].empty() || pair[1].empty())
		{
			throw invalid_argument("Invalid dictionary structure!");
		}
		dictionary.insert(make_pair(pair[0], pair[1]));
	}
	return dictionary;
}
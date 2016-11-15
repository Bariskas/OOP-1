#include "stdafx.h"
#include "DictionaryProcess.h"

using namespace std;

void PrintWelcomeMessage()
{
	cout << "Введите слово или словосочетание для перевода/добавления нового слова в словарь." << endl;
}

dict CreateDictionaryFromStream(istream& dictFile)
{
	dict dictionary;
	for_each(CGetlineIterator(dictFile), CGetlineIterator(), [&](string const& pairStr) {
		vector<string> pair;
		boost::split(pair, pairStr, boost::is_any_of(":"));
		if (pair.size() != 2 || pair[0].empty() || pair[1].empty())
		{
			throw invalid_argument("Invalid dictionary structure!");
		}
		dictionary.insert(make_pair(pair[0], pair[1]));
	});
	return dictionary;
}

void ProcessInput(istream& input, dict& dict)
{

}
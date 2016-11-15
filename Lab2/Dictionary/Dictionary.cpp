#include "stdafx.h"
#include "DictionaryProcess.h"

using namespace std;

void PrepareFileForRead(string const& fileName, ifstream& inputFile)
{
	inputFile = ifstream(fileName);
	if (!inputFile.is_open())
	{
		throw invalid_argument("Failed to open file for reading!");
	}
}

void CheckForArguments(int argc)
{
	if (argc != 2)
	{
		throw invalid_argument("Invalid arguments count!\nUsage: Dictionary.exe <dictionary file>");
	}
}

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "");

	try
	{
		CheckForArguments(argc);
		string dictFileName = argv[1];
		ifstream dictFile;
		PrepareFileForRead(dictFileName, dictFile);
		dict dictionary = CreateDictionaryFromStream(dictFile);

	}
	catch (exception const& e)
	{
		cout << e.what();
		return 1;
	}
	PrintWelcomeMessage();
    return 0;
}


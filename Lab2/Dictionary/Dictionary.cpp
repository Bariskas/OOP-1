#include "stdafx.h"
#include "DictionaryProcess.h"

using namespace std;

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

	Dict dictionary;
	try
	{
		CheckForArguments(argc);
		dictionary.fileName = argv[1];
		ifstream inputFile;
		PrepareFileForRead(dictionary.fileName, inputFile);
		dictionary.oldWordMap = LoadDictionaryFromStream(inputFile);
	}
	catch (exception const& e)
	{
		cout << e.what();
		return 1;
	}
	PrintWelcomeMessage();
	ProcessInput(cin, dictionary);
    return 0;
}


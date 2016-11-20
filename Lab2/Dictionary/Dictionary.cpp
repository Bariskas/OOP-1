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
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try
	{
		CheckForArguments(argc);
		string filename = argv[1];
		ifstream inputFile;
		PrepareFileForRead(filename, inputFile);
		Dict dictionary = CreateDictionaryFromStream(inputFile);
		dictionary.fileName = filename;

		PrintWelcomeMessage();
		ProcessInput(cin, dictionary);
	}
	catch (exception const& e)
	{
		cout << e.what() << endl;
		return 1;
	}
    return 0;
}


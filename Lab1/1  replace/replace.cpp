#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

string StrReplace(const string& sourceStr, const string& searchStr, const string& replaceStr)
{
	const size_t searchStrLength = searchStr.length();
	size_t searchPosition = 0;
	string outputStr;

	size_t foundPosition = sourceStr.find(searchStr, searchPosition);
	while (foundPosition != string::npos)
	{
		outputStr.append(sourceStr, searchPosition, foundPosition - searchPosition);
		outputStr.append(replaceStr);

		searchPosition = foundPosition + searchStrLength;
		foundPosition = sourceStr.find(searchStr, searchPosition);
	}

	outputStr.append(sourceStr, searchPosition);

	return outputStr;
}

bool ReplaceStringsInFile(const string& inputFileName, const string& outputFileName, const string& searchString, const string& replaceString)
{
	ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
	{
		cout << "Failed to open " << inputFileName << " for reading\n";
		return false;
	}

	ofstream outputFile(outputFileName);
	if (!outputFile.is_open())
	{
		cout << "Failed to open " << outputFileName << " for writing\n";
		return false;
	}

	string lineStr;
	while (getline(inputFile, lineStr))
	{
		string processedStr = StrReplace(lineStr, searchString, replaceString);
		if (!(outputFile << processedStr << endl))
		{
			cout << "Failed to save data on disk\n";
			return false;
		}
		outputFile.flush();
	}
	return true;
}

int main(int argc, char *argv[])
{
	if (argc != 5)
	{
		cout << "Invalid arguments count\n" << "Usage: StringReplace.exe <input file> <output file> <search string> <replace string>";
		return 1;
	}

	if (std::any_of(&argv[1], &argv[4], [](char* arg) {
		return strlen(arg) == 0;
	}))
	{
		cout << "Arguments <input file>, <output file>, <search string> must be non empty!";
		return 1;
	}

	string inputFileName = argv[1];
	string outputFileName = argv[2];
	string searchString = argv[3];
	string replaceString = argv[4];

	if (!ReplaceStringsInFile(inputFileName, outputFileName, searchString, replaceString))
	{
		return 1;
	}
}
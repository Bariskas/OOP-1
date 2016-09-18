#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string strReplace(const string& sourceStr, const string& searchStr, const string& replaceStr)
{
	const size_t searchStrLength = searchStr.length();
	size_t searchPosition = 0;
	string outputStr;

	size_t foundPosition = sourceStr.find(searchStr, searchPosition);
	while (foundPosition != string::npos)
	{
		string strBeforeFound = sourceStr.substr(searchPosition, foundPosition - searchPosition);
		outputStr += strBeforeFound + replaceStr;

		searchPosition = foundPosition + searchStrLength;
		foundPosition = sourceStr.find(searchStr, searchPosition);
	}

	outputStr += sourceStr.substr(searchPosition);

	return outputStr;
}

bool writeLineToFile(ofstream& output, const string& str)
{
	string lineStr = str + '\n';
	for (const char& ch : lineStr)
	{
		if (!output.put(ch))
		{
			return false;
		}
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

	for (int i = 1; i < 4; i++)
	{
		string argStrValue = argv[i];
		if (argStrValue.empty())
		{
			cout << "Argument " << i << " must be non empty\n";
			return 1;
		}
	}

	ifstream inputFile(argv[1]);
	if (!inputFile.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}

	ofstream outputFile(argv[2]);
	if (!outputFile.is_open())
	{
		cout << "Failed to open " << argv[2] << " for writing\n";
		return 1;
	}

	string lineStr;
	while (getline(inputFile, lineStr))
	{
		string processedStr = strReplace(lineStr, argv[3], argv[4]);
		if (!writeLineToFile(outputFile, processedStr))
		{
			cout << "Failed to save data on disk\n";
			return 1;
		}
	}
}
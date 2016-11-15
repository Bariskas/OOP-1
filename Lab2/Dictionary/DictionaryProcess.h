#pragma once

typedef std::map<std::string, std::string> dictionaryMap;

struct Dict
{
	Dict(dictionaryMap oldMap, dictionaryMap newMap);
	Dict();
	dictionaryMap oldWordMap;
	dictionaryMap newWordMap;
	std::string fileName;
};

void PrintCursor();
void PrintWelcomeMessage();
bool AskForSaveBeforeExit(std::istream& input);
bool CheckForUserWantsToSave(std::istream& input);
bool CheckIsDictionaryModified(Dict& dictionary);
void SaveDictionaryToFileIfNeeded(Dict& dictionary);
void SaveDictionaryToFile(Dict& dictionary);
dictionaryMap LoadDictionaryFromStream(std::istream& dictFile);
void SaveMapToStream(dictionaryMap& map, std::ostream& outputFile);
bool ProcessCommand(std::string const& cmd, Dict& dictionary);
void ProcessInput(std::istream& input, Dict& dictionary);
#pragma once

typedef std::unordered_multimap<std::string, std::string> dictionaryMap;

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
void PrintTranslations(std::vector<std::string> const& translations);
void AskForAddToDictionary(std::string const& word, Dict& dictionary);
bool AskForSaveBeforeExit(std::istream& input);
bool GetUserResponseForTranslationOfWord(std::istream& input, std::string const& word, std::string& translatedWord);
bool GetUserResponseForSavingFile(std::istream& input);
bool GetTranslationsOfWord(std::string const& word, Dict& dictionary, std::vector<std::string>& translations);
bool CheckIsDictionaryModified(Dict& dictionary);
void AddWordsPairToDictionary(std::pair<std::string, std::string> pair, Dict& dictionary);
void SaveDictionaryToFileIfNeeded(Dict& dictionary);
void SaveDictionaryToFile(Dict& dictionary);
dictionaryMap LoadDictionaryFromStream(std::istream& dictFile);
void SaveMapToStream(dictionaryMap& map, std::ostream& outputFile);
void ProcessEnteredWord(std::string const& word, Dict& dictionary);
bool ProcessCommand(std::string const& cmd, Dict& dictionary);
void ProcessInput(std::istream& input, Dict& dictionary);
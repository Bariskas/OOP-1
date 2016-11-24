#pragma once

typedef std::unordered_multimap <std::string, std::string> DictionaryMap;

struct Dict
{
	Dict(DictionaryMap const& oldMap, DictionaryMap const& newMap);
	Dict() = default;
	DictionaryMap wordMap;
	DictionaryMap reversedWordMap;
	DictionaryMap newWordMap;
	std::string fileName;
};

void PrintCursor();
void PrintWelcomeMessage();
void PrintTranslations(std::vector<std::string> const& translations);
void RequestAddingNewWordToDictionary(std::string const& word, Dict& dictionary);
bool PromptToSave(std::istream& input);
bool GetUserResponseForTranslationOfWord(std::istream& input, std::string const& word, std::string& translatedWord);
bool GetUserResponseForSavingFile(std::istream& input);
bool GetTranslationsOfWord(std::string const& word, Dict& dictionary, std::vector<std::string>& translations);
void GetTranslationsFromMap(std::string const& word, DictionaryMap& map, std::vector<std::string>& translations);
bool IsDictionaryModified(Dict& dictionary);
void AddWordsPairToDictionary(std::pair<std::string, std::string> const& pair, Dict& dictionary);
void SaveDictionaryToFileIfNeeded(Dict& dictionary);
void SaveDictionaryToFile(Dict& dictionary);
Dict CreateDictionaryFromStream(std::istream& dictFile);
void SaveMapToStream(DictionaryMap& map, std::ostream& outputFile);
void ProcessEnteredWord(std::string const& word, Dict& dictionary);
bool ProcessCommand(std::string const& cmd, Dict& dictionary);
void ProcessInput(std::istream& input, Dict& dictionary);
void ValidateWord(std::string const& word);
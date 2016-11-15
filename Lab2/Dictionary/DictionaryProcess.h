#pragma once

typedef std::map<std::string, std::string> dict;

void PrintWelcomeMessage();
dict CreateDictionaryFromStream(std::istream& dictFile);
void ProcessInput(std::istream& input, dict& dict);
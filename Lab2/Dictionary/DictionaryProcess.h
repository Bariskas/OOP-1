#pragma once

typedef std::map<std::string, std::string> dict;

void PrintWelcomeMessage();
dict CreateDictionaryFromStream(std::ifstream& dictFile);
#include "stdafx.h"
#include "FileUtils.h"

void PrepareFileForRead(std::string const& fileName, std::ifstream& inputFile)
{
	inputFile = std::ifstream(fileName);
	if (!inputFile.is_open())
	{
		throw std::invalid_argument("Failed to open file for reading!");
	}
}

void PrepareFileForWrite(std::string const& fileName, std::ofstream& outputFile)
{
	outputFile = std::ofstream(fileName, std::ios::app);
	if (!outputFile.is_open())
	{
		throw std::invalid_argument("Failed to open file for writing!");
	}
}
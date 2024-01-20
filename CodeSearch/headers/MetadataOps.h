#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Metadata.h"
#include <algorithm>
#include <regex>
class MetadataOps 
{
	public:
		void GetFileMetaData(FileMetadata* fmd, std::vector<TokenMetadata>* tokens);
		void ReadFilesIntoBuffer(std::filesystem::path& path, std::vector<std::string>* fbuffer);
	private:
		void PatternEntry(std::regex& pattern, std::vector<std::string> *patternName, std::string& line);
		void LineTokenizer(std::string& line, std::vector<std::string> *classNames, std::vector<std::string> *structNames, std::vector<std::string> *enumNames, std::vector<std::string> *functionNames);
};
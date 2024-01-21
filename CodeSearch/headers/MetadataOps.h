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
		void PatternEntry(std::regex& pattern, std::string* code, std::vector<TokenMetadata>* tokens, const std::string& patternName, FileMetadata* filemd);
		void CodeTokenizer(std::string* code, std::vector<TokenMetadata>* tokens, FileMetadata* filemd);
};
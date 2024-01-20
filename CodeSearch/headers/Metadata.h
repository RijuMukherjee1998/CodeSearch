#pragma once

#include<string>
#include <filesystem>

#include "Extensions.h"

struct FileMetadata 
{
	std::filesystem::path filepath;
	Extensions ext;

};

struct TokenMetadata {
	TokenType ttype;
	std::string tokenName;
	unsigned int token_line_no;
	FileMetadata fmd;
};

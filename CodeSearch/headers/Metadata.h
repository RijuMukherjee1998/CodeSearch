#pragma once

#include<string>
#include <filesystem>

#include "Extensions.h"

struct FileMetadata 
{
	std::filesystem::path filepath;
	Extensions ext;
};

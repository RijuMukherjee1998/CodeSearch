#pragma once

#include <iostream>
#include <filesystem>
#include <thread>
#include <stack>
#include <chrono>
#include "imgui.h"
#include "Extensions.h"
#include "Metadata.h"
#include "MetadataOps.h"

class FileController {
public:
	std::vector<std::string> FileCount_Iterator(const std::filesystem::path& repo_path, ImGuiTextBuffer* outputBuffer);
	std::vector<FileMetadata> FilterOutCodeFiles(std::vector<std::string>* allFiles);
	void SerializeFileMetaData(FileMetadata* fmd);


private:
	int file_count = 0;
	Extensions StringsToEnum(std::string& str);

	void Serialize_TokenMetaData(std::ofstream& ofs, TokenMetadata& tmd);
	void Deserialize_TokenMetaData(std::ifstream& ifs, TokenMetadata& tmd);

public:
	void AppendTextToBuffer(ImGuiTextBuffer* outputBuffer, const char* text)
	{
		try {
			outputBuffer->append(text);
			outputBuffer->append("\n");
		}
		catch (std::exception e) {
			std::cerr << e.what() << std::endl;
			throw;
		}
	}
	void ClearOutputBuffer(ImGuiTextBuffer* outputBuffer) {
		outputBuffer->clear();
	}

};
#pragma once

#include <iostream>
#include <filesystem>
#include <thread>
#include <stack>
#include <chrono>
#include "imgui.h"

class FileController {
public:
	std::vector<std::string> FileCount_Iterator(const std::filesystem::path& repo_path, ImGuiTextBuffer& outputBuffer);
private:
	int file_count = 0;

public:
	void AppendTextToBuffer(ImGuiTextBuffer& outputBuffer, const char* text)
	{
		try {
			outputBuffer.append(text);
			outputBuffer.append("\n");
		}
		catch (std::exception e) {
			std::cerr << e.what() << std::endl;
			throw;
		}
	}
	void ClearOutputBuffer(ImGuiTextBuffer& outputBuffer) {
		outputBuffer.clear();
	}

};
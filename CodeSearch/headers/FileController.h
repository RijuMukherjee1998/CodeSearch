#pragma once

#include <iostream>
#include <filesystem>
#include <thread>
#include <stack>
#include <chrono>

class FileController {
public:
	static FileController* GetInstance();
	unsigned int FileCount(const std::filesystem::path& repo_path);
	unsigned int FileCount_Iterator(const std::filesystem::path& repo_path);
	void TestPrint();
private:
	int file_count = 0;



};
#include "FileController.h"

std::vector<std::string> FileController::FileCount_Iterator(const std::filesystem::path& repo_path, ImGuiTextBuffer& outBuffer) {
	std::stack<std::filesystem::path> dir_stack;
	std::vector<std::string> allFiles;
	int fileCount = 0;
	//std::cout << repo_path << std::endl;
	ClearOutputBuffer(outBuffer);
	if (repo_path.empty() || !std::filesystem::exists(repo_path)) {
		fileCount = 0;
		std::cout << "No Such Dir Exist" << std::endl;
		return allFiles;
	}
	dir_stack.push(repo_path);
	
	while (!dir_stack.empty())
	{
		try 
		{
			std::filesystem::path current_dir = dir_stack.top();
			dir_stack.pop();
			for (const auto& entry : std::filesystem::directory_iterator(current_dir)) {
				if (entry.is_directory()) {
					dir_stack.push(entry.path());
				}
				else if (entry.is_regular_file()) {
					++fileCount;
				}
				if (!entry.path().empty()) {
					std::string pstr = entry.path().generic_string();
					allFiles.push_back(pstr);
					const char* path = pstr.c_str();
					AppendTextToBuffer(outBuffer, path);
				}
			}
		}
		catch (std::exception e) {
			std::cerr << e.what() << std::endl;
			AppendTextToBuffer(outBuffer, "Unable to Load into Dir.");
			continue;
		}
	}

	return allFiles;
}

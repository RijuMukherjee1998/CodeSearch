#include "../../headers/FileController.h"

unsigned int FileController::FileCount(const std::filesystem::path& repo_path) {
	int fileCount = 0;
	std::cout << repo_path << std::endl;
	if (repo_path.empty()) {
		fileCount = 0;
		std::cout << "No Such Dir Exist" << std::endl;
		return 0;
	}

	for (const auto& entry : std::filesystem::directory_iterator(repo_path)) {
		if (entry.is_directory()) {
			fileCount += FileCount(entry.path());
		}
		else if (entry.is_regular_file()) {
			++fileCount;
		}
	}
	return fileCount;
}

unsigned int FileController::FileCount_Iterator(const std::filesystem::path& repo_path) {
	std::stack<std::filesystem::path> dir_stack;
	int fileCount = 0;
	std::cout << repo_path << std::endl;
	if (repo_path.empty() || !std::filesystem::exists(repo_path)) {
		fileCount = 0;
		std::cout << "No Such Dir Exist" << std::endl;
		return 0;
	}
	dir_stack.push(repo_path);
	
	while (!dir_stack.empty())
	{
		try 
		{
			std::filesystem::path current_dir = dir_stack.top();
			dir_stack.pop();
			std::cout << current_dir << std::endl;
			for (const auto& entry : std::filesystem::directory_iterator(current_dir)) {
				if (entry.is_directory()) {
					dir_stack.push(entry.path());
				}
				else if (entry.is_regular_file()) {
					++fileCount;
				}
			}
		}
		catch (std::exception e) {
			std::cerr << e.what() << std::endl;
		}
	}

	return fileCount;
}

void FileController::TestPrint() {
	std::cout << "Hello Thread" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout << "Delay complete!" << std::endl;
	std::cout << "End Thread" << std::endl;

}

/*void FileController::PrintPermission(std::filesystem::perms permissions) {
	namespace fs = std::filesystem;
	std::cout << "Owner Read: " << ((permissions & fs::perms::owner_read) != fs::perms::none) << std::endl;
	std::cout << "Owner Write: " << ((permissions & fs::perms::owner_write) != fs::perms::none) << std::endl;
	std::cout << "Owner Execute: " << ((permissions & fs::perms::owner_exec) != fs::perms::none) << std::endl;
	std::cout << "Group Read: " << ((permissions & fs::perms::group_read) != fs::perms::none) << std::endl;
	std::cout << "Group Write: " << ((permissions & fs::perms::group_write) != fs::perms::none) << std::endl;
	std::cout << "Group Execute: " << ((permissions & fs::perms::group_exec) != fs::perms::none) << std::endl;
	std::cout << "Others Read: " << ((permissions & fs::perms::others_read) != fs::perms::none) << std::endl;
	std::cout << "Others Write: " << ((permissions & fs::perms::others_write) != fs::perms::none) << std::endl;
	std::cout << "Others Execute: " << ((permissions & fs::perms::others_exec) != fs::perms::none) << std::endl;
}*/

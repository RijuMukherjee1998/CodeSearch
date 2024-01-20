
#include "FileController.h"


std::vector<std::string> FileController::FileCount_Iterator(const std::filesystem::path& repo_path, ImGuiTextBuffer* outBuffer) {
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
					allFiles.emplace_back(pstr);
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

std::vector <FileMetadata> FileController::FilterOutCodeFiles(std::vector<std::string>* allFiles) {
	std::vector<FileMetadata> filteredFiles;
	for(std::vector<std::string>::const_iterator cit = allFiles->cbegin(); cit != allFiles->cend(); cit++ )
	{
		std::filesystem::path filePath(*cit);
		std::string extension = filePath.extension().string();
		Extensions ext = StringsToEnum(extension);
		if (ext != Extensions::notsupported) {
			std::cout <<"Extension is :"<< extension << std::endl;
			FileMetadata fmd;
			fmd.filepath = filePath;
			fmd.ext = ext;
			filteredFiles.emplace_back(fmd);
		}		
	}
	return filteredFiles;
}

void FileController::SerializeFileMetaData(FileMetadata* fmd)
{
	MetadataOps mdops;
	std::vector<TokenMetadata>* tokens = new std::vector<TokenMetadata>();
	mdops.GetFileMetaData(fmd, tokens);
	std::filesystem::path currentPath = std::filesystem::current_path();

	std::ofstream c_ofstream(currentPath.append("\\data\\class.jrn"), std::ios::binary);
	std::ofstream s_ofstream(currentPath.append("\\data\\struct.jrn"), std::ios::binary);
	std::ofstream e_ofstream(currentPath.append("\\data\\enum.jrn"), std::ios::binary);
	std::ofstream f_ofstream(currentPath.append("\\data\\function.jrn"), std::ios::binary);
	if (tokens != NULL)
	{
		for (int i = 0; i < tokens->size(); i++)
		{
			if (tokens->at(i).ttype == TokenType::CLASS)
			{
				std::cout<< "CLASS" << std::endl;
				std::cout << tokens->at(i).tokenName << std::endl;
				std::cout << tokens->at(i).token_line_no << std::endl;
				std::cout << tokens->at(i).fmd.filepath << std::endl;
				Serialize_TokenMetaData(c_ofstream, tokens->at(i));
			}
			else if (tokens->at(i).ttype == TokenType::STRUCT)
			{
				std::cout << "STRUCT" << std::endl;
				std::cout << tokens->at(i).tokenName << std::endl;
				std::cout << tokens->at(i).token_line_no << std::endl;
				std::cout << tokens->at(i).fmd.filepath << std::endl;
				Serialize_TokenMetaData(s_ofstream, tokens->at(i));
			}
			else if (tokens->at(i).ttype == TokenType::ENUM)
			{
				std::cout << "ENUM" << std::endl;
				std::cout << tokens->at(i).tokenName << std::endl;
				std::cout << tokens->at(i).token_line_no << std::endl;
				std::cout << tokens->at(i).fmd.filepath << std::endl;
				Serialize_TokenMetaData(e_ofstream, tokens->at(i));
			}
			else if (tokens->at(i).ttype == TokenType::FUNCTION)
			{
				std::cout << "FUNCTION" << std::endl;
				std::cout << tokens->at(i).tokenName << std::endl;
				std::cout << tokens->at(i).token_line_no << std::endl;
				std::cout << tokens->at(i).fmd.filepath << std::endl;
				Serialize_TokenMetaData(f_ofstream, tokens->at(i));
			}
		}
	}
	else
	{
		std::cout << "Token Meta Data is null";
	}
}
void FileController::Serialize_TokenMetaData(std::ofstream& ofs, TokenMetadata& tmd)
{
	ofs.write(reinterpret_cast<const char*>(&tmd.ttype), sizeof(tmd.ttype));
	
	size_t tokenNameSize = tmd.tokenName.size();
	ofs.write(reinterpret_cast<const char*>(&tokenNameSize), sizeof(tokenNameSize));
	ofs.write(tmd.tokenName.c_str(), tokenNameSize);

	ofs.write(reinterpret_cast<const char*>(&tmd.token_line_no), sizeof(tmd.token_line_no));
	ofs.write(reinterpret_cast<const char*>(&tmd.fmd), sizeof(tmd.fmd));
}

Extensions FileController::StringsToEnum(std::string& str)
{

	if (str == ".c") {
		return Extensions::c;
	}
	else if(str == ".cpp")
	{
		return Extensions::cpp;
	}
	else if(str == ".cc")
	{
		return Extensions::cpp;
	}
	else if (str == ".h")
	{
		return Extensions::h;
	}
	else if (str == ".hpp")
	{
		return Extensions::h;
	}
	else if (str == ".cs") 
	{
		return Extensions::cs;
	}
	else if (str == ".java")
	{
		return Extensions::java;
	}
	else if (str == ".py")
	{
		return Extensions::py;
	}
	else if (str == ".js")
	{
		return Extensions::js;
	}
	else if (str == ".rb")
	{
		return Extensions::rb;
	}
	else if (str == ".swift")
	{
		return Extensions::swift;
	}
	else if (str == ".go")
	{
		return Extensions::go;
	}
	else if (str == ".rs")
	{
		return Extensions::rs;
	}
	else if (str == ".ts")
	{
		return Extensions::ts;
	}
	else
	{
		return Extensions::notsupported;
	}
	return Extensions::notsupported;
}

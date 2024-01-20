#include "MetadataOps.h"


void MetadataOps::GetFileMetaData(FileMetadata* filemd, std::vector<TokenMetadata>* tokens)
{
    std::vector <std::string> *fileBuffer = new std::vector<std::string>();
	ReadFilesIntoBuffer(filemd->filepath, fileBuffer);
    
    std::vector<std::string> *classNames = new std::vector<std::string>();
    std::vector<std::string> *structNames = new std::vector<std::string>();
    std::vector<std::string> *enumNames = new std::vector<std::string>();
    std::vector<std::string> *functionNames = new std::vector<std::string>();

    TokenMetadata tmd ;
    size_t no_of_lines = fileBuffer->size();
    std::cout << "No of Lines = " << no_of_lines << std::endl;
    for (int i = 0; i < no_of_lines; i++) {
        std::string line = fileBuffer->at(i);
        std::cout << " line is " << line << std::endl;
        LineTokenizer(line, classNames, structNames, enumNames, functionNames);
    }
    for (int i = 0; i < classNames->size(); i++) {
        tmd.ttype = TokenType::CLASS;
        tmd.tokenName = classNames->at(i);
        tmd.token_line_no = i;
        tmd.fmd = *filemd;
        tokens->emplace_back(tmd);
    }
    for (int i = 0; i < structNames->size(); i++) {
        tmd.ttype = TokenType::STRUCT;
        tmd.tokenName = structNames->at(i);
        tmd.token_line_no = i;
        tmd.fmd = *filemd;
        tokens->emplace_back(tmd);
    }
    for (int i = 0; i < enumNames->size(); i++) {
        tmd.ttype = TokenType::ENUM;
        tmd.tokenName = enumNames->at(i);
        tmd.token_line_no = i;
        tmd.fmd = *filemd;
        tokens->emplace_back(tmd);
    }
    for (int i = 0; i < functionNames->size(); i++) {
        tmd.ttype = TokenType::FUNCTION;
        tmd.tokenName = functionNames->at(i);
        tmd.token_line_no = i;
        tmd.fmd = *filemd;
        tokens->emplace_back(tmd);
    }
    free(classNames);
    free(structNames);
    free(enumNames);
    free(functionNames);
}

void MetadataOps::ReadFilesIntoBuffer(std::filesystem::path& fpath, std::vector<std::string>* fileBuffer) {

    // Check if the file exists
    if (!std::filesystem::exists(fpath)) {
        std::cerr << "File does not exist." << std::endl;
        return;
    }

    // Create an ifstream object to open and read the file
    std::ifstream inputFile(fpath);

    // Check if the file is open
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    // Read and display the content of the file
    std::string line;
    while (std::getline(inputFile, line)) {
        fileBuffer->emplace_back(line);
    }

    // Close the file when you're done
    inputFile.close();

}

void MetadataOps::LineTokenizer(std::string& line, std::vector<std::string> *classNames, std::vector<std::string> *structNames, std::vector<std::string> *enumNames, std::vector<std::string> *functionNames) {
    // Define regular expressions for identifying classes, structs, enums, and functions
    std::regex classPattern(R"class(\bclass\s+(\w+)\s*(?:(?::\s*\w+\s*)?[^;{]*\{?)?)class");
    std::regex structPattern("struct\\s+(\\w+)\\s*\\{");
    std::regex enumPattern(R"(\benum\s+(\w+)\s*\{)");
    std::regex functionPattern(R"(\b(?:\w+\s+)?(\w+)\s*\([^)]*\)\s*\{)");

    //class pattern matching
    PatternEntry(classPattern, classNames, line);
    //struct pattern matching
    PatternEntry(structPattern, structNames, line);
    //struct pattern matching
    PatternEntry(enumPattern, enumNames, line);
    //function pattern matching
    PatternEntry(functionPattern, functionNames, line);
}

void MetadataOps::PatternEntry(std::regex& pattern, std::vector<std::string> *patternName, std::string& line)
{
    std::sregex_iterator iter(line.begin(), line.end(), pattern);
    std::sregex_iterator end;
    while (iter != end) {
        std::smatch match = *iter;
        std::cout << match.str() << std::endl;
        patternName->emplace_back(match.str());
        ++iter;
    }
}
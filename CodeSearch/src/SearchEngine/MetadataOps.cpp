#include "MetadataOps.h"


void MetadataOps::GetFileMetaData(FileMetadata* filemd, std::vector<TokenMetadata>* tokens)
{
    std::vector <std::string> *fileBuffer = new std::vector<std::string>();
	ReadFilesIntoBuffer(filemd->filepath, fileBuffer);

    size_t no_of_lines = fileBuffer->size();
    std::string* code = new std::string();
    std::cout << "No of Lines = " << no_of_lines << std::endl;
    for (int i = 0; i < no_of_lines; i++)
    {
        code->append(fileBuffer->at(i));
    }
    CodeTokenizer(code,tokens,filemd);
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

void MetadataOps::CodeTokenizer(std::string* code, std::vector<TokenMetadata>* tokens, FileMetadata* filemd) {
    // Define regular expressions for identifying classes, structs, enums, and functions
    std::regex classPattern(R"class(\bclass\s+(\w+)\s*(?:(?::\s*\w+\s*)?[^;{]*\{?)?)class");
    std::regex structPattern("struct\\s+(\\w+)\\s*\\{");
    std::regex enumPattern(R"(\benum\s+(\w+)\s*\{)");
    std::regex functionPattern(R"(\b(?:\w+\s+)?(\w+)\s*\([^)]*\)\s*(?:\n|\r\n?)?\{)");

    //class pattern matching
    PatternEntry(classPattern,code,tokens,"class", filemd);
    //struct pattern matching
    PatternEntry(structPattern,code,tokens,"struct", filemd);
    //struct pattern matching
    PatternEntry(enumPattern,code,tokens,"enum", filemd);
    //function pattern matching
    PatternEntry(functionPattern,code,tokens,"function", filemd);
}

void MetadataOps::PatternEntry(std::regex& pattern, std::string *code, std::vector<TokenMetadata>* tokens, const std::string& patternName, FileMetadata* filemd)
{
    std::sregex_iterator iter(code->begin(), code->end(), pattern);
    std::sregex_iterator end;
    TokenMetadata tmd;
    while (iter != end) {
        std::smatch match = *iter;
        std::cout << match.str() << std::endl;
        if (patternName == "class") {
            tmd.ttype = TokenType::CLASS;
            tmd.tokenName = match[1].str();
            tmd.token_line_no = 1;
            tmd.fmd = *filemd;
            tokens->emplace_back(tmd);
            ++iter;
        }
        else if (patternName == "struct") {
            tmd.ttype = TokenType::STRUCT;
            tmd.tokenName = match[1].str();
            tmd.token_line_no = 1;
            tmd.fmd = *filemd;
            tokens->emplace_back(tmd);
            ++iter;
        }
        else if (patternName == "enum") {
            tmd.ttype = TokenType::ENUM;
            tmd.tokenName = match[1].str();
            tmd.token_line_no = 1;
            tmd.fmd = *filemd;
            tokens->emplace_back(tmd);
            ++iter;
        }
        else if (patternName == "function") {
            tmd.ttype = TokenType::FUNCTION;
            tmd.tokenName = match[1].str();
            tmd.token_line_no = 1;
            tmd.fmd = *filemd;
            tokens->emplace_back(tmd);
            ++iter;
        }
    }
}
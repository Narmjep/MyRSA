#include "char.h"

bool CopyTextFileContent(const std::string& path, std::string& output){
	std::ifstream file(path, std::ios::binary);
    std::string fileStr;
    std::istreambuf_iterator<char> inputIt(file), emptyInputIt;
    std::back_insert_iterator<std::string> stringInsert(fileStr);
    copy(inputIt, emptyInputIt, stringInsert);

    output = fileStr;
    return true;
}

std::vector<char> CopyBinFileContent(const std::string& path) {
    std::ifstream input(path, std::ios::binary);
    std::vector<char> buffer(std::istreambuf_iterator<char>(input), {}); // contains more than content
    return buffer;
}

bool CharToInt(const char* input, int* output, size_t size) {
    for (int i = 0; i < (int)size; i++) {
        output[i] = (int)input[i];
    }
    return true;
}



bool IntToChar(int* input, char* output, size_t size) {
    for (int i = 0; i < (int)size; i++) {
        output[i] = (char)input[i];
    }
    return true;
}

bool XOR(int key, int* input, int* output, size_t size) {
    for (int i = 0; i < size; i++) {
        int in = input[i];
        int dig = key ^ in;
        output[i] = dig;
    }

    return true;
}
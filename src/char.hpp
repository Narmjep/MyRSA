#pragma once
#include <iostream>
#include <fstream>
#include <string.h>
#include <cstddef>
#include <vector>

/// @brief Stores the content of a file to a string.
/// @param path The path to the file.
/// @param output The string the content will be stored in.
/// @return true on success, false on failure.
bool CopyTextFileContent(const std::string& path, std::string& output){
	std::ifstream file(path, std::ios::binary);
    std::string fileStr;
    std::istreambuf_iterator<char> inputIt(file), emptyInputIt;
    std::back_insert_iterator<std::string> stringInsert(fileStr);
    copy(inputIt, emptyInputIt, stringInsert);

    output = fileStr;
    return true;
}

/// @brief Stores the content of a file to a string.
/// @param path The path to the file.
/// @param output The string the content will be stored in.
/// @return true on success, false on failure.
std::vector<char> CopyBinFileContent(const std::string& path) {
    std::ifstream input(path, std::ios::binary);
    std::vector<char> buffer(std::istreambuf_iterator<char>(input), {}); // contains more than content
    return buffer;
}

/**
 * @brief Turns a char[] to a int[]
 * 
 * @param input input array
 * @param output output array
 * @param size number of bytes to convert
 * @return true on success
 * @return false false on failure
 */
bool CharToInt(const char* input, int* output, size_t size) {
    for (int i = 0; i < (int)size; i++) {
        output[i] = (int)input[i];
    }
    return true;
}


/**
 * @brief Turns a int[] to a char[]
 * 
 * @param input input array
 * @param output output array
 * @param size number of ints to convert
 * @return true on success
 * @return false false on failure
 */
bool IntToChar(int* input, char* output, size_t size) {
    for (int i = 0; i < (int)size; i++) {
        output[i] = (char)input[i];
    }
    return true;
}

/**
 * @brief Encrypts an array using XOR encryption
 * 
 * @param key the value that will be XOR'd with the input.
 * @param input input array
 * @param output output array
 * @param size number of ints to encrypt
 * @return true on success
 * @return false on failure
 */
bool XOR(int key, int* input, int* output, size_t size) {
    for (size_t i = 0; i < size; i++) {
        int in = input[i];
        int dig = key ^ in;
        output[i] = dig;
    }

    return true;
}
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
bool CopyTextFileContent(const std::string& path, std::string& output);

/**
 * @brief Gets the bytes of a file.
 * 
 * @param path Path to the file.
 * @return std::vector<char> A vector containing the bytes read
 */
std::vector<char> CopyBinFileContent(const std::string& path);

/**
 * @brief Turns a char[] to a int[]
 * 
 * @param input input array
 * @param output output array
 * @param size number of bytes to convert
 * @return true on success
 * @return false false on failure
 */
bool CharToInt(const char* input, int* output, size_t size);


/**
 * @brief Turns a int[] to a char[]
 * 
 * @param input input array
 * @param output output array
 * @param size number of ints to convert
 * @return true on success
 * @return false false on failure
 */
bool IntToChar(int* input, char* output, size_t size);

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
bool XOR(int key, int* input, int* output, size_t size);
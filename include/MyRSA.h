#pragma once
#include "ppcm_pgcd.h"
#include <vector>
#include "json.hpp"
#include <fstream>
#include <iomanip>

#define SMALLEST_RANGE_VALUE 7
#define DEFAULT_DATA_FILE_NAME "data.bin"


using json = nlohmann::json;

namespace RSA {

	/// @brief A Key used for encryption or decryption
	struct Key {
		std::string type;
		int N;
		int X;
		/// @brief Constructor
		/// @param path Path to the json file
		Key(std::string path);
	};;

	/// @brief Calculates a pair of key
	/// @param range The closest prime number that is smaller or equal to range will be the largest possible prime used in the calculations.
	/// @param publicKey receives the N and x value for the public key
	/// @param privateKey receives the N and x value for the private key.
	/// @return 
	bool CreateKeys(size_t range, int publicKey[2], int privateKey[2]);
	/// @brief Encrypts an array using RSA encryption
	/// @param input the input array to be encrypted
	/// @param output receives the encrypted ints
	/// @param size number of ints to be encrypted
	/// @param pub the key used for the encryption.
	/// @return true on success, false on failure.
	bool EncryptMessage(int input[], int output[], size_t size, int pub[2]);
	/// @brief Encrypts an array using RSA encryption
	/// @param input the input array to be encrypted
	/// @param output receives the encrypted ints
	/// @param size number of ints to be encrypted
	/// @param key the key used for the encryption.
	/// @return true on success, false on failure.
	bool EncryptMessage(int input[], int output[], size_t size, RSA::Key& key);
	/// @brief Decrypts an array using RSA encryption
	/// @param input the input array to be encrypted
	/// @param output receives the decrypted ints
	/// @param size number of ints to be decrypted
	/// @param priv the key used for the decryption.
	/// @return true on success, false on failure.
	bool DecryptMessage(int input[], int output[], size_t size, int priv[2]);
	/// @brief Decrypts an array using RSA decryption
	/// @param input the input array to be decrypted
	/// @param output receives the decrypted ints
	/// @param size number of ints to be decryption
	/// @param key the key used for the decryption.
	/// @return true on success, false on failure.
	bool DecryptMessage(int input[], int output[], size_t size, RSA::Key& key);

	// Json

	/// @brief Creates a Key json file
	/// @param path Path of the new file
	/// @param type they type of the key. This can be set to  either "private" or "public".
	/// @param N 
	/// @param x 
	/// @return true on success, false on failure
	bool WriteKeyFile(const std::string& path, const std::string& type, int N, int x);

	//Optimization
	
	namespace Optimization {

		/**
		 * @brief Loads the content of the data file to memory. Call this before calling GetCompositionFromData(int number) or CompositionEcists(int number).
		 * 
		 * @param dataFile An input stream from the data file
		 * @return true on success, otherwise fale
		 */
		bool LoadDataFileToMemory(const std::string& dataFile);

		/// @brief Frees the content of the data file
		void FreeData();

		/// @brief Verifies that the compostion of the number is contained in the data file
		/// @param number the number to be verified
		/// @return true if it is contained, otherwise false
		bool CompositionExists(int number);

		/**
		 * @brief Writes the composition of a range of number to a data file
		 * 
		 * @param path The path to the output file
		 * @param begin first number included
		 * @param end last number included
		 * @return true on success
		 * @return false on failure
		 */
		bool WritePrimeDecompositionToFile(const std::string& path, int begin, int end);
	
		/**
		 * @brief Get the prime decomposition of a number from a data file. Make sure to load the file into memory fist using LoadDataFileToMemory(std::ifstream dataFile).
		 * 
		 * @param number 
		 * @return std::vector<int> vector containing the decomposition
		 */
		std::vector<int> GetCompositionFromData(int number);
	};
	
};
#pragma once
#include "ppcm_pgcd.h"
#include <vector>
#include "json.hpp"
#include <fstream>
#include <iomanip>



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
		 * @brief 
		 * 
		 * @param path 
		 * @return true 
		 * @return false 
		 */
		bool CompositionExists(std::ifstream& file, int number);

		/**
		 * @brief 
		 * 
		 * @param path 
		 * @param begin 
		 * @param end 
		 * @return true 
		 * @return false 
		 */
		bool WritePrimeDecompositionToFile(const std::string& path, int begin, int end);
	
		/**
		 * @brief 
		 * 
		 * @param path 
		 * @param number 
		 * @return std::vector<int> 
		 */
		std::vector<int> DeserializePrimeCompositionFile(std::string path, int number);
	};
	
};
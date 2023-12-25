#pragma once
#include "myrsa_math.hpp"
#include <vector>
#include "json.hpp"
#include <fstream>
#include <iomanip>
#include <chrono>

#define SMALLEST_RANGE_VALUE 7
#define DEFAULT_DATA_FILE_NAME "data.bin"

using json = nlohmann::json;

namespace RSA{

    /// @brief A Key used for encryption or decryption
	struct Key {
		std::string type;
		int N;
		int X;
		/// @brief Constructor
		/// @param path Path to the json file
		Key(std::string path);
	};

    Key::Key(std::string path) {
        std::ifstream keyfile(path);
        if(keyfile.good() == false){
            std::cerr << "Incorrect filestream: " << path << std::endl;
        }
        json data;
        keyfile >> data;

        this->type = data.value("Type", "Error");
        this->N = data.value("N", 0);
        this->X = data.value("X", 0);
    }

    /**
     * @brief Get the first N prime numbers from 13 to N included
     * 
     * @param N 
     * @return std::vector<int> 
     */
    static std::vector<int> GetMinPrimes(int N) {
        std::vector<int> returnlist = GetPrimes(N);
        for (int i = 0; i <= 4; i++) {
            returnlist.erase(returnlist.begin());
        }
        return returnlist;
    }

    namespace Optimization{
        static size_t dataSize;

        static void inline writeToFile(std::ofstream& file, int number){
            file.write(reinterpret_cast<char*>(&number) , sizeof(number));
        }

        static int inline ReadValueFromArray(std::ifstream& file){
            char buffer[sizeof(int)];
            file.read(buffer, sizeof(int));
            return *reinterpret_cast<int*>(buffer);
        }

        static const char* ReadCacheFile(std::ifstream& inputFile){
            inputFile.seekg(0, std::ios::end);
            size_t fileSize = (size_t)inputFile.tellg();
            inputFile.seekg(0, std::ios::beg);
            char* fileData = new char[fileSize];
            dataSize = fileSize;
            inputFile.read(fileData, fileSize);
            return fileData;
        }

        static inline bool DataNotLoaded(){
            std::cerr << "No cache file has been loaded to memory. Use LoadCacheFileToMemory(str::string& path) before calling this method!\n";
            return false;
        }

        /*
            Data file format:
            Offset(4 bytes)     Value
            0                   range begin
            1                   range end
            2                   size n0 composition
            3                   n0 composition 1
            4                   n0 composition 2
            ...
            x                   size n1 composition
            x + 1               n1 composition 1
            ...
        */

        static const int* data = nullptr;

        #define isDataLoaded (data != nullptr)

        /**
         * @brief Loads the content of the data file to memory. Call this before calling GetCompositionFromData(int number) or CompositionEcists(int number).
         * 
         * @param dataFile An input stream from the data file
         * @return true on success, otherwise fale
         */
        bool LoadCacheFileToMemory(const std::string& path){
            std::ifstream inputFile(path);
            if(!inputFile.good()){
                std::cerr << "File " << path << " does not exist.\n";
                return false;
            }
            const char* content = ReadCacheFile(inputFile);
            data = reinterpret_cast<const int*>(content);
            return true;
            
        }

        /// @brief Frees the content of the data file
        void FreeData(){
            delete[] data;
        }

        /// @brief Verifies that the compostion of the number is contained in the data file
        /// @param number the number to be verified
        /// @return true if it is contained, otherwise false
        bool CompositionExistsInCache(int number){
            //Check if data loaded
            if(!isDataLoaded) return DataNotLoaded();
            int begin = data[0]; //read first
            int end = data[1]; // read second
            if( begin > number || number > end) return false;
            else return true;
        }

        /**
         * @brief Writes the composition of a range of number to a data file
         * 
         * @param path The path to the output file
         * @param begin first number included
         * @param end last number included
         * @return true on success
         * @return false on failure
         */
        bool WritePrimeDecompositionToFile(const std::string& path, int begin, int end){
            std::ofstream outputFile(path, std::ios::binary);
            //Write range of file
            writeToFile(outputFile, begin);
            writeToFile(outputFile, end);
            //Calculate prime decomposition
            std::vector<int> composition;
            int progress = 0;
            int range = end - begin;
            for (int i = begin; i <= end; i++) {
                //Calculate progress
                int newProgress = (i - begin) * 100 / (end - begin);
                if(newProgress - progress >= 10) {
                    progress = newProgress;
                    std::cout << "Progress: " << progress << "%\n";
                }
                //
                composition = Decompose(i);
                //Write size of composition
                writeToFile(outputFile,composition.size());
                //Write composition
                for(auto number : composition){
                    writeToFile(outputFile,number);
                }
            }
            outputFile.close();
            return true;
        }

        /**
                 * @brief Get the prime decomposition of a number from a data file. Make sure to load the file into memory fist using LoadCacheFileToMemory(std::ifstream dataFile).
                 * 
                 * @param number 
                 * @return std::vector<int> vector containing the decomposition
                 */
        std::vector<int> GetPrimeDecompositionFromCache(int number){
            std::vector<int> ret;
            //Check if data loaded
            if(!isDataLoaded){
                DataNotLoaded();
                return ret;
            }
            //Check if number is in range
            if(!CompositionExistsInCache(number)){
                std::cerr << "Number " << number << " is not in the cache! Using standard algorithm instead...\n";
                return Decompose(number);
            }
            
            const int* dataCpy = data;
            int counter = 0;
            int current = dataCpy[0];
            dataCpy += 2;
            while(current != number){
                size_t intsToSkip = *dataCpy;
                dataCpy += intsToSkip + 1;
                current++;
            }
            //Read composition
            size_t size = *dataCpy;
            dataCpy++;
            for(size_t i = 0; i < size; i++){
                int value = *dataCpy;
                ret.push_back(value);
                dataCpy++;
            }
            //Cleanup
            return ret;
        }

        /**
         * @brief Get the range of the data file
         * 
         * @param path path to the data file
         * @param begin the begin of the range will be stored here
         * @param end the end of the range will be stored here
         * @return true if the file exists and the range was read successfully
         * @return false otherwise
         */
        bool GetCacheRange(int& begin, int& end){
            if(!isDataLoaded){
                DataNotLoaded();
                return false;
            }
            begin = data[0];
            end = data[1];
            return true;
        }
    } // namespace Optimization

    /// @brief Calculates a pair of key
        /// @param range The closest prime number that is smaller or equal to range will be the largest possible prime used in the calculations.
        /// @param publicKey receives the N and x value for the public key
        /// @param privateKey receives the N and x value for the private key.
        /// @return 
    bool CreateKeys(size_t range, int publicKey[2], int privateKey[2]) {
        if(range < 17) range = 17;
        int p;
        int q;
        int N;
        int k;
        int x;

        //Keys
        int pub[2];
        int priv[2];
        std::vector<int> dval;
        int d = 0;
        std::vector<int> eval;
        int e = 0;

        //Get p and q
        std::vector<int> minPrimes = GetMinPrimes(range);
        x = rand() % minPrimes.size();
        p = minPrimes[x];
        q = p;

        while (q == p) {
            x = rand() % minPrimes.size();
            q = minPrimes[x];
        }

        //Get N
        N = p * q;
        //Get k
        k = (p - 1) * (q - 1);

        //Get e
        std::vector<int> eprimes;
        std::vector<int> kprimes;
        std::vector<int> evalues;
        //kprimes = Decompose(k);

        //Check if precalculated
        auto start = std::chrono::high_resolution_clock::now();
        //Check for cached data
        if(Optimization::LoadCacheFileToMemory(DEFAULT_DATA_FILE_NAME) && Optimization::CompositionExistsInCache(range - 1)){
            std::cout << "Using optimization\n";
            int begin;
            int end;
            Optimization::GetCacheRange(begin, end);
            printf("Cache file range: %d - %d\n", begin, end);
            kprimes = Optimization::GetPrimeDecompositionFromCache(k);
            for (size_t i = SMALLEST_RANGE_VALUE; i < range; i++) {
                eprimes = Optimization::GetPrimeDecompositionFromCache(i);
                if (CheckIfCommonInt(kprimes, eprimes) == false) {
                    evalues.push_back(i);
                }
            }
        } else {
        //No cached data available
            kprimes = Decompose(k);
            std::cout << "No precalculated values found.\n";
            for (size_t i = SMALLEST_RANGE_VALUE; i < range; i++) {
                eprimes = Decompose(i);
                if (CheckIfCommonInt(kprimes, eprimes) == false) {
                    evalues.push_back(i);
                }
            }
        }

        Optimization::FreeData();

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
        std::cout << "Decomposition duration: " << duration.count() << "ms\n";

        int random = rand() % evalues.size();
        e = evalues[random];

        //Get D
        std::vector<int> emult = GetMultiples(e, k);

        for (int i = 1; i <= k; i++) {
            if (emult[i] % k == 1) {
                d = i;
                break;
            }
        }

        //Generate Keys
        pub[0] = N;
        pub[1] = e;

        priv[0] = N;
        priv[1] = d;

        std::string keys = std::to_string(pub[0]) + "," + std::to_string(pub[1]) + "," + std::to_string(priv[0]) + "," + std::to_string(priv[1]);
        privateKey[0] = priv[0];
        privateKey[1] = priv[1];
        std::cout << std::endl;
        publicKey[0] = pub[0];
        publicKey[1] = pub[1];


        return true;
    }

    static int pow_mod(int m, int e, int n) {
        int x = m;
        for (int i = 1; i < e; i++) {
            x = (x * m) % n;
        }
        return x;
    }

    /// @brief Encrypts an array using RSA encryption
        /// @param input the input array to be encrypted
        /// @param output receives the encrypted ints
        /// @param size number of ints to be encrypted
        /// @param pub the key used for the encryption.
        /// @return true on success, false on failure.
    bool EncryptMessage(int input[], int output[], size_t size, int pub[2]) {

        int c;
        int m;
        int n = pub[0];
        int e = pub[1];
        
        for (size_t i = 0; i < size; i++) {

            m = input[i];
            c = pow_mod(m, e, n);
            output[i] = c;
        }

        return true;
    }

    /// @brief Encrypts an array using RSA encryption
        /// @param input the input array to be encrypted
        /// @param output receives the encrypted ints
        /// @param size number of ints to be encrypted
        /// @param key the key used for the encryption.
        /// @return true on success, false on failure.
    bool EncryptMessage(int input[], int output[], size_t size, Key& key) {

        int c;
        int m;
        int n = key.N;
        int e = key.X;

        for (size_t i = 0; i < size; i++) {

            m = input[i];
            c = pow_mod(m, e, n);
            output[i] = c;
        }

        return true;
    }

    /// @brief Decrypts an array using RSA encryption
        /// @param input the input array to be encrypted
        /// @param output receives the decrypted ints
        /// @param size number of ints to be decrypted
        /// @param priv the key used for the decryption.
        /// @return true on success, false on failure.
    bool DecryptMessage(int input[], int output[], size_t size, Key& key) {

        int c;
        int m;
        int n = key.N;
        int d = key.X;

        for (size_t i = 0; i < size; i++) {

            c = input[i];
            m = pow_mod(c, d, n);
            output[i] = m;
        }

        return true;
    }

    /// @brief Decrypts an array using RSA decryption
        /// @param input the input array to be decrypted
        /// @param output receives the decrypted ints
        /// @param size number of ints to be decryption
        /// @param key the key used for the decryption.
        /// @return true on success, false on failure.
    bool DecryptMessage(int input[], int output[], size_t size, int priv[2]) {

        int c;
        int m;
        int n = priv[0];
        int d = priv[1];

        for (size_t i = 0; i < size; i++) {
            c = input[i];
            m = pow_mod(c, d, n);
            output[i] = m;
        }

        return true;
    }

    /// @brief Creates a Key json file
        /// @param path Path of the new file
        /// @param type they type of the key. This can be set to  either "private" or "public".
        /// @param N 
        /// @param x 
        /// @return true on success, false on failure
    bool WriteKeyFile(const std::string& path, const std::string& type, int N, int x) {
        std::ofstream keyfile(path);
        json Key =
        {
            {"Type",type},
            {"N",N},
            {"X",x}
        };

        keyfile << std::setw(4) << Key;

        return true;
    }


    
} // namespace RSA





#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

//Project

//Functions:

/**
 * @brief Prints a vector
 * 
 * @param vec the vector to be printed
 * @param name the name of the vector
 */
void Spell(std::vector<int> vec, const std::string& name);


/**
 * @brief Returns a vector of prime numbers from 2 to L included
 * 
 * @param L 
 * @return std::vector<int> 
 */
std::vector<int> GetPrimes(int L);

/**
 * @brief Check if N is a prime number
 * 
 * @param N 
 * @return true 
 * @return false 
 */
bool CheckIfPrime(int N);

/**
 * @brief Decompose N into its prime factors
 * 
 * @param N 
 * @return std::vector<int> 
 */
std::vector<int> Decompose(int N);


/**
 * @brief Get the multiples of N
 * 
 * @param N 
 * @param range then number of multiples to get
 * @return std::vector<int> 
 */
std::vector<int> GetMultiples(int N, int range);


/**
 * @brief Calculates the frequencies of the elements in a vector
 * 
 * @param comp 
 * @return std::vector<int> 
 */
std::vector<int> CalculateFrequencies(std::vector<int> comp);

/**
 * @brief Checks if two vectors have a common integer
 * 
 * @param vec1 
 * @param vec2 
 * @return true 
 * @return false 
 */
bool CheckIfCommonInt(std::vector<int> vec1, std::vector<int> vec2);

//PGCD & PPCM

/**
 * @brief returns the largest common divisor of N1 and N2
 * 
 * @param N1 
 * @param N2 
 * @return int 
 */
int GetLargestCommonDivisor(int N1, int N2);

/**
 * @brief returns the smallest common multiple of N1 and N2
 * 
 * @param N1 
 * @param N2 
 * @return int 
 */
int GetSmallestCommonMultiple(int N1, int N2);


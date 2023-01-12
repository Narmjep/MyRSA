#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

//Project

//Functions:

//Print vector

void spell(std::vector<int> vec, const std::string& name);


//Get Primes
std::vector<int> getprimes(int L);

//Check if prime

bool checkprime(int N);


//Decompose

std::vector<int> decompose(int N);


//Get Multiples

std::vector<int> multiples(int N, int range);

void printMultiples(int N, int range);

//Get Frequencies
std::vector<int> frequency(std::vector<int> comp);

//Cehck if two vectors contain similar elements
bool checkIfCommonInt(std::vector<int> vec1, std::vector<int> vec2);

//PGCD & PPCM

/**
 * @brief returns the largest common divisor of N1 and N2
 * 
 * @param N1 
 * @param N2 
 * @return int 
 */
int LCD(int N1, int N2);

/**
 * @brief returns the smallest common multiple of N1 and N2
 * 
 * @param N1 
 * @param N2 
 * @return int 
 */
int SCM(int N1, int N2);


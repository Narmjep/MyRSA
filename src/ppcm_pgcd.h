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


int PGCD(int N1, int N2);

int PPCM(int N1, int N2);


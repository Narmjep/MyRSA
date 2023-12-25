# pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <unordered_set>

//Print vector

/**
 * @brief Prints a vector
 * 
 * @param vec the vector to be printed
 * @param name the name of the vector
 */
void Spell (std::vector<int> vec, const std::string& name){
    std::cout<<name<<": ";
    for (size_t i=0; i<vec.size(); i++){
        std::cout<<vec[i]<<";";
    }
    std::cout<<std::endl;
}

/**
 * @brief Returns a vector of prime numbers from 2 to L included
 * 
 * @param L 
 * @return std::vector<int> 
 */
std::vector<int> GetPrimes(int L){
    //Create bitset
    std::vector<bool> primesSet(L+1,true);
    //Seive algorithm
    for(int i = 2; i <= L; i++){
        if(!primesSet[i]) continue;
        //set multiples of prime number to false
        for(int j = i*2; j <= L; j+=i){
            primesSet[j] = 0;
        }
    }
    //Create vector for compatibility reasons
    std::vector<int> result;
    for(int i = 2; i <= L; i++){
        if(primesSet[i]) result.push_back(i);
    }
    return result;
}

/**
 * @brief Check if N is a prime number
 * 
 * @param N 
 * @return true 
 * @return false 
 */
bool CheckIfPrime (int N){
    std::vector<int> primes = GetPrimes(N);
    for (size_t i= 0; i < primes.size();i++ ){
        if (N==primes[i]){
            return true;
        }
    }
    return false;
}

/**
 * @brief Decompose N into its prime factors
 * 
 * @param N 
 * @return std::vector<int> 
 */
std::vector<int> Decompose(int N){
    std::vector<int> composition;
    //N is a prime number
    if (CheckIfPrime(N) == true){
        composition.push_back(N);
    }
    //N is not a prime number
    else {
        //Calculate N^2 prime numbers
        std::vector<int> primes = GetPrimes((int)std::sqrt(N));
        //Cacluclate N mod prime numbers until N is a prime number or 1
        for(size_t i = 0; i < primes.size(); i++){
            while(N % primes[i] == 0){
                composition.push_back(primes[i]);
                N /= primes[i];
            }
            if(N == 1) break;
        }
        if(N != 1 && CheckIfPrime(N)) composition.push_back(N);
    }
    return composition;
}

/**
 * @brief Get the multiples of N
 * 
 * @param N 
 * @param range then number of multiples to get
 * @return std::vector<int> 
 */
std::vector<int> GetMultiples(int N, int range){
    std::vector<int> mult;
    for(int i=0;i<=range;i++){
        mult.push_back(i*N);
    }
    return mult;
}

/**
 * @brief Calculates the frequencies of the elements in a vector
 * 
 * @param comp 
 * @return std::vector<int> 
 */
std::vector<int> CalculateFrequencies (std::vector<int> composition){
    std::vector<int> freq;
    int prev = 0;
    for (size_t i=0;i<composition.size();i++){
        if (composition[i] == prev){

        } else {
        int f = std::count(composition.begin(),composition.end(),composition[i]);
        freq.push_back(f);
        }
        prev = composition[i];
    }
    return freq;
}

/**
 * @brief Checks if two vectors have a common integer
 * 
 * @param vec1 
 * @param vec2 
 * @return true 
 * @return false 
 */
bool CheckIfCommonInt(std::vector<int> vec1 , std::vector<int> vec2){
    std::unordered_set<int> set1_hash;
    for(int i : vec1){
        set1_hash.insert(i);
    }
    for(int i : vec2){
        if(set1_hash.count(i) > 0) return true;
    }
    return false;
}

/**
 * @brief returns the largest common divisor of N1 and N2
 * 
 * @param N1 
 * @param N2 
 * @return int 
 */
int GetLargestCommonDivisor (int N1 , int N2){
    std::vector<int> comp1 = Decompose(N1);
    std::vector<int> freq1 = CalculateFrequencies(comp1);
    std::vector<int> comp2 = Decompose(N2);
    std::vector<int> freq2 = CalculateFrequencies(comp2);
    std::vector<int> common;

    comp1.erase(unique(comp1.begin(),comp1.end()),comp1.end());
    comp2.erase(unique(comp2.begin(),comp2.end()),comp2.end());

    //Get common primes
    for (size_t i=0;i<comp1.size();i++){
        for (size_t k=0;k<comp2.size();k++){
            if (comp1[i]==comp2[k]){
                common.push_back(comp1[i]);
            }
        }
    }

    //Get lowest frequency
    std::vector<int> powers;

    for (size_t i=0; i <common.size(); i++){
        auto itr = std::find(comp1.begin(),comp1.end(),common[i]);
        int index = std::distance(comp1.begin(),itr);
        int fr1 = freq1[index];

        auto itr2 = std::find(comp2.begin(),comp2.end(),common[i]);
        int index2 = std::distance(comp2.begin(),itr2);
        int fr2 = freq2[index2];

        if (fr1 <= fr2){
            powers.push_back(fr1);
        } else {
            powers.push_back(fr2);
        }
    }
    //Final result
    double lcd = 1;
    for (size_t i=0;i<common.size();i++){
        lcd = lcd*pow(common[i],powers[i]);
    }
    return (int)lcd;
}

/**
 * @brief returns the smallest common multiple of N1 and N2
 * 
 * @param N1 
 * @param N2 
 * @return int 
 */
int GetSmallestCommonMultiple (int N1 , int N2){
    std::vector<int> comp1 = Decompose(N1);
    std::vector<int> freq1 = CalculateFrequencies(comp1);
    std::vector<int> comp2 = Decompose(N2);
    std::vector<int> freq2 = CalculateFrequencies(comp2);

    comp1.erase(unique(comp1.begin(),comp1.end()),comp1.end());
    comp2.erase(unique(comp2.begin(),comp2.end()),comp2.end());

    //Get all primes
    std::vector<int> common = Decompose(N1);
    for (size_t i=0; i<comp2.size();i++){
        common.push_back(comp2[i]);
    }
    std::sort(common.begin(),common.end());
    common.erase(unique(common.begin(),common.end()),common.end());

    //Get highest frequency
    std::vector<int> powers;

    for (size_t i=0; i<common.size(); i++){
        int index;
        int fr1;
        int index2;
        int fr2;

        if (std::count(comp1.begin(),comp1.end(),common[i])){
            auto itr = std::find(comp1.begin(),comp1.end(),common[i]);
            index = std::distance(comp1.begin(),itr);
            fr1 = freq1[index];
        } else{
            fr1 = 0;
        }
        if (std::count(comp2.begin(),comp2.end(),common[i])){
            auto itr2 = std::find(comp2.begin(),comp2.end(),common[i]);
            index2 = std::distance(comp2.begin(),itr2);
            fr2 = freq2[index2];
        } else{
            fr2 = 0;
        }

        if (fr1 >= fr2){
            powers.push_back(fr1);
        } else {
            powers.push_back(fr2);
        }
    }

    //Final result
    double scm = 1;
    for (size_t i=0; i < common.size(); i++){
        scm = scm*pow(common[i],powers[i]);
    }
    return (int)scm;
}




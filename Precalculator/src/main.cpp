#include <iostream>
#include <fstream>
#include <myRSA.hpp>
#include <vector>
#include <string>

#define DEFAULT_RANGE 8192
#define START 7

void writeToFile(std::ofstream& file, int number){
    file.write(reinterpret_cast<char*>(&number) , sizeof(number));
}

int main(int argc, char** argv){
    int range = DEFAULT_RANGE;
    try{
        if(argc > 1) range = std::stoi(argv[1]);
    } catch(...){
        std::cerr << "Invalid argument.\n";
        return -1;
    }
    std::cout << "Generating prime decomposition for numbers from " << START << " to " << range << "..." << std::endl;
    RSA::Optimization::WritePrimeDecompositionToFile("data.bin", START, range);
    std::cout << "Done." << std::endl;
    return 0;
}

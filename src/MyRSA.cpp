#include "MyRSA.h"
#include <chrono>

static std::vector<int> getMinPrimes(int N) {
    std::vector<int> returnlist = getprimes(N);
    for (int i = 0; i <= 4; i++) {
        returnlist.erase(returnlist.begin());
    }
    return returnlist;
}

RSA::Key::Key(std::string path) {
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

bool RSA::CreateKeys(size_t range, int publicKey[2], int privateKey[2]) {
    if(range < 17) range = 17;
    int p;
    int q;
    int N;
    int k;
    //int k = (p-1)*(q-1);

    int x;

    //Keys
    int pub[2];
    int priv[2];
    std::vector<int> dval;
    int d = 0;
    std::vector<int> eval;
    int e = 0;

    //Get p and q
    std::vector<int> minPrimes = getMinPrimes(range);
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
    kprimes = decompose(k);

    //Check if precalculated
    auto start = std::chrono::high_resolution_clock::now();
    if(RSA::Optimization::LoadDataFileToMemory(DEFAULT_DATA_FILE_NAME) && RSA::Optimization::CompositionExists(range - 1)){
        std::cout << "Using optimization\n";
        for (int i = SMALLEST_RANGE_VALUE; i < range; i++) {
            eprimes = RSA::Optimization::GetCompositionFromData(i);
            if (checkIfCommonInt(kprimes, eprimes) == false) {
                evalues.push_back(i);
            }
        }
    } else {
        std::cout << "No precalculated values found.\n";
        for (int i = SMALLEST_RANGE_VALUE; i < range; i++) {
            eprimes = decompose(i);
            if (checkIfCommonInt(kprimes, eprimes) == false) {
                evalues.push_back(i);
            }
        }
    }
    RSA::Optimization::FreeData();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
    std::cout << "Decomposition duration: " << duration.count() << '\n';

    //Get D
    do{
        int random = rand() % evalues.size();
        e = evalues[random];
        std::vector<int> emult = multiples(e, k);
        for (int i = 0; i <= k; i++) {
            if (emult[i] % k == 1) {
                d = i;
                break;
            }
        }
    } while(d == 0);


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

bool RSA::EncryptMessage(int input[], int output[], size_t size, int pub[2]) {

    int c;
    int m;
    int n = pub[0];
    int e = pub[1];
    
    for (int i = 0; i < size; i++) {

        m = input[i];
        c = pow_mod(m, e, n);
        output[i] = c;
    }

    return true;
}

bool RSA::EncryptMessage(int input[], int output[], size_t size, RSA::Key& key) {

    int c;
    int m;
    int n = key.N;
    int e = key.X;

    for (int i = 0; i < size; i++) {

        m = input[i];
        c = pow_mod(m, e, n);
        output[i] = c;
    }

    return true;
}

bool RSA::DecryptMessage(int input[], int output[], size_t size, RSA::Key& key) {

    int c;
    int m;
    int n = key.N;
    int d = key.X;

    for (int i = 0; i < size; i++) {

        c = input[i];
        m = pow_mod(c, d, n);
        output[i] = m;
    }

    return true;
}

bool RSA::DecryptMessage(int input[], int output[], size_t size, int priv[2]) {

    int c;
    int m;
    int n = priv[0];
    int d = priv[1];

    for (int i = 0; i < size; i++) {

        c = input[i];
        m = pow_mod(c, d, n);
        output[i] = m;
    }

    return true;
}

//Json

bool RSA::WriteKeyFile(const std::string& path, const std::string& type, int N, int x) {
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


//Optimization
static size_t dataSize;

static void inline writeToFile(std::ofstream& file, int number){
    file.write(reinterpret_cast<char*>(&number) , sizeof(number));
}

static int inline readValueFromArray(std::ifstream& file){
    char buffer[sizeof(int)];
    file.read(buffer, sizeof(int));
    return *reinterpret_cast<int*>(buffer);
}

static const char* readDataFile(std::ifstream& inputFile){
    inputFile.seekg(0, std::ios::end);
    size_t fileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);
    char* fileData = new char[fileSize];
    dataSize = fileSize;
    inputFile.read(fileData, fileSize);
    return fileData;
}

static inline bool dataNotLoaded(){
    std::cerr << "No data file has been loaded to memory. Use RSA::Optimization::LoadDataFileToMemory(str::string& path) before calling this method!\n";
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
    x                   size n2 composition
    ...
*/

static const int* data = nullptr;

#define isDataLoaded (data != nullptr)

bool RSA::Optimization::LoadDataFileToMemory(const std::string& path){
    std::ifstream inputFile(path);
    if(!inputFile.good()){
        std::cerr << "File " << path << " does not exist.\n";
        return false;
    }
    const char* content = readDataFile(inputFile);
    data = reinterpret_cast<const int*>(content);
    return true;
    
}

void RSA::Optimization::FreeData(){
    delete[] data;
}

bool RSA::Optimization::CompositionExists(int number){
    //Check if data loaded
    if(!isDataLoaded) return dataNotLoaded();
    int begin = data[0]; //read first
    int end = data[1]; // read second
    if( begin > number || number > end) return false;
    else return true;
}

//TODO Speed up
bool RSA::Optimization::WritePrimeDecompositionToFile(const std::string& path, int begin, int end){
    std::ofstream outputFile(path, std::ios::binary);
    //Write range of file
    writeToFile(outputFile, begin);
    writeToFile(outputFile, end);
    std::vector<int> composition;
    int progress = 0;
    int range = end - begin;
    for (int i = begin; i <= end; i++) {
        int newProgress = (i - begin) * 100 / (end - begin);
        if(newProgress - progress >= 10) {
            progress = newProgress;
            std::cout << "Progress: " << progress << "%\n";
        }
        composition = decompose(i);
        writeToFile(outputFile,composition.size());
        for(auto number : composition){
            writeToFile(outputFile,number);
        }
    }
    outputFile.close();
    return true;
}

std::vector<int> RSA::Optimization::GetCompositionFromData(int number){
    std::vector<int> ret;
    //Check if data loaded
    if(!isDataLoaded){
        dataNotLoaded();
        return ret;
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
    for(int i = 0; i < size; i++){
        int value = *dataCpy;
        ret.push_back(value);
        dataCpy++;
    }
    //Cleanup
    return ret;
}






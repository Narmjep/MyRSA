#include "MyRSA.h"

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

    for (int i = 7; i < range; i++) {
        eprimes = decompose(i);
        if (checkIfCommonInt(kprimes, eprimes) == false) {
            evalues.push_back(i);
        }
    }
    int random = rand() % evalues.size();
    e = evalues[random];

    //Get D
    std::vector<int> emult = multiples(e, k);

    for (int i = 0; i <= k; i++) {
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

bool RSA::WriteKeyFile(std::string path, std::string type, int N, int x) {
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

static void inline writeToFile(std::ofstream& file, int number){
    file.write(reinterpret_cast<char*>(&number) , sizeof(number));
}

static int inline readValueFromFile(std::ifstream& file){
    char buffer[sizeof(int)];
    file.read(buffer, sizeof(int));
    return reinterpret_cast<int>(buffer);
}

bool RSA::Optimization::CompositionExists(std::ifstream& file, int number){
    file.seekg(std::ios::beg);
    int begin = readValueFromFile(file); //read first
    int end = readValueFromFile(file); // read second
    if( begin > number || number > end) return false;
    else return true;
}

bool RSA::Optimization::WritePrimeDecompositionToFile(const std::string& path, int begin, int end){
    std::ofstream outputFile(path, std::ios::binary);
    //Write range of file
    writeToFile(outputFile, begin);
    writeToFile(outputFile, end);
    std::vector<int> composition;
    for (int i = begin; i <= end; i++) {
        std::cout << "Current: " << i << '\n';
        composition = decompose(i);
        writeToFile(outputFile,composition.size());
        for(auto number : composition){
            writeToFile(outputFile,number);
        }
    }
    outputFile.close();
    return true;
}

std::vector<int> RSA::Optimization::DeserializePrimeCompositionFile(std::string path, int number){
    std::ifstream inputFile(path, std::ios::binary);
    std::vector<int> ret;
    //File exists?
    if(!inputFile.good()){
        std::cerr << "File " << path << " does not exist.\n";
        return ret;
    }
    //Number in file?
    if(!CompositionExists(inputFile, number)){
        std::cout << path << " does not contain the composition of "<< number << '\n';
        return ret;
    }
    
    int counter = 0;
    inputFile.seekg(std::ios::beg);
    int current = readValueFromFile(inputFile);
    while(current != number){
        int bytesToSkip;
        current++;
    }



    
    


}




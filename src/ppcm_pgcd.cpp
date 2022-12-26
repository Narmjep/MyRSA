#include "ppcm_pgcd.h"








//---------------------------
//Functions:

//Print vector

void spell (std::vector<int> vec, const std::string& name){
    std::cout<<name<<": ";
    for (int i=0;i<vec.size();i++){
        std::cout<<vec[i]<<";";
    }
    std::cout<<std::endl;
}


//Get Primes
std::vector<int> getprimes(int L){

    //Calculating Prime numbers
    std::vector<int> list;
    list.push_back(2);
    bool prim = false;
    for (int i=3;i<=L;i++){
        prim = true;


        for (int n = 0; n < list.size(); n++){
            if (i%list[n] == 0){
                prim = false;
            }  
        }
        if (prim == true){
            list.push_back(i);
        }
    }


    //Convert Vector to array
    return list;
}

//Check if prime

bool checkprime (int N){
    std::vector<int> primes = getprimes(N);
    for (int i= 0;i < primes.size();i++ ){
        if (N==primes[i]){
            return true;
        }
    }
    return false;
}


//Decompose

std::vector<int> decompose(int N){

    std::vector<int> comp;

        if (checkprime(N) == true){
            comp.push_back(N);
  
        }

        else {
            int X = N;
            while (checkprime(X)==false){
                std::vector<int> primes = getprimes(N);
                for (int i = 0; i <= primes.size();i++){
                    if (X%primes[i] == 0){
                        comp.push_back(primes[i]);


                        X= X/primes[i];
                        break;
                    }
                }
            }
            comp.push_back(X);

        }


    //Resize vector

    

    return comp;
}

//Get Multiples

std::vector<int> multiples(int N, int range){
    std::vector<int> mult;
    for(int i=0;i<=range;i++){
        mult.push_back(i*N);
    }
    return mult;
}

void printMultiples(int N, int range){
    std::vector<int> mult;
    mult = multiples(N, range);
    for(int i=0;i<=range;i++){
        std::cout<<i<<": "<<mult[i]<<"\n";
    }
}

//Get Frequencies
std::vector<int> frequency (std::vector<int> comp){

    std::vector<int> freq;

    int prev = 0;
    for (int i=0;i<comp.size();i++){

        if (comp[i] == prev){
        
        } else {
        int f = std::count(comp.begin(),comp.end(),comp[i]);
        freq.push_back(f);
        }
        prev = comp[i];
    }

    return freq;
}

//Cehck if two vectors contain similar elements
bool checkIfCommonInt(std::vector<int> vec1 , std::vector<int> vec2){
    for (int i=0;i<vec1.size();i++){
        for (int j=0;j<vec2.size();j++){
            if(vec1[i]==vec2[j]){
                return true;
            }
        }
    }
    return false;
}

//PGCD & PPCM


int PGCD (int N1 , int N2){
    std::vector<int> comp1 = decompose(N1);
    std::vector<int> freq1 = frequency(comp1);
    std::vector<int> comp2 = decompose(N2);
    std::vector<int> freq2 = frequency(comp2);
    std::vector<int> common;

    comp1.erase(unique(comp1.begin(),comp1.end()),comp1.end());
    comp2.erase(unique(comp2.begin(),comp2.end()),comp2.end());


    //Get common primes
    for (int i=0;i<comp1.size();i++){
        for (int k=0;k<comp2.size();k++){

            if (comp1[i]==comp2[k]){

                common.push_back(comp1[i]);

            }
        }
    }


    //Get lowest frequency
    std::vector<int> powers;

    for (int i=0;i<common.size();i++){
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
    int pgcd = 1;

    for (int i=0;i<common.size();i++){
        pgcd = pgcd*pow(common[i],powers[i]);
    }





    return pgcd;
}

int PPCM (int N1 , int N2){
    std::vector<int> comp1 = decompose(N1);
    std::vector<int> freq1 = frequency(comp1);
    std::vector<int> comp2 = decompose(N2);
    std::vector<int> freq2 = frequency(comp2);


    comp1.erase(unique(comp1.begin(),comp1.end()),comp1.end());
    comp2.erase(unique(comp2.begin(),comp2.end()),comp2.end());


    //Get all primes
        std::vector<int> common = decompose(N1);
        for (int i=0; i<comp2.size();i++){
            common.push_back(comp2[i]);
        }
        std::sort(common.begin(),common.end());
        common.erase(unique(common.begin(),common.end()),common.end());

    //Get highest frequency
    std::vector<int> powers;

    for (int i=0;i<common.size();i++){

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
    int pgcd = 1;

    for (int i=0;i<common.size();i++){
        pgcd = pgcd*pow(common[i],powers[i]);
    }





    return pgcd;
}




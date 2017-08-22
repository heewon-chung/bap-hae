#include "generatingTools.h"

void generateRandomPtxt(vector<HAEPtxt>& ptxt, int num){
    ptxt.clear();
    ptxt.resize(num);
    
    for(unsigned long i = 0; i < num; i++){
        ptxt[i].msg = rand() % 10;
        ptxt[i].tag = rand() % 10;
    }
}

void generateBinaryMsg(vector<HAEPtxt>& ptxt, int num){
    ptxt.clear();
    ptxt.resize(num);
    
    for(unsigned long i = 0; i < num; i++){
        ptxt[i].msg = rand() % 2;
        ptxt[i].tag = rand() % 10;
    }
}

void generatingRandomizer(vector<HAEPtxt>& rnd, vector<HAECtxt>& encRnd, const HAESecKey& secretKey){
    rnd.clear();
    rnd.resize(NUMRANDOMIZER);

    #pragma omp parallel for
    for(unsigned long i = 0; i < NUMRANDOMIZER; i++){
        rnd[i].msg = RandomBits_ZZ(RANDOMBITS) % MSGSPACE;
        rnd[i].tag = conv<ZZ>(1);
    }
    encrypt(encRnd, rnd, secretKey);
}

void generateRandomSumOne(vector<ZZ>& rnd){
    rnd.clear();
    rnd.resize(NUMRANDOMIZER);
    
    ZZ sum;

    for(unsigned long i = 0; i < NUMRANDOMIZER - 1; i++){
        RandomBits(rnd[i], RANDOMBITS);
        rnd[i] %= MSGSPACE;
        sum += rnd[i];
    }

    rnd[NUMRANDOMIZER - 1] = 1 - sum;
}
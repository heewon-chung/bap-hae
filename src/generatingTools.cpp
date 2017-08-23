#include "generatingTools.h"

void generateRandomPtxt(vector<HAEPtxt>& ptxt, int num){
    ptxt.clear();
    ptxt.resize(num);
    
    for(unsigned long i = 0; i < num; i++){
        RandomBits(ptxt[i].msg, RANDOMBITS);
        ptxt[i].msg %= MSGSPACE;
        RandomBits(ptxt[i].tag, RANDOMBITS);
        ptxt[i].tag %= TAGSPACE;
    }
}

void generateBinaryMsg(vector<HAEPtxt>& ptxt, int num){
    ptxt.clear();
    ptxt.resize(num);
    
    for(unsigned long i = 0; i < num; i++){
        ptxt[i].msg = rand() % 2;
        RandomBits(ptxt[i].tag, RANDOMBITS);
    }
}

void generateRandomizer(vector<HAEPtxt>& rnd, vector<HAECtxt>& encRnd, const HAESecKey& secretKey){
    rnd.clear();
    rnd.resize(NUMRANDOMIZER);

    #pragma omp parallel for
    for(unsigned long i = 0; i < NUMRANDOMIZER; i++){
        RandomBits(rnd[i].msg, RANDOMBITS);
        rnd[i].msg %= MSGSPACE;
        rnd[i].tag = conv<ZZ>(0);
    }
    encrypt(encRnd, rnd, secretKey);
}

void generateRandomVector(vector<ZZ>& rnd){
    rnd.clear();
    rnd.resize(NUMRANDOMIZER);
    
    ZZ sum;

    for(unsigned long i = 0; i < NUMRANDOMIZER; i++){
        RandomBits(rnd[i], RANDOMBITS);
        rnd[i] %= MSGSPACE;
        sum += rnd[i];
    }
}
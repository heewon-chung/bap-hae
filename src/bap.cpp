#include "bap.h"

void enrollment(vector<HAECtxt>& encIris, const vector<HAEPtxt>& iris, const HAESecKey& secretKey){
    int numCtxt = iris.size();

    encIris.clear();
    encIris.resize(numCtxt);

    encrypt(encIris, iris, secretKey);
}

void requestAuthentication(vector<HAECtxt>& encIris, vector<HAEPtxt>& rnd, vector<HAECtxt>& encRnd, const vector<HAEPtxt>& iris, const HAESecKey& secretKey){
    int numCtxt = iris.size();

    encIris.clear();
    encIris.resize(numCtxt);
    encrypt(encIris, iris, secretKey);

    generateRandomizer(rnd, encRnd, secretKey);
}

void computeHDandMasking(HAECtxt& maskCtxt, ZZ& masking, const vector<HAECtxt>& encIris1, const vector<HAECtxt>& encIris2, const vector<HAEPtxt>& rnd, const vector<HAECtxt>& encRnd, const HAEEvalKey& evalKey){
    assert(encIris1.size() == encIris2.size());
    assert(rnd.size() == encRnd.size());

    vector<ZZ>  svrSecretVector;
    HAECtxt     tmpMasking;
    
    masking = conv<ZZ>(0);

    hammingDistance(maskCtxt, encIris1, encIris2, evalKey);

    generateRandomVector(svrSecretVector);

    #pragma omp parallel for
    for(unsigned long i = 0; i < NUMRANDOMIZER; i++){
        masking += (svrSecretVector[i] * rnd[i].msg);
        tmpMasking += (svrSecretVector[i] * encRnd[i]);
    }
    maskCtxt += tmpMasking;
    maskCtxt %= evalKey;
}

bool checkValidity(const ZZ& masking, const ZZ& decHD){
    int     threshold = NUMBITS * 10 / 3;
    ZZ      recoverHD = decHD - masking;

    if(recoverHD > threshold){
        return false;
    }
    else{
        return true;
    }
}
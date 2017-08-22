#include "matching.h"

long hammingDistance(const vector<HAEPtxt>& ptxt1, const vector<HAEPtxt>& ptxt2){
    assert(ptxt1.size() == ptxt2.size());
    
    unsigned long   numBits = ptxt1.size(),
                    hammingDistance = 0;

    for(unsigned long i = 0; i < numBits; i++){
        if(ptxt1[i].msg != ptxt2[i].msg){
            hammingDistance++;
        }
    }

    return hammingDistance;
}

void hammingDistance(HAECtxt& hdCtxt, const vector<HAECtxt>& ct1, const vector<HAECtxt>& ct2, const HAEEvalKey& evalKey){
    assert(ct1.size() == ct2.size());
    unsigned long ctxtSize = ct1.size();

    hdCtxt = ct1[0];
    hdCtxt -= ct2[0];
    power(hdCtxt, hdCtxt, 2);

    #pragma omp parallel for
    for(unsigned long i = 1; i < ctxtSize; i++){
        HAECtxt tmpCtxt = ct1[i];
        tmpCtxt -= ct2[i];
        power(tmpCtxt, tmpCtxt, 2);
        hdCtxt += tmpCtxt;
    }
    hdCtxt %= evalKey;
}
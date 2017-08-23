#include "hae.h"

void generateSecretKey(HAESecKey& sk){
    GenPrime(sk.msgMod, 200);
    GenPrime(sk.tagMod, 20000);
}

void generateEvalKey(HAEEvalKey& ek, const HAESecKey& sk){
    ek = sk.msgMod;
    ek *= sk.tagMod;
}

void encrypt(HAECtxt& ctxt, const HAEPtxt ptxt, const HAESecKey& sk){
    ZZ          rnd1, rnd2;
    vector<ZZ>  residue, prime;

    RandomBits(rnd1, ERRORBND);
    RandomBits(rnd2, ERRORBND);

    prime.push_back(sk.msgMod);
    prime.push_back(sk.tagMod);

    residue.push_back(rnd1 * MSGSPACE + ptxt.msg);
    residue.push_back(rnd2 * TAGSPACE + ptxt.tag);

    crt(ctxt, prime, residue);
}

void encrypt(vector<HAECtxt>& ctxt, const vector<HAEPtxt>& ptxt, const HAESecKey& sk){
    int         numCtxt = ptxt.size();
    vector<ZZ>  prime;

    ctxt.clear();
    ctxt.resize(numCtxt);

    prime.push_back(sk.msgMod);
    prime.push_back(sk.tagMod);

    #pragma omp parallel for
    for(unsigned long i = 0; i < numCtxt; i++){
        ZZ          rnd1, rnd2;
        vector<ZZ>  residue;
    
        RandomBits(rnd1, ERRORBND);
        RandomBits(rnd2, ERRORBND);

        residue.push_back(rnd1 * MSGSPACE + ptxt[i].msg);
        residue.push_back(rnd2 * TAGSPACE + ptxt[i].tag);
    
        crt(ctxt[i], prime, residue);
    }
}

void decrypt(ZZ& decPtxt, const HAECtxt& ct, const ZZ& tag, const HAESecKey& sk){
    ZZ ctTag = ct % sk.tagMod;
    ctTag %= TAGSPACE;

    assert(ctTag == tag);

    decPtxt = ct % sk.msgMod;
    decPtxt %= MSGSPACE;
}

// Decryption for Hamming Distance
void decryptForHD(int& decPtxt, const HAECtxt& ctxt, const vector<HAEPtxt>& ptxt1, const vector<HAEPtxt>& ptxt2, const HAESecKey& sk){
    assert(ptxt1.size() == ptxt2.size());
    int numBits = ptxt1.size();
    ZZ  tag = conv<ZZ>(0);;

    ZZ ctTag = ctxt % sk.tagMod;
    ctTag %= TAGSPACE;

    for(unsigned long i = 0; i < numBits; i++){
        ZZ tmpTag = ptxt1[i].tag - ptxt2[i].tag;
        tmpTag *= tmpTag;
        tag += tmpTag;
    }

    assert(ctTag == tag);

    ZZ tmpDec = ctxt % sk.msgMod;
    tmpDec %= MSGSPACE;
    decPtxt = conv<int>(tmpDec);
}

// Decryption for Hamming Distance
void decryptForHD(ZZ& decPtxt, const HAECtxt& ctxt, const vector<HAEPtxt>& ptxt1, const vector<HAEPtxt>& ptxt2, const HAESecKey& sk){
    assert(ptxt1.size() == ptxt2.size());
    int numBits = ptxt1.size();
    ZZ  tag = conv<ZZ>(0);

    ZZ ctTag = ctxt % sk.tagMod;
    ctTag %= TAGSPACE;

    for(unsigned long i = 0; i < numBits; i++){
        ZZ tmpTag = ptxt1[i].tag - ptxt2[i].tag;
        tmpTag *= tmpTag;
        tag += tmpTag;
    }
    
    assert(ctTag == tag);

    decPtxt = ctxt % sk.msgMod;
    decPtxt %= MSGSPACE;
}
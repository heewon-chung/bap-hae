#include "hae.h"

void generateSecretKey(HAESecKey& sk){
    GenPrime(sk.msgMod, 300);
    GenPrime(sk.tagMod, 300);
}

void encrypt(Ctxt& ctxt, const int& msg, const int& tag, const HAESecKey& sk){
    ZZ          rnd1, rnd2;
    vector<ZZ>  residue, prime;

    RandomBits(rnd1, ERRORBND);
    RandomBits(rnd2, ERRORBND);

    prime.push_back(sk.msgMod);
    prime.push_back(sk.tagMod);

    residue.push_back(rnd1 * MSGSPACE + msg);
    residue.push_back(rnd2 * TAGSPACE + tag);

    crt(ctxt, prime, residue);
}

void encrypt(vector<Ctxt>& ctxt, const vector<int>& msg, const vector<int>& tag, const HAESecKey& sk){
    assert(msg.size() == tag.size());

    int         numCtxt = msg.size();
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
    
        residue.push_back(rnd1 * MSGSPACE + msg[i]);
        residue.push_back(rnd2 * TAGSPACE + tag[i]);
    
        crt(ctxt[i], prime, residue);
    }
}

void decrypt(int& decPtxt, const Ctxt& ct, const int& tag, const HAESecKey& sk){
    ZZ ctTag = ct % sk.tagMod;
    ctTag %= TAGSPACE;

    assert(ctTag == tag);

    ZZ tmpDec = ct % sk.msgMod;
    tmpDec %= MSGSPACE;
    decPtxt = conv<int>(tmpDec);
}

void decrypt(ZZ& decPtxt, const Ctxt& ct, const int& tag, const HAESecKey& sk){
    ZZ ctTag = ct % sk.tagMod;
    ctTag %= TAGSPACE;

    assert(ctTag == tag);

    decPtxt = ct % sk.msgMod;
    decPtxt %= MSGSPACE;
}

// Decryption for Hamming Distance
void decryptForHD(int& decPtxt, const Ctxt& ct, const vector<int>& tag1, const vector<int>& tag2, const HAESecKey& sk){
    assert(tag1.size() == tag2.size());
    int numTag = tag1.size(),
        tag = 0;

    ZZ ctTag = ct % sk.tagMod;
    ctTag %= TAGSPACE;

    for(unsigned long i = 0; i < numTag; i++){
        int tmpTag = tag1[i] - tag2[i];
        tmpTag *= tmpTag;
        tag += tmpTag;
    }

    assert(ctTag == tag);

    ZZ tmpDec = ct % sk.msgMod;
    tmpDec %= MSGSPACE;
    decPtxt = conv<int>(tmpDec);
}
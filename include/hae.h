#ifndef HAE_H
#define HAE_H

#include <cstdlib>
#include <vector>
#include <cassert>

#include <NTL/ZZ.h>

#include "param.h"
#include "crt.h"

#define HAECtxt     ZZ
#define HAEEvalKey  ZZ

typedef struct {
    ZZ msgMod;      // modulus for message space
    ZZ tagMod;      // modulus for tag space
} HAESecKey; 

typedef struct {
    ZZ msg;        // message for HAE
    ZZ tag;        // tag for HAE
} HAEPtxt;

void generateSecretKey(HAESecKey&);
void generateEvalKey(HAEEvalKey&, const HAESecKey&);

void encrypt(HAECtxt&, const HAEPtxt&, const HAESecKey&);
void encrypt(vector<HAECtxt>&, const vector<HAEPtxt>&, const HAESecKey&);

void decrypt(ZZ&, const HAECtxt&, const ZZ&, const HAESecKey&);
void decryptForHD(int&, const HAECtxt&, const vector<HAEPtxt>&, const vector<HAEPtxt>&, const HAESecKey&);
void decryptForHD(ZZ&, const HAECtxt&, const vector<HAEPtxt>&, const vector<HAEPtxt>&, const HAESecKey&);

#endif
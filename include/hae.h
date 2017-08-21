#ifndef HAE_H
#define HAE_H

#include <cstdlib>
#include <vector>
#include <cassert>

#include <NTL/ZZ.h>

#include "param.h"
#include "crt.h"

#define HAECtxt ZZ

typedef struct {
    ZZ msgMod;      // modulus for message space
    ZZ tagMod;      // modulus for tag space
} HAESecKey; 

typedef struct {
    int msg;        // message for HAE
    int tag;        // tag for HAE
} HAEPtxt;

void generateSecretKey(HAESecKey&);

void encrypt(HAECtxt&, const HAEPtxt&, const HAESecKey&);
void encrypt(vector<HAECtxt>&, const vector<HAEPtxt>&, const HAESecKey&);

void decrypt(int&, const HAECtxt&, const int&, const HAESecKey&);
void decryptForHD(int&, const HAECtxt&, const vector<HAEPtxt>&, const vector<HAEPtxt>&, const HAESecKey&);

#endif
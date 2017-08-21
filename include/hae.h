#ifndef HAE_H
#define HAE_H

#include <cstdlib>
#include <vector>
#include <cassert>

#include <NTL/ZZ.h>

#include "param.h"
#include "crt.h"

#define Ctxt ZZ

typedef struct {
    ZZ msgMod;    // modulus for message space
    ZZ tagMod;    // modulus for tag space
} HAESecKey; 

void generateSecretKey(HAESecKey&);

void encrypt(Ctxt&, const int&, const int&, const HAESecKey&);
void encrypt(vector<Ctxt>&, const vector<int>&, const vector<int>&, const HAESecKey&);

void decrypt(int&, const Ctxt&, const int&, const HAESecKey&);
void decrypt(ZZ&, const Ctxt&, const int&, const HAESecKey&);
void decryptForHD(int&, const Ctxt&, const vector<int>&, const vector<int>&, const HAESecKey&);

#endif
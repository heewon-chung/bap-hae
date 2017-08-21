#ifndef CRT_H
#define CRT_H

#include <cstdlib>
#include <cassert>
#include <vector>

#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

void crt(ZZ&, const vector<ZZ>&, const vector<ZZ>&);

#endif
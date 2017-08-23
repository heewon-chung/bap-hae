#ifndef PARAM_H
#define PARAM_H

#include <NTL/ZZ.h>

using namespace NTL;

const long  NUMBITS = 2048;
const long  SECURITY = 80;
const long  ERRORBND = 2 * SECURITY;
const long  RANDOMBITS = 40;
const long  NUMRANDOMIZER = 100;

const ZZ    MSGSPACE = conv<ZZ>(1) << 2 * SECURITY;
const ZZ    TAGSPACE = conv<ZZ>(1) << 2 * SECURITY;

#endif
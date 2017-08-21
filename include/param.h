#ifndef PARAM_H
#define PARAM_H

#include <NTL/ZZ.h>

using namespace NTL;

const long SECURITY = 20;
const long ERRORBND = 5;
const long RANDOMBITS = SECURITY;

const ZZ MSGSPACE = conv<ZZ>((1 << SECURITY));
const ZZ TAGSPACE = conv<ZZ>((1 << SECURITY));

const long NUMRANDOMIZER = 10;

#endif
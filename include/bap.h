#ifndef BAP_H
#define BAP_H

#include <cstdlib>
#include <vector>

#include <NTL/ZZ.h>

#include "param.h"
#include "generatingTools.h"
#include "hae.h"
#include "matching.h"

void enrollment(vector<HAECtxt>&, const vector<HAEPtxt>&, const HAESecKey&);
void requestAuthentication(vector<HAECtxt>&, vector<HAEPtxt>&, vector<HAECtxt>&, const vector<HAEPtxt>&, const HAESecKey&);
void computeHDandMasking(HAECtxt&, ZZ&, const vector<HAECtxt>&, const vector<HAECtxt>&, const vector<HAEPtxt>&, const vector<HAECtxt>&, const HAEEvalKey&);
bool checkValidity(const ZZ&, const ZZ&);

#endif
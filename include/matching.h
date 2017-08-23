#ifndef MATCHING_H
#define MATCHING_H

#include <cstdlib>
#include <cassert>
#include <vector>

#include "hae.h"

long hammingDistance(const vector<HAEPtxt>&, const vector<HAEPtxt>&);
void hammingDistance(HAECtxt&, const vector<HAECtxt>&, const vector<HAECtxt>&, const HAEEvalKey&);

#endif
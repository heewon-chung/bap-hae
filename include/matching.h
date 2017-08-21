#ifndef MATCHING_H
#define MATCHING_H

#include <cstdlib>
#include <cassert>
#include <vector>

#include "hae.h"

long hammingDistance(const vector<int>&, const vector<int>&);
void hammingDistance(Ctxt&, const vector<Ctxt>&, const vector<Ctxt>&);

#endif
#include <cstdlib>
#include <vector>
#include <iostream>

#include "param.h"
#include "hae.h"

using namespace std;

void generateRandomPtxt(vector<HAEPtxt>&, int);
void generateBinaryMsg(vector<HAEPtxt>&, int);
void generateRandomSumOne(vector<ZZ>&);
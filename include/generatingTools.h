#include <cstdlib>
#include <vector>
#include <iostream>

#include "param.h"
#include "hae.h"

using namespace std;

void generateRandomPtxt(vector<HAEPtxt>&, int);
void generateBinaryMsg(vector<HAEPtxt>&, int);
void generateRandomizer(vector<HAEPtxt>&, vector<HAECtxt>&, const HAESecKey&);
void generateRandomVector(vector<ZZ>&);
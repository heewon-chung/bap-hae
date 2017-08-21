#include <cstdlib>
#include <vector>

#include <NTL/ZZ.h>

#include "param.h"
#include "bapTools.h"
#include "hae.h"
#include "timeUtils.h"

#define NUMTEST 10

using namespace std;
using namespace NTL;

int main(void){
    srand(time(NULL));
    SetSeed(conv<ZZ>(time(NULL)));

    cout << "\nHomomorphic Authentication Encryption Test Started...\n";
    HAESecKey secretKey;
    // Secret Key Generation
    cout << "Generating Secret Key...\n";
    generateSecretKey(secretKey);
    
    // Variable for HAE
    vector<HAEPtxt>     ptxt;
    vector<HAECtxt>     ctxt;
    vector<ZZ>          origMsg, decMsg(NUMTEST);
    TIMER               start, end;
    
    // Message Generation
    cout << "Generating Messages...\n";
    generateRandomPtxt(ptxt, NUMTEST);
    
    // encryption 
    cout << "Encrypting...";
    start = TIC;
    encrypt(ctxt, ptxt, secretKey);
    end = TOC;
    cout << get_time_us(start, end, NUMTEST) << "sec\n";

    // decryption
    cout << "Decrypting...";
    start = TIC;
    for(unsigned long i = 0; i < NUMTEST; i++){
        decrypt(decMsg[i], ctxt[i], ptxt[i].tag, secretKey);
    }
    end = TOC;
    cout << get_time_us(start, end, NUMTEST) << "sec\n\n";


    for(unsigned long i = 0; i < NUMTEST; i++){
        origMsg.push_back(ptxt[i].msg);
    }
    assert(origMsg == decMsg);
}
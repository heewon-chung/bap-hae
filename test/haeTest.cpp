#include <cstdlib>
#include <vector>

#include <NTL/ZZ.h>

#include "param.h"
#include "generalTools.h"
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
    generateSecretKey(secretKey);

    // Variable for HAE
    vector<int>     msg, tag;
    vector<Ctxt>    ctxt;
    vector<int>     decPtxt(NUMTEST);
    TIMER           start, end;
    
    // Message Generation
    cout << "Generating Secret Key...\n";
    generateMsgAndTag(msg, tag, NUMTEST);
    
    // encryption 
    cout << "Encrypting...\n";
    start = TIC;
    encrypt(ctxt, msg, tag, secretKey);
    end = TOC;
    cout << get_time_us(start, end, NUMTEST) << "sec\n";

    // decryption
    cout << "Decrypting...\n";
    start = TIC;
    for(unsigned long i = 0; i < NUMTEST; i++){
        decrypt(decPtxt[i], ctxt[i], tag[i], secretKey);
    }
    end = TOC;
    cout << get_time_us(start, end, NUMTEST) << "sec\n\n";

    assert(msg == decPtxt);
}
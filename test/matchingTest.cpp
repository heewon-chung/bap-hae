#include <cstdlib>
#include <vector>

#include <NTL/ZZ.h>

#include "param.h"
#include "generalTools.h"
#include "hae.h"
#include "matching.h"
#include "timeUtils.h"

#define NUMBITS 100

using namespace std;
using namespace NTL;

int main(void){
    srand(time(NULL));
    SetSeed(conv<ZZ>(time(NULL)));

    cout << "\nMatching Test Started...\n";
    HAESecKey secretKey;
    // Secret Key Generation
    generateSecretKey(secretKey);

    // Variable for HAE
    vector<int>     msg1, tag1, msg2, tag2;
    vector<Ctxt>    ctxt1, ctxt2;
    Ctxt            hdCtxt;
    int             decHD;
    TIMER           start, end;
    
    // Message Generation
    cout << "Generating Secret Key...\n";
    generateBinaryMsgAndTag(msg1, tag1, NUMBITS);
    generateBinaryMsgAndTag(msg2, tag2, NUMBITS);
    
    long ptxtHD = hammingDistance(msg1, msg2);

    // encryption 
    cout << "Encrypting...";
    start = TIC;
    encrypt(ctxt1, msg1, tag1, secretKey);
    encrypt(ctxt2, msg2, tag2, secretKey);
    end = TOC;
    cout << get_time_us(start, end, 2 * NUMBITS) << "sec\n";

    // compute hamming distance
    cout << "Computing Hamming Distance...";
    start = TIC;
    hammingDistance(hdCtxt, ctxt1, ctxt2);
    end = TOC;
    cout << get_time_us(start, end, 1) << "sec\n";

    // decryption
    cout << "Decrypting...";
    start = TIC;
    decryptForHD(decHD, hdCtxt, tag1, tag2, secretKey);
    end = TOC;
    cout << get_time_us(start, end, NUMBITS) << "sec\n\n";

    cout << "Hamming Distance (plaintext): " << ptxtHD << endl;
    cout << "Hamming Distance (ciphertext): " << decHD << endl;
    assert(ptxtHD == decHD);
}
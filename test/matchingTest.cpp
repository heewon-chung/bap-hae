#include <cstdlib>
#include <vector>

#include <NTL/ZZ.h>

#include "param.h"
#include "generatingTools.h"
#include "hae.h"
#include "matching.h"
#include "timeUtils.h"

#define NUMBITS 2000

using namespace std;
using namespace NTL;

int main(void){
    srand(time(NULL));
    SetSeed(conv<ZZ>(time(NULL)));

    cout << "\nMatching Test Started...\n";
    cout << "Genereting Secret Key...\n";
    HAESecKey secretKey;
    // Secret Key Generation
    generateSecretKey(secretKey);

    cout << "Generating Evaluation Key...\n";
    HAEEvalKey evalKey;
    generateEvalKey(evalKey, secretKey);

    // Variable for HAE
    vector<HAEPtxt>     ptxt1, ptxt2;
    vector<HAECtxt>     ctxt1, ctxt2;
    HAECtxt             hdCtxt;
    int                 decHD;
    TIMER               start, end;
    
    // Message Generation
    cout << "Generating Binary Messages...\n";
    generateBinaryMsg(ptxt1, NUMBITS);
    generateBinaryMsg(ptxt2, NUMBITS);
    
    long ptxtHD = hammingDistance(ptxt1, ptxt2);

    // encryption
    cout << "Encrypting...";
    start = TIC;
    encrypt(ctxt1, ptxt1, secretKey);
    encrypt(ctxt2, ptxt2, secretKey);
    end = TOC;
    cout << get_time_us(start, end, 2 * NUMBITS) << " ms\n";

    // compute hamming distance
    cout << "Computing Hamming Distance...";
    start = TIC;
    hammingDistance(hdCtxt, ctxt1, ctxt2, evalKey);
    end = TOC;
    cout << get_time_us(start, end, 1) << " ms\n";

    // decryption
    cout << "Decrypting...";
    start = TIC;
    decryptForHD(decHD, hdCtxt, ptxt1, ptxt2, secretKey);
    end = TOC;
    cout << get_time_us(start, end, NUMBITS) << " ms\n\n";

    cout << "Hamming Distance (plaintext): " << ptxtHD << endl;
    cout << "Hamming Distance (ciphertext): " << decHD << endl;
    
    assert(ptxtHD == decHD);
}
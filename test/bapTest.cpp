#include <cstdlib>
#include <vector>

#include <NTL/ZZ.h>

#include "param.h"
#include "bapTools.h"
#include "hae.h"
#include "bap.h"
#include "timeUtils.h"

#define NUMBITS 400

using namespace std;
using namespace NTL;

int main(void){
    srand(time(NULL));
    SetSeed(conv<ZZ>(time(NULL)));

    cout << "\nMatching Test Started...\n";
    HAESecKey secretKey;
    // Secret Key Generation
    generateSecretKey(secretKey);

    // Variable for Biometric Authentication Protocol
    vector<HAEPtxt>     iris1, iris2, rnd;
    vector<HAECtxt>     encIris1, encIris2, encRnd;
    ZZ                  masking;
    HAECtxt             maskCtxt;
    TIMER               start, end;
    
    // Message Generation
    cout << "Generating Secret Key...\n";
    generateBinaryMsg(iris1, NUMBITS);
    generateBinaryMsg(iris2, NUMBITS);
    
    long ptxtHD = hammingDistance(iris1, iris2);

    cout << "\nClient: \tEncrypting Iris for Enrollment...";
    start = TIC;
    enrollment(encIris1, iris1, secretKey);
    end = TOC;
    cout << get_time_us(start, end, 1) << "sec\n";

    cout << "Client: \tEncrypting Iris for Authentication...";
    start = TIC;
    requestAuthentication(encIris2, rnd, encRnd, iris2, secretKey);
    end = TOC;
    cout << get_time_us(start, end, 1) << "sec\n";

    cout << "Server: \tComputing Hamming Distance and Masking Ctxt...";
    start = TIC;
    computeHDandMasking(maskCtxt, masking, encIris1, encIris2, rnd, encRnd);
    end = TOC;
    cout << get_time_us(start, end, 1) << "sec\n";

    // cout << "Client: \tDecrypting...";
    // start = TIC;

    // end = TOC;
    // cout << get_time_us(start, end, 1) << "sec\n";

    // cout << "Server: \tChecking Validity of the Client...";
    // start = TIC;

    // end = TOC;
    // cout << get_time_us(start, end, 1) << "sec\n";

}
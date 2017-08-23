#include <cstdlib>
#include <vector>

#include <NTL/ZZ.h>

#include "param.h"
#include "generatingTools.h"
#include "hae.h"
#include "bap.h"
#include "timeUtils.h"

using namespace std;
using namespace NTL;

int main(void){
    srand(time(NULL));
    SetSeed(conv<ZZ>(time(NULL)));

    cerr << "\nBiometric Authentication Protocl Test Started...\n";
    // Secret Key Generation
    cerr << "Generating Secret Key...\n";
    HAESecKey secretKey;
    generateSecretKey(secretKey);

    cerr << "Generating Evaluation Key...\n";
    HAEEvalKey evalKey;
    generateEvalKey(evalKey, secretKey);

    // Variable for Biometric Authentication Protocol
    vector<HAEPtxt>     iris1, iris2, rnd;
    vector<HAECtxt>     encIris1, encIris2, encRnd;
    ZZ                  masking, decHD;
    HAECtxt             maskCtxt;
    TIMER               start, end;
    
    // Message Generation
    cerr << "Generating Binary Messages...\n";
    generateBinaryMsg(iris1, NUMBITS);
    generateBinaryMsg(iris2, NUMBITS);
    
    long ptxtHD = hammingDistance(iris1, iris2);

    cerr << "\nClient: \tEncrypting Iris for Enrollment... ";
    start = TIC;
    enrollment(encIris1, iris1, secretKey);
    end = TOC;
    cerr << get_time_us(start, end, 1) << " ms\n";

    cerr << "Client: \tEncrypting Iris for Authentication... ";
    start = TIC;
    requestAuthentication(encIris2, rnd, encRnd, iris2, secretKey);
    end = TOC;
    cerr << get_time_us(start, end, 1) << " ms\n";

    cerr << "Server: \tComputing Hamming Distance and Masking Ctxt... ";
    start = TIC;
    computeHDandMasking(maskCtxt, masking, encIris1, encIris2, rnd, encRnd, evalKey);
    end = TOC;
    cerr << get_time_us(start, end, 1) << " ms\n";

    cerr << "Client: \tDecrypting... ";
    start = TIC;
    decryptForHD(decHD, maskCtxt, iris1, iris2, secretKey);
    end = TOC;
    cerr << get_time_us(start, end, 1) << " ms\n";

    cerr << "Server: \tChecking Validity of the Client... ";
    start = TIC;
    bool result = checkValidity(masking, decHD);
    end = TOC;
    cerr << get_time_us(start, end, 1) << " ms\n\n";

    cerr << "Original Hamming Distance (plaintext): " << ptxtHD << endl;
    cerr << "Recover Hamming Distance (ciphertext): " << decHD - masking << endl;
    cerr << "Biometric Authentication Protocol Result : " << result << endl;
}
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

    cout << "\nBiometric Authentication Protocl Test Started...\n";
    // Secret Key Generation
    cout << "Generating Secret Key...\n";
    HAESecKey secretKey;
    generateSecretKey(secretKey);

    cout << "Generating Evaluation Key...\n";
    HAEEvalKey evalKey;
    generateEvalKey(evalKey, secretKey);

    // Variable for Biometric Authentication Protocol
    vector<HAEPtxt>     iris1, iris2, rnd;
    vector<HAECtxt>     encIris1, encIris2, encRnd;
    ZZ                  masking, decHD;
    HAECtxt             maskCtxt;
    TIMER               start, end;
    
    // Message Generation
    cout << "Generating Binary Messages...\n";
    generateBinaryMsg(iris1, NUMBITS);
    generateBinaryMsg(iris2, NUMBITS);
    
    long ptxtHD = hammingDistance(iris1, iris2);

    cout << "\nClient: \tEncrypting Iris for Enrollment... ";
    start = TIC;
    enrollment(encIris1, iris1, secretKey);
    end = TOC;
    cout << get_time_us(start, end, 1) << " ms\n";

    cout << "Client: \tEncrypting Iris for Authentication... ";
    start = TIC;
    requestAuthentication(encIris2, rnd, encRnd, iris2, secretKey);
    end = TOC;
    cout << get_time_us(start, end, 1) << " ms\n";

    cout << "Server: \tComputing Hamming Distance and Masking Ctxt... ";
    start = TIC;
    computeHDandMasking(maskCtxt, masking, encIris1, encIris2, rnd, encRnd, evalKey);
    end = TOC;
    cout << get_time_us(start, end, 1) << " ms\n";

    cout << "Client: \tDecrypting... ";
    start = TIC;
    decryptForHD(decHD, maskCtxt, iris1, iris2, secretKey);
    end = TOC;
    cout << get_time_us(start, end, 1) << " ms\n";

    cout << "Server: \tChecking Validity of the Client... ";
    start = TIC;
    bool result = checkValidity(masking, decHD);
    end = TOC;
    cout << get_time_us(start, end, 1) << " ms\n\n";

    cout << "Original Hamming Distance (plaintext): " << ptxtHD << endl;
    cout << "Recover Hamming Distance (ciphertext): " << decHD - masking << endl;
    cout << "Biometric Authentication Protocol Result : " << result << endl;
}
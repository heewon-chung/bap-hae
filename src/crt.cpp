#include "crt.h"

void crt(ZZ& result, const vector<ZZ>& prime, const vector<ZZ>& residue){
    assert(prime.size() == residue.size());

    ZZ productPrime = prime[0] * prime[1];
    
    if(prime[0] < prime[1]){
        ZZ tmp = prime[1] % prime[0];
        result = residue[0] * prime[1] * InvMod(tmp, prime[0]);
        result += residue[1] * prime[0] * InvMod(prime[0], prime[1]);    
    }
    else{
        ZZ tmp = prime[0] % prime[1];
        result = residue[0] * prime[1] * InvMod(prime[1], prime[0]);
        result += residue[1] * prime[0] * InvMod(tmp, prime[1]);
    }

    result %= productPrime;
}
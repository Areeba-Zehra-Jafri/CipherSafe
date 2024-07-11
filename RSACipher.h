#ifndef RSACIPHER_H
#define RSACIPHER_H

#include <string>
#include <utility>
#include <vector>
#include "Cryptography.h"
using namespace std;

class RSA : public Cryptography
{
public:
    RSA(const string &plaintext, const string &ciphertext, long long p, long long q, long long e);
    pair<long long, long long> getPublicKey();
    pair<long long, long long> getPrivateKey();
    string get_plaintext();
    string get_ciphertext();
    string encrypt();
    string decrypt();
    void set_plaintext(const string &p);
    void set_ciphertext(const string &c);

private:
    long long p, q, e, n, phi, d;
    string plaintext;
    string ciphertext;
    long long generatePrime();
    long long gcd(long long a, long long b);
    long long modInverse(long long a, long long m);
    long long modExp(long long base, long long exp, long long mod);
    vector<long long> stringToInt(const string &str);
    string intToString(const vector<long long> &nums);
};

#endif

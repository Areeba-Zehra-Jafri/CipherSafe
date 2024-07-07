#ifndef AFFINECIPHER_H
#define AFFINECIPHER_H

#include "Cryptography.h"
#include <string>
#include <iostream>

using namespace std;

class AffineCipher : public Cryptography {
public:
    AffineCipher(const string& plain_text, const string& cipher_text, int a, int b);
    string get_ciphertext();
    string get_plaintext();
    string encrypt() ;
    string decrypt() ;
    void set_plaintext(const string& p);
    void set_ciphertext(const string& c);

private:
    int a, b;
    static int m;
    int modInverse(int a, int m);
};

#endif // AFFINECIPHER_H

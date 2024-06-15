#ifndef AFFINECIPHER_H
#define AFFINECIPHER_H

#include "Cryptography.h"
#include <string>
#include <iostream>

using namespace std;

class AffineCipher : public Cryptography {
public:
    AffineCipher(string plain_text, string cipher_text, int a, int b);
    string get_cipher();
    string get_decrypt();
    string encrypt() override;
    string decrypt() override;

private:
    int a, b;
    static int m;
    int modInverse(int a, int m);
};

#endif // AFFINECIPHER_H

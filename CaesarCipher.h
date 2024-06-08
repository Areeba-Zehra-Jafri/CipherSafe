#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

#include "Cryptography.h"

class CaesarCipher:protected Cryptography
{
private:
    int shift;

public:
    CaesarCipher(string p,string c,int s);
    string encrypt() override;
    string decrypt() override;
    ~CaesarCipher();
};

#endif 
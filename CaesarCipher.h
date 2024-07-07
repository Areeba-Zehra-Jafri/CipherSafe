#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

#include "Cryptography.h"

class CaesarCipher:public Cryptography
{
private:
    int shift;

public:
    CaesarCipher(const string& p,const string& c,int s);
    string get_ciphertext();
    string get_plaintext();
    string encrypt() ;
    string decrypt() ;
    void set_plaintext(const string& p);
    void set_ciphertext(const string& c);
    ~CaesarCipher();
};

#endif 
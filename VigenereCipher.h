
#ifndef VIGENERECIPHER_H
#define VIGENERECIPHER_H

#include "Cryptography.h"

class VigenereCipher : public Cryptography
{
private:
    string key;

public:
    VigenereCipher(const string& p,const string& c,const string& k);
    string get_ciphertext();
    string get_plaintext();
    string encrypt() override;
    string decrypt() override;
    void set_key(const string& k);
    void set_plaintext(const string& p);
    void set_ciphertext(const string& c);
};

#endif

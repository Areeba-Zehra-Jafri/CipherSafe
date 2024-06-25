#ifndef VERNAMCIPHER_H
#define VERNAMCIPHER_H

#include "Cryptography.h"
#include <string>
#include <vector>

using namespace std;

class VernamCipher:public Cryptography {
private:
    string key;
public:
    VernamCipher(const string& p,const string& c,string key);
    string get_plain_text();
    string get_cipher();
    string encrypt();
    string decrypt();
    void set_plaintext(const string& p);
    void set_ciphertext(const string& p);
};

#endif

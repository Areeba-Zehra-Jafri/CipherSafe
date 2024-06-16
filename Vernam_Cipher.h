#ifndef VERNAMCIPHER_H
#define VERNAMCIPHER_H

#include "Cryptography.h"
#include <string>
#include <vector>

using namespace std;

class VernamCipher:public Cryptography {
public:
    VernamCipher(string plain_text,string key);
    string get_plain_text();
    string get_cipher();
    string encrypt();
    string decrypt();

private:
    string key;
  

};

#endif

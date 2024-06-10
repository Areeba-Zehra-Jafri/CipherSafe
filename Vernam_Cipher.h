#ifndef VERNAMCIPHER_H
#define VERNAMCIPHER_H

#include "Cryptography.h"
#include <string>
#include <vector>

using namespace std;

class VernamCipher:public Cryptography {
public:
    VernamCipher(string plain_text,string cipher_text,string key);
    string get_plain_text();
    string get_cipher();
    string get_decrypt();
    string get_key();

    string encrypt();
    string decrypt();

private:
   // string plaintext;
    //string ciphertext;
    string key;
    char matrix[26];

    int matrixValue(char c);
    vector<int> toBinary(int value);
    int toDecimal(const vector<int>& binary);
    vector<int> xorBinary(const vector<int>& bin1, const vector<int>& bin2);
};

#endif

#ifndef HILLCIPHER_H
#define HILLCIPHER_H

#include "Cryptography.h"

class HillCipher : public Cryptography
{
private:
    vector<vector<int>> keyMatrix;
    vector<vector<int>> inverseKeyMatrix;
    int modInverse(int a, int m);
    void generateKeyMatrix(const string& key);
    void generateInverseKeyMatrix();

public:
    HillCipher(const string& p, const string& c, const string& key);
    string encrypt() ;
    string decrypt() ;
    void set_plaintext(const string& p);
    void set_ciphertext(const string& c);
    ~HillCipher();
};

#endif 

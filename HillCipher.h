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
    HillCipher(string p, string c, const string& key);
    string encrypt() override;
    string decrypt() override;
    ~HillCipher();
};

#endif 

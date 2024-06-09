#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include <iostream>
#include <string>
#include<vector>
using namespace std;

class Cryptography
{
protected:
    string plaintext;
    string ciphertext;

public:
    Cryptography(string p,string c);
    virtual string encrypt() = 0;
    virtual string decrypt() = 0;
    virtual ~Cryptography();
};

#endif 
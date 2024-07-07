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
    Cryptography(const string& p = "", const string& c = "");
    virtual string encrypt() = 0;
    virtual string decrypt() = 0;
    virtual void set_plaintext(const string& p);
    virtual void set_ciphertext(const string& c);
    virtual string get_ciphertext();
    virtual string get_plaintext();
    virtual ~Cryptography();
};

#endif 
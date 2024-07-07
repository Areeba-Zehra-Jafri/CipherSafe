#ifndef RAILFENCE_H
#define RAILFENCE_H
#include <iostream>
#include "Cryptography.h"
#include <string>
#include <vector>

class RailFenceCipher : public Cryptography
{
private:
    int key;

public:
    // Constructor
    RailFenceCipher(const string &p, const string &c, int railKey);
    string get_ciphertext();
    string get_plaintext();
    string encrypt();
    string decrypt();
    void set_plaintext(const string &p);
    void set_ciphertext(const string &c);
};

#endif

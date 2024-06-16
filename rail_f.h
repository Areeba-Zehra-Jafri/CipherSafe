#ifndef RAILFENCE_H
#define RAILFENCE_H
#include <iostream>
#include "Cryptography.h"
#include <string>
#include <vector>

class RailFenceCipher: public Cryptography {
private:
    // std::string plaintext;
    // std::string ciphertext;
    int key;

public:
    // Constructor
    RailFenceCipher(const std::string& p,string& c, int railKey)  ;

    std::string encrypt() ;
    std::string decrypt() ;

};

#endif

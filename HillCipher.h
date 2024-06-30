#ifndef HILLCIPHER_H
#define HILLCIPHER_H

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "Cryptography.h"

using namespace std;

class HillCipher:public Cryptography {
private:
    vector<vector<int>> keyMatrix;
    vector<vector<int>> inverseKeyMatrix;
    int determinant(int a, int b, int c, int d);
     int modInverse(int a, int m);
    void generateKeyMatrix();
     void generateInverseKeyMatrix();

    string key;

public:
     HillCipher(const string& c, const string& p, const string& k);
    string encrypt();
    string decrypt();
    void set_plaintext(const string& p);
    void set_ciphertext(const string& c);
};

#endif // HILLCIPHER_H

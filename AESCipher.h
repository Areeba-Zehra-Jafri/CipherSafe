#ifndef AESCIPHER_H
#define AESCIPHER_H

#include <string>
#include <vector>
#include "Cryptography.h"

class AES : public Cryptography
{
private:
    vector<vector<int>> key;
    void padPlaintext();
    uint8_t gmul(uint8_t a, uint8_t b);
    uint8_t gmul_02(uint8_t x);
    uint8_t gmul_03(uint8_t x);
    uint8_t gmul_09(uint8_t x);
    uint8_t gmul_0b(uint8_t x);
    uint8_t gmul_0d(uint8_t x);
    uint8_t gmul_0e(uint8_t x);
    vector<uint8_t> keyExpansion(const vector<vector<int>> &key);
    void subBytes(vector<uint8_t> &state);
    void shiftRows(vector<uint8_t> &state);
    void mixColumns(vector<uint8_t> &state);
    void addRoundKey(vector<uint8_t> &state, const vector<uint8_t> &roundKey);
    void invSubBytes(vector<uint8_t> &state);
    void invShiftRows(vector<uint8_t> &state);
    void invMixColumns(vector<uint8_t> &state);

public:
    AES(const string &p, const string &c, const vector<vector<int>> &k);
    string get_plaintext();
    string get_ciphertext();
    string encrypt();
    string decrypt();
    void set_plaintext(const string &p);
    void set_ciphertext(const string &c);
};

#endif

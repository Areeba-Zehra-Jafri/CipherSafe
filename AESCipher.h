#ifndef AESCIPHER_H
#define AESCIPHER_H

#include <string>
#include <vector>
#include "Cryptography.h"

class AES : public Cryptography
{
private:
    std::vector<std::vector<int>> key;
    void padPlaintext();
    uint8_t gmul(uint8_t a, uint8_t b);
    uint8_t gmul_02(uint8_t x);
    uint8_t gmul_03(uint8_t x);
    uint8_t gmul_09(uint8_t x);
    uint8_t gmul_0b(uint8_t x);
    uint8_t gmul_0d(uint8_t x);
    uint8_t gmul_0e(uint8_t x);
    std::vector<uint8_t> keyExpansion(const std::vector<std::vector<int>>& key);
    void subBytes(std::vector<uint8_t>& state);
    void shiftRows(std::vector<uint8_t>& state);
    void mixColumns(std::vector<uint8_t>& state);
    void addRoundKey(std::vector<uint8_t>& state, const std::vector<uint8_t>& roundKey);
    void invSubBytes(std::vector<uint8_t>& state);
    void invShiftRows(std::vector<uint8_t>& state);
    void invMixColumns(std::vector<uint8_t>& state);

public:
    AES(std::string p, std::string c, const std::vector<std::vector<int>>& k);
    std::string encrypt() override;
    std::string decrypt() override;
};

#endif



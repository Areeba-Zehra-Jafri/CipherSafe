#ifndef CIPHERINPUT_H
#define CIPHERINPUT_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <cctype>
#include <unordered_set>

class CipherInput {
public:
    static int getAffineCipherKey();
    static int getCaesarCipherKey();
    static std::string getHillCipherKey();
    static int getRailFenceCipherKey();
    static std::vector<long long> getRSACipherKey();
    static std::string getVernamCipherKey();
    static std::string getVigenereCipherKey();
    static std::vector<std::vector<int>> getAESCipherKey();
    static std::string getMonoalphabeticCipherKey();

private:
    static int gcd(int a, int b);
    static bool isPrime(long long n);
};

#endif // CIPHERINPUT_H

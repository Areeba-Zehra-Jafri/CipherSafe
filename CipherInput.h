#ifndef CIPHERINPUT_H
#define CIPHERINPUT_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <cctype>
#include <unordered_set>

using namespace std;

class CipherInput
{
public:
    static int getAffineCipherKey();
    static int getCaesarCipherKey();
    static std::string getHillCipherKey();
    static int getRailFenceCipherKey();
    static vector<long long> getRSACipherKey();
    static string getVigenereCipherKey();
    static vector<vector<int>> getAESCipherKey();
    static string getMonoalphabeticCipherKey();
    static string getVernamCipherKey();

private:
    static int gcd(int a, int b);
    static bool isPrime(long long n);
};

#endif // CIPHERINPUT_H

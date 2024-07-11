#ifndef MONOALPHABETIC_H
#define MONOALPHABETIC_H

#include "Cryptography.h"
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <unordered_set>

using namespace std;

class monoalphabetic : public Cryptography
{

private:
    string key;
    const string sets = "abcdefghijklmnopqrstuvwxyz"; // Character set
    unordered_map<char, char> cipher;
    unordered_map<char, char> decipher;
    void createCipherAlphabet();

public:
    monoalphabetic(const string &p, const string &c, const string &k);
    string get_ciphertext();
    string get_plaintext();
    string encrypt();
    string decrypt();
    void set_plaintext(const string &p);
    void set_ciphertext(const string &c);
};

#endif // MONOALPHABETIC_H

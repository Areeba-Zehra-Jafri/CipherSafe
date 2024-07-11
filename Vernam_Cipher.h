#ifndef VERNAMCIPHER_H
#define VERNAMCIPHER_H

#include "Cryptography.h"
#include <string>
#include <vector>

using namespace std;

class VernamCipher : public Cryptography
{
private:
    string key;
    void generateKey(size_t length); // Function to generate a random key

public:
    VernamCipher(const string &p, const string &c, const string &k); // Default parameter for key
    string get_plaintext();
    string get_ciphertext();
    string encrypt();
    string decrypt();
    void set_plaintext(const string &p);
    void set_ciphertext(const string &p);
    void set_key(const string &k);
};

#endif // VERNAMCIPHER_H

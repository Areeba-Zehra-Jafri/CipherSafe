#include <iostream>
#include <string>
#include <stdexcept>
#include "Vernam_Cipher.h"
using namespace std;

VernamCipher::VernamCipher(const string plaintext, const string k) : Cryptography(plaintext, ""), key(k) {}

string VernamCipher::encrypt()
{

    if (plaintext.length() != key.length())
    {
        throw std::invalid_argument("Key must be the same length as plaintext.");
    }
    std::string ciphertext;
    for (size_t i = 0; i < plaintext.length(); ++i)
    {
        ciphertext += (plaintext[i] ^ key[i]);
    }
    this->ciphertext=ciphertext;
    return ciphertext;
}

// Decryption function
string VernamCipher:: decrypt()
{
    if (ciphertext.length() != key.length())
    {
        throw std::invalid_argument("Key must be the same length as ciphertext.");
    }
    std::string plaintext;
    for (size_t i = 0; i < ciphertext.length(); ++i)
    {
        plaintext += ciphertext[i] ^ key[i];
    }
    return plaintext;
}

string VernamCipher:: get_plain_text()
{
    return plaintext;
}

string VernamCipher:: get_cipher()
{
    return ciphertext;
}
#include <iostream>
#include <string>
#include <stdexcept>
#include "Vernam_Cipher.h"

using namespace std;

VernamCipher::VernamCipher(const string& plaintext, const string& ciphertext, const string k)
    : Cryptography(plaintext, ciphertext), key(k) {}

string VernamCipher::encrypt()
{
    try {
        if (plaintext.length() != key.length())
        {
            throw invalid_argument("Key must be the same length as plaintext.");
        }

        string ciphertext;
        for (size_t i = 0; i < plaintext.length(); ++i)
        {
            char encrypted_char = ((plaintext[i] - 'A') ^ (key[i] - 'A')) + 'A'; // Map to A-Z
            ciphertext += encrypted_char;
        }
        this->ciphertext = ciphertext;
        return ciphertext;

    } catch (const exception& e) {
        cerr << "Encryption error: " << e.what() << endl;
        throw; // Re-throw the exception to propagate it further if needed
    }
}

string VernamCipher::decrypt()
{
    try {
        if (ciphertext.length() != key.length())
        {
            throw invalid_argument("Key must be the same length as ciphertext.");
        }

        string plaintext;
        for (size_t i = 0; i < ciphertext.length(); ++i)
        {
            char decrypted_char = ((ciphertext[i] - 'A') ^ (key[i] - 'A')) + 'A'; // Reverse the mapping
            plaintext += decrypted_char;
        }
        this->plaintext = plaintext;
        return plaintext;

    } catch (const exception& e) {
        std::cerr << "Decryption error: " << e.what() << endl;
        throw; // Re-throw the exception to propagate it further if needed
    }
}

string VernamCipher::get_plain_text()
{
    return plaintext;
}

string VernamCipher::get_cipher()
{
    return ciphertext;
}

void VernamCipher::set_plaintext(const string& p)
{
    plaintext = p;
}

void VernamCipher::set_ciphertext(const string& c)
{
    ciphertext = c;
}

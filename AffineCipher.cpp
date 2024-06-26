#include "AffineCipher.h"
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <iostream>

using namespace std;

int AffineCipher::m = 26;

AffineCipher::AffineCipher(const string& plain_text, const string& cipher_text, int a, int b) : Cryptography(plain_text, cipher_text), a(a), b(b)
{
    try
    {
        if (__gcd(a, m) != 1)
        {
            throw invalid_argument("a and m must be coprime.");
        }
    }
    catch (const invalid_argument& e)
    {
        cerr << e.what() << endl;
        throw; 
    }
}

int AffineCipher::modInverse(int a, int m)
{
    a = a % m;
    for (int x = 1; x < m; x++)
    {
        if ((a * x) % m == 1)
        {
            return x;
        }
    }
    throw invalid_argument("Multiplicative inverse does not exist.");
}

string AffineCipher::get_cipher()
{
    return ciphertext;
}

string AffineCipher::get_decrypt()
{
    return plaintext;
}

string AffineCipher::encrypt()
{
    try
    {
        int n = plaintext.size();
        if (n == 0) 
        {
            throw runtime_error("Plaintext cannot be empty.");
        }

        string cipher_text;
        for (char &c : plaintext)
        {
            if (isalpha(c))
            {
                char base = islower(c) ? 'a' : 'A';
                int x = c - base;
                int encrypted_char = (a * x + b) % m;
                c = encrypted_char + base;
            }
            // Add the character to ciphertext whether it's transformed or not
            cipher_text += c;
        }
        this->ciphertext = cipher_text; // Update the member variable
        return ciphertext;
    }
    catch (const exception& e)
    {
        cerr << "Encryption error: " << e.what() << endl;
        throw; // Re-throw the exception for the caller to handle
    }
}

string AffineCipher::decrypt()
{
    try
    {
        int n = ciphertext.size();
        if (n == 0) 
        {
            throw runtime_error("Ciphertext cannot be empty.");
        }

        string plain_text;
        int a_inv = modInverse(a, m);

        for (char &c : ciphertext)
        {
            if (isalpha(c))
            {
                char base = islower(c) ? 'a' : 'A';
                int x = c - base;
                int decrypted_char = a_inv * (x - b + m) % m;
                c = decrypted_char + base;
            }
            // Add the character to plain_text whether it's transformed or not
            plain_text += c;
        }
        this->plaintext = plain_text; // Update the member variable
        return plain_text;
    }
    catch (const exception& e)
    {
        cerr << "Decryption error: " << e.what() << std::endl;
        throw; // Re-throw the exception for the caller to handle
    }
}

void AffineCipher::set_plaintext(const string& p)
{
    plaintext = p;
}

void AffineCipher::set_ciphertext(const string& c)
{
    ciphertext = c;
}

#include "CaesarCipher.h"
#include <stdexcept>
#include <cctype>
#include <iostream>

using namespace std;

CaesarCipher::CaesarCipher(const string& p, const string& c, int s) : Cryptography(p, c), shift(s)
{
    try
    {
        if (shift < 0 || shift >= 26)
        {
            throw invalid_argument("Shift value must be in the range [0, 25].");
        }
    }
    catch (const invalid_argument& e)
    {
        cerr << "Initialization error: " << e.what() << endl;
        throw; // Re-throw to signal construction failure
    }
}

string CaesarCipher::encrypt()
{
    try
    {
        if (plaintext.empty())
        {
            throw runtime_error("Plaintext cannot be empty.");
        }

        ciphertext = plaintext;
        for (char &c : ciphertext)
        {
            if (isalpha(c))
            {
                char base = islower(c) ? 'a' : 'A';
                c = (c - base + shift) % 26 + base;
            }
        }
        return ciphertext;
    }
    catch (const exception& e)
    {
        cerr << "Encryption error: " << e.what() << endl;
        throw; // Re-throw the exception for the caller to handle
    }
}

string CaesarCipher::decrypt()
{
    try
    {
        if (ciphertext.empty())
        {
            throw runtime_error("Ciphertext cannot be empty.");
        }

        string plaintext = ciphertext;
        for (char &c : plaintext)
        {
            if (isalpha(c))
            {
                char base = islower(c) ? 'a' : 'A';
                c = (c - base - shift + 26) % 26 + base;
            }
        }
        return plaintext;
    }
    catch (const exception& e)
    {
        cerr << "Decryption error: " << e.what() << endl;
        throw; // Re-throw the exception for the caller to handle
    }
}

void CaesarCipher::set_plaintext(const string& p)
{
    try
    {
        if (p.empty())
        {
            throw invalid_argument("Plaintext cannot be empty.");
        }
        plaintext = p;
    }
    catch (const invalid_argument& e)
    {
        cerr << "Set plaintext error: " << e.what() << endl;
        throw; // Re-throw the exception for the caller to handle
    }
}

void CaesarCipher::set_ciphertext(const string& c)
{
    try
    {
        if (c.empty())
        {
            throw invalid_argument("Ciphertext cannot be empty.");
        }
        ciphertext = c;
    }
    catch (const invalid_argument& e)
    {
        cerr << "Set ciphertext error: " << e.what() << endl;
        throw; // Re-throw the exception for the caller to handle
    }
}

CaesarCipher::~CaesarCipher() {}

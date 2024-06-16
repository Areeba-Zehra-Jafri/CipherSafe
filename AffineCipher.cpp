#include "AffineCipher.h"
#include <stdexcept>
#include <algorithm>
#include <cctype>

int AffineCipher::m = 26;

AffineCipher::AffineCipher(string plain_text, string cipher_text, int a, int b) : Cryptography(plain_text, cipher_text), a(a), b(b)
{
    if (__gcd(a, m) != 1)
    {
        cout << "a and m must be coprime." << endl;
        throw invalid_argument("a and m must be coprime.");
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
    int n = plaintext.size();
    string cipher_text ;
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

string AffineCipher::decrypt()
{
    int n = ciphertext.size();
    string plain_text ;
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
        // Add the character to decrypt_text whether it's transformed or not
        plain_text += c;
    }
    this->plaintext = plain_text; // Update the member variable
   // return decrypt_text;
   return plain_text;
}

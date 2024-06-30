#include <iostream>
#include <string>
#include <stdexcept>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "Vernam_Cipher.h"

using namespace std;

VernamCipher::VernamCipher(const string &plaintext, const string &ciphertext)
    : Cryptography(plaintext, ciphertext)
{

    generateKey(plaintext.length());
    if (plaintext.length() != key.length())
    {
        throw invalid_argument("In Vernam Cipher, key must be the same length as plaintext.");
    }
}

void VernamCipher::generateKey(size_t length)
{
    srand(time(0)); // Seed the random number generator
    key.clear();
    for (size_t i = 0; i < length; ++i)
    {
        key += static_cast<char>('A' + rand() % 26); // Generate a random character from A to Z
    }
}

string VernamCipher::encrypt()
{
    try
    {
        if (plaintext.length() != key.length())
        {
            throw invalid_argument("In Vernam Cipher, key must be the same length as plaintext.");
        }

        srand(time(0));                                    // Seed the random number generator
        auto start = chrono::high_resolution_clock::now(); // Start time

        string ciphertext;
        for (size_t i = 0; i < plaintext.length(); ++i)
        {
            char encrypted_char = ((plaintext[i] - 'A') ^ (key[i] - 'A')) + 'A'; // Map to A-Z
            ciphertext += encrypted_char;

            // Introduce an artificial delay
            int delay = rand() % 100 + 1; // Random delay between 1 and 100 nanoseconds
            auto delay_start = chrono::high_resolution_clock::now();
            while (chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - delay_start).count() < delay)
                ;
        }
        this->ciphertext = ciphertext;

        auto end = chrono::high_resolution_clock::now(); // End time
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
        cout << "Encryption time: " << duration.count() << " ns" << endl; // Print the duration in nanoseconds

        return ciphertext;
    }
    catch (const exception &e)
    {
        cerr << "Encryption error: " << e.what() << endl;
        throw; // Re-throw the exception to propagate it further if needed
    }
}

string VernamCipher::decrypt()
{
    try
    {
        if (ciphertext.length() != key.length())
        {
            throw invalid_argument("Key must be the same length as ciphertext.");
        }

        srand(time(0));                                    // Seed the random number generator
        auto start = chrono::high_resolution_clock::now(); // Start time

        string plaintext;
        for (size_t i = 0; i < ciphertext.length(); ++i)
        {
            char decrypted_char = ((ciphertext[i] - 'A') ^ (key[i] - 'A')) + 'A'; // Reverse the mapping
            plaintext += decrypted_char;

            // Introduce an artificial delay
            int delay = rand() % 100 + 1; // Random delay between 1 and 100 nanoseconds
            auto delay_start = chrono::high_resolution_clock::now();
            while (chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - delay_start).count() < delay)
                ;
        }
        this->plaintext = plaintext;

        auto end = chrono::high_resolution_clock::now(); // End time
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
        cout << "Decryption time: " << duration.count() << " ns" << endl; // Print the duration in nanoseconds

        return plaintext;
    }
    catch (const exception &e)
    {
        cerr << "Decryption error: " << e.what() << endl;
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

void VernamCipher::set_plaintext(const string &p)
{
    plaintext = p;
    generateKey(plaintext.length()); // Generate a new key when plaintext is set
}

void VernamCipher::set_ciphertext(const string &c)
{
    ciphertext = c;
}

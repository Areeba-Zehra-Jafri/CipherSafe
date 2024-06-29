#include "VigenereCipher.h"
#include <stdexcept>
#include <chrono>  // Include the chrono library
#include <cstdlib> // For srand and rand
#include <ctime>   // For time

using namespace std;

VigenereCipher::VigenereCipher(const string &p, const string &c, const string &k)
    : Cryptography(p, c), key(k) {}

void VigenereCipher::set_key(const string &k)
{
    key = k;
}

string VigenereCipher::encrypt()
{
    try
    {
        if (plaintext.empty() || key.empty())
        {
            throw invalid_argument("Empty plaintext or key.");
        }

        srand(time(0));                                    // Seed the random number generator
        auto start = chrono::high_resolution_clock::now(); // Start time

        string encrypted_text;
        for (size_t i = 0; i < plaintext.length(); ++i)
        {
            char plain_char = plaintext[i];
            char key_char = key[i % key.length()];
            char encrypted_char = 'A' + (plain_char - 'A' + key_char - 'A') % 26;
            encrypted_text += encrypted_char;

            // Introduce an artificial delay
            int delay = rand() % 100 + 1; // Random delay between 1 and 100 nanoseconds
            auto delay_start = chrono::high_resolution_clock::now();
            while (chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - delay_start).count() < delay)
                ;
        }
        ciphertext = encrypted_text;

        auto end = chrono::high_resolution_clock::now(); // End time
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
        cout << "Encryption time: " << duration.count() << " ns" << endl; // Print the duration in nanoseconds

        return ciphertext;
    }
    catch (const exception &e)
    {
        cerr << "Encryption error: " << e.what() << endl;
        throw; // Rethrow the exception for handling in the caller code
    }
}

string VigenereCipher::decrypt()
{
    try
    {
        if (ciphertext.empty() || key.empty())
        {
            throw std::invalid_argument("Empty ciphertext or key.");
        }

        srand(time(0));                                    // Seed the random number generator
        auto start = chrono::high_resolution_clock::now(); // Start time

        string decrypted_text;
        for (size_t i = 0; i < ciphertext.length(); ++i)
        {
            char cipher_char = ciphertext[i];
            char key_char = key[i % key.length()];
            char decrypted_char = 'A' + (cipher_char - key_char + 26) % 26;
            decrypted_text += decrypted_char;

            // Introduce an artificial delay
            int delay = rand() % 100 + 1; // Random delay between 1 and 100 nanoseconds
            auto delay_start = chrono::high_resolution_clock::now();
            while (chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - delay_start).count() < delay)
                ;
        }
        plaintext = decrypted_text;

        auto end = chrono::high_resolution_clock::now(); // End time
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
        cout << "Decryption time: " << duration.count() << " ns" << endl; // Print the duration in nanoseconds

        return plaintext;
    }
    catch (const exception &e)
    {
        cerr << "Decryption error: " << e.what() << endl;
        throw; // Rethrow the exception for handling in the caller code
    }
}

void VigenereCipher::set_plaintext(const string &p)
{
    plaintext = p;
}

void VigenereCipher::set_ciphertext(const string &c)
{
    ciphertext = c;
}

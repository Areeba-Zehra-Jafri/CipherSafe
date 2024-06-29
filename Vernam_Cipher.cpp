#include <iostream>
#include <string>
#include <stdexcept>
#include <chrono> // Include the chrono library
#include <cstdlib> // For srand and rand
#include <ctime>   // For time
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

        srand(time(0)); // Seed the random number generator
        auto start = chrono::high_resolution_clock::now(); // Start time

        string ciphertext;
        for (size_t i = 0; i < plaintext.length(); ++i)
        {
            char encrypted_char = ((plaintext[i] - 'A') ^ (key[i] - 'A')) + 'A'; // Map to A-Z
            ciphertext += encrypted_char;

            // Introduce an artificial delay
            int delay = rand() % 100 + 1; // Random delay between 1 and 100 nanoseconds
            auto delay_start = chrono::high_resolution_clock::now();
            while (chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - delay_start).count() < delay);
        }
        this->ciphertext = ciphertext;

        auto end = chrono::high_resolution_clock::now(); // End time
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
        cout << "Encryption time: " << duration.count() << " ns" << endl; // Print the duration in nanoseconds

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

        srand(time(0)); // Seed the random number generator
        auto start = chrono::high_resolution_clock::now(); // Start time

        string plaintext;
        for (size_t i = 0; i < ciphertext.length(); ++i)
        {
            char decrypted_char = ((ciphertext[i] - 'A') ^ (key[i] - 'A')) + 'A'; // Reverse the mapping
            plaintext += decrypted_char;

            // Introduce an artificial delay
            int delay = rand() % 100 + 1; // Random delay between 1 and 100 nanoseconds
            auto delay_start = chrono::high_resolution_clock::now();
            while (chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - delay_start).count() < delay);
        }
        this->plaintext = plaintext;

        auto end = chrono::high_resolution_clock::now(); // End time
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
        cout << "Decryption time: " << duration.count() << " ns" << endl; // Print the duration in nanoseconds

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

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
        throw invalid_argument("\033[1;31mIn Vernam Cipher, key must be the same length as plaintext.\033[0m");
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
            throw invalid_argument("\033[1;31mIn Vernam Cipher, key must be the same length as plaintext.\033[0m");
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
        cout << "\n---------------------------\n";
        cout << "Encryption time: " << duration.count() << " ns" << endl; // Print the duration in nanoseconds
        cout << "---------------------------\n"
             << endl;

        cout << "\n\033[1;34m---------------------------\n";
        cout << "Encryption successful." << endl;
        cout << "\n---------------------------\033[0m\n"<< endl;

        return ciphertext;
    }
    catch (const exception &e)
    {
        cerr << "\033[1;31mEncryption error:\033[0m " << e.what() << endl;
    }
}

string VernamCipher::decrypt()
{
    try
    {
        if (ciphertext.length() != key.length())
        {
            throw invalid_argument("\033[1;31mKey must be the same length as ciphertext.\033[0m");
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
        cout << "\n---------------------------\n";
        cout << "Decryption time: " << duration.count() << " ns" << endl; // Print the duration in nanoseconds
        cout << "---------------------------\n"
             << endl;

        cout << "\n\033[1;34m---------------------------\n";
        cout << "Decryption successful." << endl;
        cout << "\n---------------------------\033[0m\n"<< endl;

        return plaintext;
    }
    catch (const exception &e)
    {
        cerr << "\033[1;31mDecryption error:\033[0m " << e.what() << endl;
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

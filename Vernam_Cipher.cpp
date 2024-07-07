#include <iostream>
#include <string>
#include <stdexcept>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "Vernam_Cipher.h"

using namespace std;

VernamCipher::VernamCipher(const string &plaintext, const string &ciphertext, const string &k)
    : Cryptography(plaintext, ciphertext), key(k)
{
}

void VernamCipher::generateKey(size_t length)
{
    srand(static_cast<unsigned>(time(0))); // Seed the random number generator
    key.clear();
    for (size_t i = 0; i < length; ++i)
    {
        key += static_cast<char>('A' + rand() % 26); // Generate a random character from A to Z
    }
}

string VernamCipher::encrypt()
{
    if (plaintext.length() != key.length())
    {
        throw invalid_argument("\033[1;31mIn Vernam Cipher, key must be the same length as plaintext.\033[0m");
    }
    try
    {
        if (plaintext.length() != key.length())
        {
            throw invalid_argument("\033[1;31mIn Vernam Cipher, key must be the same length as plaintext.\033[0m");
        }

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
        cout << "\n---------------------------\033[0m\n"
             << endl;

        return ciphertext;
    }
    catch (const exception &e)
    {
        cerr << "\033[1;31mEncryption error:\033[0m " << e.what() << endl;
    }
    return "";
}

string VernamCipher::decrypt()
{
    if (ciphertext.length() != key.length())
    {
        throw invalid_argument("\033[1;31mIn Vernam Cipher, key must be the same length as ciphertext.\033[0m");
    }
    try
    {
        if (ciphertext.length() != key.length())
        {
            throw invalid_argument("\033[1;31mKey must be the same length as ciphertext.\033[0m");
        }

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
        cout << "\n---------------------------\033[0m\n"
             << endl;

        return plaintext;
    }
    catch (const exception &e)
    {
        cerr << "\033[1;31mDecryption error:\033[0m " << e.what() << endl;
    }
    return "";
}

string VernamCipher::get_plain_text()
{
    cout << "==INPUT RULES==\n"
         << endl;
    cout << "Input must contain only alphanumeric characters (no spaces)." << endl;
    cout << "-----------------" << endl;
    cout << "Enter the plaintext : ";
    cin >> plaintext;
    cout << "-----------------" << endl;

    return plaintext;
}

string VernamCipher::get_ciphertext()
{
    cout << "-----------------" << endl;
    cout << "Enter the ciphertext : ";
    cin >> ciphertext;
    cout << "-----------------" << endl;

    return ciphertext;
}

void VernamCipher::set_plaintext(const string &p)
{
    try
    {

        for (char c : p)
        {
            if (!isalnum(c))
            {
                throw invalid_argument("\033[1;31mIn Vernam Cipher, plaintext must contain only alphanumeric characters.\033[0m");
            }
        }
        if (plaintext.length() != key.length())
        {
            throw invalid_argument("\033[1;31mIn Vernam Cipher, key must be the same length as plaintext.\033[0m");
        }
        plaintext = p;
    }
    catch (const exception &e)
    {
        cerr << "\033[1;31mError setting plaintext:\033[0m " << e.what() << endl;
    }
}

void VernamCipher::set_ciphertext(const string &c)
{
    try
    {
        if (ciphertext.length() != key.length())
        {
            throw invalid_argument("\033[1;31mIn Vernam Cipher, key must be the same length as ciphertext.\033[0m");
        }
        ciphertext = c;
    }
    catch (const exception &e)
    {
        cerr << "\033[1;31mError setting ciphertext:\033[0m " << e.what() << endl;
    }
}

void VernamCipher::set_key(const string &k)
{
    key = k;
    if (plaintext.length() != key.length() && ciphertext.length() != key.length())
    {
        throw invalid_argument("\033[1;31mIn Vernam Cipher, key must be the same length as plaintext and ciphertext.\033[0m");
    }
}

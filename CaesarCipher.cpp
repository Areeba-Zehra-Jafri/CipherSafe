#include "CaesarCipher.h"
#include <stdexcept>
#include <cctype>
#include <iostream>
#include <chrono> // Include the chrono library

using namespace std;

CaesarCipher::CaesarCipher(const string &p, const string &c, int s) : Cryptography(p, c), shift(s)
{
}

string CaesarCipher::get_ciphertext()
{
    cout << "\n-------------------------------\n";
    cout << "Enter the ciphertext to decrypt:\n";
    cout << "----------------------------------\n"
         << endl;
    cin >> ciphertext;

    return ciphertext;
}

string CaesarCipher::get_plaintext()
{
    cout << "==INPUT RULES==\n";
    cout << "Only alphabetic characters are allowed(no spaces)\n";
    cout << "\n-------------------------------\n";
    cout << "Enter the plaintext to encrypt:\n";
    cout << "--------------------------------\n"
         << endl;
    cin >> plaintext;

    return plaintext;
}

string CaesarCipher::encrypt()
{
    try
    {
        if (plaintext.empty())
        {
            throw runtime_error("\033[1;31mPlaintext cannot be empty.\033[0m");
        }

        srand(time(0)); // Seed the random number generator

        auto start = chrono::high_resolution_clock::now(); // Start time

        ciphertext = plaintext;
        for (char &c : ciphertext)
        {
            if (isalpha(c))
            {
                char base = islower(c) ? 'a' : 'A';
                c = (c - base + shift) % 26 + base;
            }
            int delay = rand() % 100 + 1; // Random delay between 1 and 100 nanoseconds
            auto delay_start = chrono::high_resolution_clock::now();
            while (chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - delay_start).count() < delay)
                ;
        }

        auto end = chrono::high_resolution_clock::now(); // End time
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
        cout << "\n---------------------------\n";
        cout << "Encryption time: " << duration.count() << " ns" << endl;
        cout << "---------------------------\n"
             << endl; // Print the duration in nanoseconds

        cout << "\n\033[1;34m---------------------------\n";
        cout << "Encryption successful." << endl;
        cout << "\n---------------------------\033[0m\n"
             << endl;

        return ciphertext;
    }
    catch (const exception &e)
    {

        cerr << "\033[1;31mEncryption error: " << e.what() << "\033[0m" << endl;
    }
}

string CaesarCipher::decrypt()
{
    try
    {
        if (ciphertext.empty())
        {
            throw runtime_error("\033[1;31mCiphertext cannot be empty.\033[0m");
        }

        srand(time(0)); // Seed the random number generator

        auto start = chrono::high_resolution_clock::now(); // Start time

        string plaintext = ciphertext;
        for (char &c : plaintext)
        {
            if (isalpha(c))
            {
                char base = islower(c) ? 'a' : 'A';
                c = (c - base - shift + 26) % 26 + base;
            }
            int delay = rand() % 100 + 1; // Random delay between 1 and 100 nanoseconds
            auto delay_start = chrono::high_resolution_clock::now();
            while (chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - delay_start).count() < delay)
                ;
        }

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
        cerr << "\033[1;31mDecryption error: " << e.what() << "\033[0m" << endl;
    }
}

void CaesarCipher::set_plaintext(const string &p)
{
    try
    {

        if (plaintext.empty())
        {
            throw invalid_argument("\033[1;31mPlaintext cannot be empty.\033[0m");
        }

        for (char c : plaintext)
        {
            if (!isalpha(c))
            {
                throw invalid_argument("\033[1;31mPlaintext must contain only alphabetic characters.\033[0m");
            }
        }
        plaintext = p;
    }
    catch (const invalid_argument &e)
    {
        cerr << "\033[1;31mSet plaintext error:" << e.what() << "\033[0m" << endl;
    }
}

void CaesarCipher::set_ciphertext(const string &c)
{
    try
    {

        if (ciphertext.empty())
        {
            throw invalid_argument("\033[1;31mCiphertext cannot be empty.\033[0m");
        }

        for (char c : ciphertext)
        {
            if (!isalpha(c))
            {
                throw invalid_argument("\033[1;31mCiphertext must contain only alphabetic characters.\033[0m");
            }
        }
        ciphertext = c;
    }
    catch (const invalid_argument &e)
    {
        cerr << "\033[1;31mSet ciphertext error:" << e.what() << "\033[0m" << endl;
    }
}

CaesarCipher::~CaesarCipher() {}

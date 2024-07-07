#include "AffineCipher.h"
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <chrono>  // Include the chrono library
#include <cstdlib> // For srand and rand
#include <ctime>   // For time

using namespace std;

int AffineCipher::m = 26;

AffineCipher::AffineCipher(const string &plain_text, const string &cipher_text, int a, int b) : Cryptography(plain_text, cipher_text), a(a), b(b)
{
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
    throw invalid_argument("\033[1;31mMultiplicative inverse does not exist.\033[0m");
}

string AffineCipher::get_ciphertext()
{
    cout << "\n-------------------------------\n";
    cout << "Enter the ciphertext to decrypt:\n";
    cout << "----------------------------------\n"
         << endl;
    cin >> ciphertext;

    return ciphertext;
}

string AffineCipher::get_plaintext()
{
    cout << "==INPUT RULES ==\n";
    cout << "Only alphabetic characters are allowed(no spaces)\n";
    cout << "\n-------------------------------\n";
    cout << "Enter the plaintext to encrypt:\n";
    cout << "--------------------------------\n"
         << endl;
    cin >> plaintext;

    return plaintext;
}

string AffineCipher::encrypt()
{
    try
    {
        int n = plaintext.size();
        if (n == 0)
        {
            throw runtime_error("\033[1;31mPlaintext cannot be empty.\033[0m");
        }

        srand(time(0)); // Seed the random number generator

        auto start = chrono::high_resolution_clock::now(); // Start time

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

            // Introduce an artificial delay
            int delay = rand() % 100 + 1; // Random delay between 1 and 100 nanoseconds
            auto delay_start = chrono::high_resolution_clock::now();
            while (chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - delay_start).count() < delay)
                ;
        }
        this->ciphertext = cipher_text; // Update the member variable

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
        cerr << "\033[1;31mPlaintext cannot be empty.\033[0m " << e.what() << endl;
    }
}

string AffineCipher::decrypt()
{
    try
    {
        int n = ciphertext.size();
        if (n == 0)
        {
            throw runtime_error("\033[1;31mCiphertext cannot be empty.\033[0m");
        }

        srand(time(0));

        auto start = chrono::high_resolution_clock::now(); // Start time

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

            // Introduce an artificial delay
            int delay = rand() % 100 + 1; // Random delay between 1 and 100 nanoseconds
            auto delay_start = chrono::high_resolution_clock::now();
            while (chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - delay_start).count() < delay)
                ;
        }
        this->plaintext = plain_text; // Update the member variable

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

        return plain_text;
    }
    catch (const exception &e)
    {
        cerr << "\033[1;31mDecryption error: \033[0m " << e.what() << std::endl;
    }
}

void AffineCipher::set_plaintext(const string &p)
{
    try
    {

        for (char c : plaintext)
        {
            if (!isalpha(c))
            {
                throw invalid_argument("\033[1;31mPlaintext should only contain alphabetic characters.\033[0m");
            }
        }
        plaintext = p;
    }
    catch (const exception &e)
    {
        cerr << e.what() << endl;
    }
}

void AffineCipher::set_ciphertext(const string &c)
{
    try
    {

        for (char ch : ciphertext)
        {
            if (!isalpha(ch))
            {
                throw invalid_argument("\033[1;31mCiphertext should only contain alphabetic characters.\033[0m");
            }
        }
        ciphertext = c;
    }
    catch (const exception &e)
    {
        cerr << e.what() << endl;
    }
}

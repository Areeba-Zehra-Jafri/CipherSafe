#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "HillCipher.h"

using namespace std;
using namespace std::chrono;

// Function to compute the determinant of a 2x2 matrix
int HillCipher::determinant(int a, int b, int c, int d)
{
    return (a * d - b * c + 26) % 26;
}

// Function to calculate the modular inverse using the extended Euclidean algorithm
int HillCipher::modInverse(int a, int m)
{
    a = a % m;
    for (int x = 1; x < m; x++)
    {
        if ((a * x) % m == 1)
        {
            return x;
        }
    }
    return -1; // If modular inverse does not exist
}

// Function to generate the key matrix from the given key string
void HillCipher::generateKeyMatrix()
{
    keyMatrix.resize(2, vector<int>(2));

    keyMatrix[0][0] = key[0] - 'a';
    keyMatrix[0][1] = key[1] - 'a';
    keyMatrix[1][0] = key[2] - 'a';
    keyMatrix[1][1] = key[3] - 'a';
}

// Function to generate the inverse key matrix using the key matrix
void HillCipher::generateInverseKeyMatrix()
{
    generateKeyMatrix();
    int det = determinant(keyMatrix[0][0], keyMatrix[0][1], keyMatrix[1][0], keyMatrix[1][1]);
    int detInverse = modInverse(det, 26);

    if (detInverse == -1)
    {
        throw runtime_error("\033[1;31mInverse key matrix cannot be generated; determinant has no modular inverse.\033[0m");
    }

    inverseKeyMatrix.resize(2, vector<int>(2));

    inverseKeyMatrix[0][0] = (keyMatrix[1][1] * detInverse) % 26;
    inverseKeyMatrix[0][1] = (-keyMatrix[0][1] * detInverse) % 26;
    inverseKeyMatrix[1][0] = (-keyMatrix[1][0] * detInverse) % 26;
    inverseKeyMatrix[1][1] = (keyMatrix[0][0] * detInverse) % 26;

    // Ensure all elements in the inverse key matrix are positive modulo 26
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            if (inverseKeyMatrix[i][j] < 0)
            {
                inverseKeyMatrix[i][j] += 26;
            }
        }
    }
}

// Constructor to initialize the HillCipher object with key and plaintext
HillCipher::HillCipher(const string &c, const string &p, const string &k) : Cryptography(p, c), key(k) {}

// Function to encrypt the plaintext using the Hill cipher
string HillCipher::encrypt()
{
    try
    {
        generateKeyMatrix();

        if (plaintext.empty())
        {
            throw runtime_error("\033[1;31mPlaintext cannot be empty.\033[0m");
        }

        for (char ch : plaintext)
        {
            if (!islower(ch))
            {
                throw invalid_argument("\033[1;31mPlaintext should only contain lowercase alphabetic characters.\033[0m");
            }
        }

        srand(time(0)); // Seed the random number generator

        auto start = chrono::high_resolution_clock::now(); // Start time

        string paddedPlaintext = plaintext;

        if (paddedPlaintext.length() % 2 != 0)
        {
            paddedPlaintext += 'x'; // Padding with 'x' to make plaintext length even
        }

        ciphertext = "";

        for (size_t i = 0; i < paddedPlaintext.length(); i += 2)
        {
            int first = paddedPlaintext[i] - 'a';
            int second = paddedPlaintext[i + 1] - 'a';

            char enc_first = ((keyMatrix[0][0] * first + keyMatrix[0][1] * second) % 26) + 'a';
            char enc_second = ((keyMatrix[1][0] * first + keyMatrix[1][1] * second) % 26) + 'a';

            ciphertext += enc_first;
            ciphertext += enc_second;

            int delay = rand() % 100 + 1; // Random delay between 1 and 100 nanoseconds
            auto delay_start = chrono::high_resolution_clock::now();
            while (chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - delay_start).count() < delay)
                ;
        }

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
}

string HillCipher::decrypt()
{
    try
    {
        generateInverseKeyMatrix();

        if (ciphertext.empty())
        {
            throw runtime_error("\033[1;31mCiphertext cannot be empty.\033[0m");
        }

        if (ciphertext.length() % 2 != 0)
        {
            throw invalid_argument("\033[1;31mCiphertext length must be even\033[0m");
        }

        srand(time(0)); // Seed the random number generator

        auto start = chrono::high_resolution_clock::now(); // Start time

        plaintext = "";

        for (size_t i = 0; i < ciphertext.length(); i += 2)
        {
            int first = ciphertext[i] - 'a';
            int second = ciphertext[i + 1] - 'a';

            char dec_first = ((inverseKeyMatrix[0][0] * first + inverseKeyMatrix[0][1] * second) % 26) + 'a';
            char dec_second = ((inverseKeyMatrix[1][0] * first + inverseKeyMatrix[1][1] * second) % 26) + 'a';

            plaintext += dec_first;
            plaintext += dec_second;

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

        // Remove padding 'x' characters added during encryption
        size_t paddingLength = plaintext.length() - ciphertext.length();
        if (paddingLength > 0)
        {
            plaintext = plaintext.substr(0, plaintext.length() - paddingLength);
        }

        return plaintext;
    }
    catch (const exception &e)
    {
        cerr << "\033[1;31mDecryption error:\033[0m " << e.what() << endl;
    }
}

void HillCipher::set_plaintext(const string &p)
{
    try
    {
        cout << "==INPUT RULES==";
        cout << "Input must contain only lowercase alphabetic characters (no spaces)." << endl;
        cout << "\n---------------------\n";
        cout << "Enter the plaintext :\n";
        cout << "-----------------------\n";
        cin >> plaintext;
        if (plaintext.empty())
        {
            throw invalid_argument("\033[1;31mPlaintext cannot be empty.\033[0m");
        }
        for (char ch : plaintext)
        {
            if (!islower(ch))
            {
                throw invalid_argument("\033[1;31mPlaintext should only contain lowercase alphabetic characters.\033[0m");
            }
        }
    }
    catch (const invalid_argument &e)
    {
        cerr << "\033[1;31mSet plaintext error:\033[0m " << e.what() << endl;
    }
}

void HillCipher::set_ciphertext(const string &c)
{
    try
    {
        cout << "\n---------------------\n";
        cout << "Enter the ciphertext :\n";
        cout << "-----------------------\n";
        cin >> ciphertext;

        if (ciphertext.empty())
        {
            throw invalid_argument("\033[1;31mCiphertext cannot be empty.\033[0m");
        }
        for (char ch : ciphertext)
        {
            if (!islower(ch))
            {
                throw invalid_argument("\033[1;31mCiphertext should only contain lowercase alphabetic characters.\033[0m");
            }
        }
    }
    catch (const invalid_argument &e)
    {
        cerr << "\033[1;31mSet ciphertext error:\033[0m " << e.what() << endl;
    }
}

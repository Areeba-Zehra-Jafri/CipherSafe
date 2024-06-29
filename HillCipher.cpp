#include "HillCipher.h"
#include <vector>
#include <stdexcept>
#include <iostream>
#include <cctype>
#include <chrono> // Include the chrono library
#include <cstdlib> // For srand and rand
#include <ctime>   // For time

using namespace std;
using namespace std::chrono;

// Constructor implementation
HillCipher::HillCipher(const string& p, const string& c, const string& key) : Cryptography(p, c)
{
    try
    {
        generateKeyMatrix(key);
        generateInverseKeyMatrix();
    }
    catch (const invalid_argument& e)
    {
        cerr << "Initialization error: " << e.what() << std::endl;
        throw; // Re-throw to signal construction failure
    }
}

int HillCipher::modInverse(int a, int m)
{
    a = a % m;
    for (int x = 1; x < m; x++)
    {
        if ((a * x) % m == 1)
            return x;
    }
    throw invalid_argument("No modular inverse found");
}

void HillCipher::generateKeyMatrix(const string& key)
{
    if (key.length() != 4)
    {
        throw invalid_argument("Key must be 4 characters long");
    }

    keyMatrix = {
        {(key[0] - 'a') % 26, (key[1] - 'a') % 26},
        {(key[2] - 'a') % 26, (key[3] - 'a') % 26}
    };
}

void HillCipher::generateInverseKeyMatrix()
{
    int determinant = keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0];
    determinant = determinant % 26;
    if (determinant < 0)
    {
        determinant += 26;
    }

    int inverseDet = modInverse(determinant, 26);

    inverseKeyMatrix = {
        {(keyMatrix[1][1] * inverseDet) % 26, (-keyMatrix[0][1] * inverseDet) % 26},
        {(-keyMatrix[1][0] * inverseDet) % 26, (keyMatrix[0][0] * inverseDet) % 26}
    };

    for (auto& row : inverseKeyMatrix)
    {
        for (auto& elem : row)
        {
            if (elem < 0)
            {
                elem += 26;
            }
        }
    }
}

string HillCipher::encrypt()
{
    try
    {
        if (plaintext.empty())
        {
            throw runtime_error("Plaintext cannot be empty.");
        }
            srand(time(0)); // Seed the random number generator

        auto start = chrono::high_resolution_clock::now(); // Start time

        ciphertext = "";

        if (plaintext.length() % 2 != 0)
        {
            plaintext += 'x'; // Padding with 'x' to make plaintext length even
        }

        for (size_t i = 0; i < plaintext.length(); i += 2)
        {
            int first = plaintext[i] - 'a';
            int second = plaintext[i + 1] - 'a';

            char enc_first = ((keyMatrix[0][0] * first + keyMatrix[0][1] * second) % 26) + 'a';
            char enc_second = ((keyMatrix[1][0] * first + keyMatrix[1][1] * second) % 26) + 'a';

            ciphertext += enc_first;
            ciphertext += enc_second;

             int delay = rand() % 100 + 1; // Random delay between 1 and 100 nanoseconds
            auto delay_start = chrono::high_resolution_clock::now();
            while (chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - delay_start).count() < delay);
        }

        auto end = chrono::high_resolution_clock::now(); // End time
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
        cout << "Encryption time: " << duration.count() << " ns" << endl; // Print the duration in nanoseconds

        return ciphertext;
    }
    catch (const exception& e)
    {
        cerr << "Encryption error: " << e.what() << endl;
        throw; // Re-throw the exception for the caller to handle
    }
}

string HillCipher::decrypt()
{
    try
    {
        if (ciphertext.empty())
        {
            throw runtime_error("Ciphertext cannot be empty.");
        }

        if (ciphertext.length() % 2 != 0)
        {
            throw invalid_argument("Ciphertext length must be even");
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
            while (chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - delay_start).count() < delay);
        }
            auto end = chrono::high_resolution_clock::now(); // End time
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
        cout << "Decryption time: " << duration.count() << " ns" << endl; // Print the duration in nanoseconds

        return plaintext;
    }
    catch (const exception& e)
    {
        cerr << "Decryption error: " << e.what() << endl;
        throw; // Re-throw the exception for the caller to handle
    }
}

void HillCipher::set_plaintext(const string& p)
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

void HillCipher::set_ciphertext(const string& c)
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

HillCipher::~HillCipher() {}

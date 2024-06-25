#include "HillCipher.h"
#include <vector>
#include <stdexcept>
#include <iostream>

// Constructor implementation
HillCipher::HillCipher(const string& p, const string& c, const string& key) : Cryptography(p, c)
{
    generateKeyMatrix(key);
    generateInverseKeyMatrix();
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
    }

    return ciphertext;
}

string HillCipher::decrypt()
{
    plaintext = "";

    if (ciphertext.length() % 2 != 0)
    {
        throw invalid_argument("Ciphertext length must be even");
    }

    for (size_t i = 0; i < ciphertext.length(); i += 2)
    {
        int first = ciphertext[i] - 'a';
        int second = ciphertext[i + 1] - 'a';

        char dec_first = ((inverseKeyMatrix[0][0] * first + inverseKeyMatrix[0][1] * second) % 26) + 'a';
        char dec_second = ((inverseKeyMatrix[1][0] * first + inverseKeyMatrix[1][1] * second) % 26) + 'a';

        plaintext += dec_first;
        plaintext += dec_second;
    }

    return plaintext;
}
void HillCipher::set_plaintext(const string& p)
{
    plaintext=p;
}
void HillCipher::set_ciphertext(const string& c)
{
    ciphertext=c;
}
HillCipher::~HillCipher() {}

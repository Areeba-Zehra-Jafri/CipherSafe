#include "CaesarCipher.h"

CaesarCipher::CaesarCipher(string p,string c,int s):Cryptography(p,c),shift(s){}

string CaesarCipher::encrypt()
{
    ciphertext = plaintext;
    for (char &c : ciphertext)
    {
        if (isalpha(c))
        {
            char base = islower(c) ? 'a' : 'A';
            c = (c - base + shift) % 26 + base;
        }
    }
    return ciphertext;
}

string CaesarCipher::decrypt()
{
    string plaintext = ciphertext;
    for (char &c : plaintext)
    {
        if (isalpha(c))
        {
            char base = islower(c) ? 'a' : 'A';
            c = (c - base - shift + 26) % 26 + base;
        }
    }
    return plaintext;
}
CaesarCipher::~CaesarCipher(){}

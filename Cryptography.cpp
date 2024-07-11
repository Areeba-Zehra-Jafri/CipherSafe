#include "Cryptography.h"

Cryptography::Cryptography(const string &p, const string &c) : plaintext(p), ciphertext(c) {}
void Cryptography::set_plaintext(const string &p)
{
    plaintext = p;
}
void Cryptography::set_ciphertext(const string &c)
{
    ciphertext = c;
}

string Cryptography::get_ciphertext()
{
    return ciphertext;
}

string Cryptography::get_plaintext()
{
    return plaintext;
}

Cryptography::~Cryptography() {}
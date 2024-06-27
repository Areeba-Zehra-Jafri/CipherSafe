#include "VigenereCipher.h"

VigenereCipher::VigenereCipher(const string& p,const string& c,const string& k):Cryptography(p,c), key(k) {}

void VigenereCipher::set_key(const string& k) {
    key = k;
}

string VigenereCipher::encrypt() {
    string encrypted_text;
    for (size_t i = 0; i < plaintext.length(); ++i) {
        char plain_char = plaintext[i];
        char key_char = key[i % key.length()];
        char encrypted_char = 'A' + (plain_char - 'A' + key_char - 'A') % 26;
        encrypted_text += encrypted_char;
    }
    ciphertext = encrypted_text;
    return ciphertext;
}

string VigenereCipher::decrypt() {
    string decrypted_text;
    for (size_t i = 0; i < ciphertext.length(); ++i) {
        char cipher_char = ciphertext[i];
        char key_char = key[i % key.length()];
        char decrypted_char = 'A' + (cipher_char - key_char + 26) % 26;
        decrypted_text += decrypted_char;
    }
    plaintext = decrypted_text;
    return plaintext;
}
void VigenereCipher::set_plaintext(const string& p)
{
    plaintext=p;
}
void VigenereCipher::set_ciphertext(const string& c)
{
    ciphertext=c;
}
#include "vernamcipher.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

// Constructor
vernamcipher::vernamcipher(const string& k) : key(k) {
    if (k.empty()) {
        cout << "Key cannot be empty" << endl;
        exit(1);
    }
}

// Encrypt function
string vernamcipher::encrypt(const string &plaintext) const {
    string ciphertext;
    for (size_t i = 0; i < plaintext.size(); ++i) {
        char encrypt_text = (plaintext[i] - 'A' + key[i % key.length()] - 'A') % 26 + 'A';
        ciphertext += encrypt_text;
    }
    return ciphertext;
}

// Decrypt function
string vernamcipher::decrypt(const string &ciphertext) const {
    string plaintext;
    for (size_t i = 0; i < ciphertext.length(); ++i) {
    char decrypt_text = (ciphertext[i] - key[i % key.length()] + 26) % 26 + 'A';
        plaintext += decrypt_text;
    }
    return plaintext;
}


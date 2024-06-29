#include "monoalphabetic.h"
#include <iostream>
#include <cctype>

monoalphabetic::monoalphabetic(const string& p, const string& c, const string& k) : Cryptography(p, c), key(k) {
    if (key.length() != sets.length()) {
        throw invalid_argument("Key length must match the length of the character set.");
    }
}

string monoalphabetic::encrypt() {
    string ciphertext = "";

    for (int i = 0; i < plaintext.length(); i++) {
        if (isalnum(plaintext[i])) {
            for (int j = 0; j < sets.length(); j++) {
                if (plaintext.at(i) == sets.at(j)) {
                    ciphertext += key.at(j);
                    break;
                }
            }
        } else {
            ciphertext += char(plaintext[i]);
        }
    }
    return ciphertext;
}

string monoalphabetic::decrypt() {
    string plaintext = "";
    for (int i = 0; i < ciphertext.length(); i++) {
        if (isalnum(ciphertext[i])) {
            for (int j = 0; j < key.length(); j++) {
                if (ciphertext.at(i) == key.at(j)) {
                    plaintext += sets.at(j);
                    break;
                }
            }
        } else {
            plaintext += char(ciphertext[i]);
        }
    }
    return plaintext;
}

void monoalphabetic::set_plaintext(const string& p) {
    try {
        if (p.empty()) {
            throw invalid_argument("Plaintext cannot be empty.");
        }
        plaintext = p;
    } catch (const invalid_argument& e) {
        cerr << "Set plaintext error: " << e.what() << endl;
        throw; // Re-throw the exception for the caller to handle
    }
}

void monoalphabetic::set_ciphertext(const string& c) {
    try {
        if (c.empty()) {
            throw invalid_argument("Ciphertext cannot be empty.");
        }
        ciphertext = c;
    } catch (const invalid_argument& e) {
        cerr << "Set ciphertext error: " << e.what() << endl;
        throw; // Re-throw the exception for the caller to handle
    }
}

// #include "monoalphabetic.h"
// #include <iostream>
// #include <cctype>

// monoalphabetic::monoalphabetic(const string& p, const string& c, const string& k) : Cryptography(p, c), key(k) {
//     if (key.length() != sets.length()) {
//         throw invalid_argument("Key length must match the length of the character set.");
//     }
// }

// string monoalphabetic::encrypt() {
//     string ciphertext = "";

//     for (int i = 0; i < plaintext.length(); i++) {
//         if (isalnum(plaintext[i])) {
//             for (int j = 0; j < sets.length(); j++) {
//                 if (plaintext.at(i) == sets.at(j)) {
//                     ciphertext += key.at(j);
//                     break;
//                 }
//             }
//         } else {
//             ciphertext += char(plaintext[i]);
//         }
//     }
//     return ciphertext;
// }

// string monoalphabetic::decrypt() {
//     string plaintext = "";
//     for (int i = 0; i < ciphertext.length(); i++) {
//         if (isalnum(ciphertext[i])) {
//             for (int j = 0; j < key.length(); j++) {
//                 if (ciphertext.at(i) == key.at(j)) {
//                     plaintext += sets.at(j);
//                     break;
//                 }
//             }
//         } else {
//             plaintext += char(ciphertext[i]);
//         }
//     }
//     return plaintext;
// }

// void monoalphabetic::set_plaintext(const string& p) {
//     try {
//         if (p.empty()) {
//             throw invalid_argument("Plaintext cannot be empty.");
//         }
//         plaintext = p;
//     } catch (const invalid_argument& e) {
//         cerr << "Set plaintext error: " << e.what() << endl;
//         throw; // Re-throw the exception for the caller to handle
//     }
// }

// void monoalphabetic::set_ciphertext(const string& c) {
//     try {
//         if (c.empty()) {
//             throw invalid_argument("Ciphertext cannot be empty.");
//         }
//         ciphertext = c;
//     } catch (const invalid_argument& e) {
//         cerr << "Set ciphertext error: " << e.what() << endl;
//         throw; // Re-throw the exception for the caller to handle
//     }
// }
#include "monoalphabetic.h"
#include <iostream>
#include <cctype>
#include"Cryptography.h"

using namespace std;
// Constructor
monoalphabetic::monoalphabetic(const string& p, const string& c, const string& k)
    : Cryptography(p, c), key(k) {
    //validateKey(key);
    createCipherAlphabet();
}

// Function to validate the key
// void monoalphabetic::validateKey(const string& key) {
//     if (key.length() != 26) {
//         throw invalid_argument("Key length must be 26 characters.");
//     }

//     unordered_set<char> charSet;
//     for (char c : key) {
//         if (!islower(c)) {
//             throw invalid_argument("Key must contain only lowercase alphabetic characters.");
//         }
//         if (charSet.find(c) != charSet.end()) {
//             throw invalid_argument("Key must not contain duplicate characters.");
//         }
//         charSet.insert(c);
//     }
// }

// Helper function to create the cipher and decipher maps
void monoalphabetic::createCipherAlphabet() {
    for (size_t i = 0; i < sets.length(); ++i) {
        cipher[sets[i]] = key[i];
        decipher[key[i]] = sets[i];
    }
}

// Function to encrypt the plaintext
std::string monoalphabetic::encrypt() {
    std::string ciphertext = plaintext;
    for (char& c : ciphertext) {
        if (isalpha(c)) {
            bool is_upper = isupper(c);
            char lower_c = tolower(c);
            c = is_upper ? toupper(cipher[lower_c]) : cipher[lower_c];
        }
    }
    return ciphertext;
}

// Function to decrypt the ciphertext
std::string monoalphabetic::decrypt() {
    std::string plaintext = ciphertext;
    for (char& c : plaintext) {
        if (isalpha(c)) {
            bool is_upper = isupper(c);
            char lower_c = tolower(c);
            c = is_upper ? toupper(decipher[lower_c]) : decipher[lower_c];
        }
    }
    return plaintext;
}

// Setter for plaintext
void monoalphabetic::set_plaintext(const std::string& p) {
    try {
        if (p.empty()) {
            throw std::invalid_argument("Plaintext cannot be empty.");
        }
        plaintext = p;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Set plaintext error: " << e.what() << std::endl;
        throw; // Re-throw the exception for the caller to handle
    }
}

// Setter for ciphertext
void monoalphabetic::set_ciphertext(const std::string& c) {
    try {
        if (c.empty()) {
            throw std::invalid_argument("Ciphertext cannot be empty.");
        }
        ciphertext = c;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Set ciphertext error: " << e.what() << std::endl;
        throw; // Re-throw the exception for the caller to handle
    }
}


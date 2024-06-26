#include "monoalphabetic.h"
#include <iostream>
#include <cctype>
#include "Cryptography.h"

using namespace std;
// Constructor
monoalphabetic::monoalphabetic(const string &p, const string &c, const string &k)
    : Cryptography(p, c), key(k)
{
    // validateKey(key);
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
void monoalphabetic::createCipherAlphabet()
{
    for (size_t i = 0; i < sets.length(); ++i)
    {
        cipher[sets[i]] = key[i];
        decipher[key[i]] = sets[i];
    }
}

// Function to encrypt the plaintext
string monoalphabetic::encrypt()
{
    string ciphertext = plaintext;
    for (char &c : ciphertext)
    {
        if (isalpha(c))
        {
            bool is_upper = isupper(c);
            char lower_c = tolower(c);
            c = is_upper ? toupper(cipher[lower_c]) : cipher[lower_c];
        }
    }

    cout << "\n\033[1;34m---------------------------\n";
    cout << "Encryption successful." << endl;
    cout << "\n---------------------------\033[0m\n"<< endl;
    return ciphertext;
}

// Function to decrypt the ciphertext
string monoalphabetic::decrypt()
{
    string plaintext = ciphertext;
    for (char &c : plaintext)
    {
        if (isalpha(c))
        {
            bool is_upper = isupper(c);
            char lower_c = tolower(c);
            c = is_upper ? toupper(decipher[lower_c]) : decipher[lower_c];
        }
    }

    cout << "\n\033[1;34m---------------------------\n";
    cout << "Decryption successful." << endl;
    cout << "\n---------------------------\033[0m\n"<< endl;
              
    return plaintext;
}

// Setter for plaintext
void monoalphabetic::set_plaintext(const std::string &p)
{
    try
    {
        if (p.empty())
        {
            throw invalid_argument("\033[1;31mPlaintext cannot be empty.\033[0m");
        }
        plaintext = p;
    }
    catch (const invalid_argument &e)
    {
        cerr << "\033[1;31mSet plaintext error:\033[0m " << e.what() << endl;
    }
}

// Setter for ciphertext
void monoalphabetic::set_ciphertext(const string &c)
{
    try
    {
        if (c.empty())
        {
            throw std::invalid_argument("\033[1;31mCiphertext cannot be empty.\033[0m");
        }
        ciphertext = c;
    }
    catch (const invalid_argument &e)
    {
        cerr << "\033[1;31mSet ciphertext error:\033[0m " << e.what() << endl;
 
    }
}

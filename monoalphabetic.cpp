#include "monoalphabetic.h"
#include <iostream>
#include <cctype>
#include "Cryptography.h"

using namespace std;
// Constructor
monoalphabetic::monoalphabetic(const string &p, const string &c, const string &k)
    : Cryptography(p, c), key(k)
{
    createCipherAlphabet();
}

// Helper function to create the cipher and decipher maps
void monoalphabetic::createCipherAlphabet()
{
    for (size_t i = 0; i < sets.length(); ++i)
    {
        cipher[sets[i]] = key[i];
        decipher[key[i]] = sets[i];
    }
}

string monoalphabetic::get_plaintext()
{
    cout << "==INPUT RULES==\n";
    cout << "\nOnly alphabets are allowed (No spaces)." << endl;
    cout << "\n----------------------\n";
    cout << "Enter the plaintext (only alphabetic characters) : ";
    cin >> plaintext;
    cout << "\n----------------------\n";

    return plaintext;
}

string monoalphabetic::get_ciphertext()
{

    cout << "\n-----------------------\n";
    cout << "Enter the ciphertext : ";
    cin >> ciphertext;
    cout << "\n-----------------------\n";

    return ciphertext;
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
    cout << "\n---------------------------\033[0m\n"
         << endl;
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
    cout << "\n---------------------------\033[0m\n"
         << endl;

    return plaintext;
}

void monoalphabetic::set_plaintext(const string &p)
{
    try
    {

        if (p.empty())
        {
            throw invalid_argument("\033[1;31mPlaintext cannot be empty.\033[0m");
        }
        for (char ch : p)
        {
            if (!isalpha(ch))
            {
                throw invalid_argument("\033[1;31mPlaintext should only contain alphabetic characters.\033[0m");
            }
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

        for (char ch : c)
        {
            if (!isalpha(ch))
            {
                throw invalid_argument("\033[1;31mCiphertext should only contain alphabetic characters.\033[0m");
            }
            if (!isupper(ch) && !islower(ch))
            {
                throw invalid_argument("\033[1;31mCiphertext should only contain uppercase or lowercase alphabetic characters.\033[0m");
            }
        }
        ciphertext = c;
    }
    catch (const invalid_argument &e)
    {
        cerr << "\033[1;31mSet ciphertext error:\033[0m " << e.what() << endl;
    }
}

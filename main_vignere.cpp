#include <iostream>
#include <string>
#include "vignere.h"

using namespace std;

int main() {
    // Get plaintext and key from user
    string plaintext, key;
    cout << "Enter plaintext: ";
    getline(cin, plaintext);
    cout << "Enter key: ";
    getline(cin, key);

    // Create a VigenereCipher object
    VigenereCipher cipher(plaintext, key);

    // Encrypt the plaintext
    string encryptedText = cipher.encrypt();
    cout << "Encrypted Text: " << encryptedText << endl;

    // Decrypt the ciphertext
    VigenereCipher decryptCipher(encryptedText, key);
    string decryptedText = decryptCipher.decrypt();
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}

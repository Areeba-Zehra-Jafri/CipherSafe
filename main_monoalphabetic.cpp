#include <iostream>
#include "monoalphabetic.h"

int main() {
    string plaintext = "HelloWorld123";
    string key = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1023456789"; // Length must be 62
    string ciphertext = "";

    try {
        // Create an instance of monoalphabetic with plaintext, ciphertext, and key
        monoalphabetic mono(plaintext, ciphertext, key);

        // Set the plaintext
        mono.set_plaintext(plaintext);

        // Encrypt the plaintext
        ciphertext = mono.encrypt();
        cout << "Encrypted Text: " << ciphertext << endl;

        // Set the ciphertext for decryption
        mono.set_ciphertext(ciphertext);

        // Decrypt the ciphertext
        string decrypted_text = mono.decrypt();
        cout << "Decrypted Text: " << decrypted_text << endl;

        // Check if decryption matches original plaintext
        if (decrypted_text == plaintext) {
            cout << "Decryption successful!" << endl;
        } else {
            cout << "Decryption failed!" << endl;
        }
    } catch (const invalid_argument& e) {
        cerr << "Initialization error: " << e.what() << endl;
        return 1; // Exit if there's an error during initialization
    }

    return 0;
}

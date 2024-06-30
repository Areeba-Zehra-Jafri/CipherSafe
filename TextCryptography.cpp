#include "TextCryptography.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib> // For srand and rand
#include <ctime>   // For time

using namespace std;

void TextCryptography::processText() {
    int choice;
    string text;

    while (true) {
        cout << "1-Encrypt a text" << endl;
        cout << "2-Decrypt a text" << endl;
        cout << "3-Exit" << endl;
        cin >> choice;

        if (choice == 3) {
            exit(0);
        }

        cin.ignore(); // Ignore any newline characters left in the input buffer
        cout << "Enter the text: ";
        getline(cin, text);

        switch (choice) {
            case 1:
                try {
                    encryptText(text);
                } catch (const exception& e) {
                    cerr << "Encryption Error: " << e.what() << endl;
                }
                break;
            case 2:
                try {
                    decryptText(text);
                } catch (const exception& e) {
                    cerr << "Decryption Error: " << e.what() << endl;
                }
                break;
            default:
                cout << "Invalid input" << endl;
                break;
        }
    }
}

void TextCryptography::encryptText(const string& plaintext) {
    Cryptography* cipher = selectCipher();
    if (!cipher) {
        throw runtime_error("Invalid cipher selection.");
    }

    try {
        cipher->set_plaintext(plaintext);
        string encryptedText = cipher->encrypt();
        cout << "Encrypted text: " << encryptedText << endl;
    } catch (const exception& e) {
        delete cipher;
        throw;  // Re-throw exception for outer handling
    }

    delete cipher;  // Clean up dynamically allocated memory
}

void TextCryptography::decryptText(const string& ciphertext) {
    Cryptography* cipher = selectCipher();
    if (!cipher) {
        throw runtime_error("Invalid cipher selection.");
    }

    try {
        cipher->set_ciphertext(ciphertext);
        string decryptedText = cipher->decrypt();
        cout << "Decrypted text: " << decryptedText << endl;
    } catch (const exception& e) {
        delete cipher;
        throw;  // Re-throw exception for outer handling
    }

    delete cipher;  // Clean up dynamically allocated memory
}

Cryptography* TextCryptography::selectCipher() {
    int choice;
    cout << "1-Caesar Cipher" << endl;
    cout << "2-Hill Cipher" << endl;
    cout << "3-Affine Cipher" << endl;
    cout << "4-Vigenere Cipher" << endl;
    cout << "5-Rail Fence Cipher" << endl;
    cout << "6-Monoalphabetic Cipher" << endl;
    cout << "7-Vernam Cipher" << endl;
    cout << "8-RSA Algorithm " << endl;
    cout << "9-AES" << endl;
    cout << "0-Exit" << endl;
    cin >> choice;

    switch (choice) {
        case 1:
            return new CaesarCipher("", "", 3);  // Example with shift 3
        case 2:
            return new HillCipher("","","hill");
        case 3:
            return new AffineCipher("","",5,8);
        case 4:
            return new VigenereCipher("","","MOM");  // Example key
        case 5:
            return new RailFenceCipher("", "", 3);
        case 6:
            return new monoalphabetic("", "", "mnbvcxzlkjhgfdsapoiuytrewq");  // Example key
        case 7:
            return new VernamCipher("", "", "MYNAMEISNOO");  // Example key
        case 8:
            return new RSA("", "", 61, 53, 17);  // Example keys
        case 9: {
            std::vector<std::vector<int>> key = {
                {0x2b, 0x28, 0xab, 0x09},
                {0x7e, 0xae, 0xf7, 0xcf},
                {0x15, 0xd2, 0x15, 0x4f},
                {0x16, 0xa6, 0x88, 0x3c}
            };
            return new AES("", "", key);
        }
        case 0:
            exit(0);
            break;
        default:
            cout << "Invalid input" << endl;
            break;
    }

    return nullptr;
}

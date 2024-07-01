#include "TextCryptography.h"
#include "CipherInput.h"
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
        cout << "3-Go back" << endl;
        cin >> choice;

        if (choice == 3) {
            return ;
        }

        cin.ignore(); 
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
        throw;  
    }

    delete cipher; 
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
        throw; 
    }

    delete cipher; 
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
    cout << "0-Go back" << endl;
    cin >> choice;
    int keyT1,keyT3,keyT5;
    string keyT2,keyT4,keyT6;
    vector<long long> keyT8;
    vector<vector<int>> keyT9;

    CipherInput obj;

    switch (choice) {
        case 1:
            cout << "Selected Caesar Cipher" << endl;
            keyT1= obj.getCaesarCipherKey();
            return new CaesarCipher("", "", keyT1); 
        case 2:
            cout << "Selected Hill Cipher" << endl;
            keyT2 = obj.getHillCipherKey();
            return new HillCipher("","",keyT2);
        case 3:
            cout << "Selected Affine Cipher" << endl;
            keyT3 = obj.getAffineCipherKey();
            return new AffineCipher("","",keyT3 / 100,keyT3 % 100);
        case 4:
            cout << "Selected Vigenère Cipher" << endl;
            keyT4 = obj.getVigenereCipherKey();
            return new VigenereCipher("","",keyT4); 
        case 5:
            cout << "Selected Rail Fence Cipher" << endl;
            keyT5 = obj.getRailFenceCipherKey();
            return new RailFenceCipher("", "", keyT5);
        case 6:
             cout << "Selected Monoalphabetic Cipher" << endl;
             keyT6 = obj.getMonoalphabeticCipherKey();
            return new monoalphabetic("", "", keyT6); 
        case 7:
            cout << "Selected Vernam Cipher" << endl;
            return new VernamCipher("", "");  
        case 8:
            cout << "Selected RSA Algorithm" << endl;
            keyT8 = obj.getRSACipherKey();
            return new RSA("", "", keyT8[0], keyT8[1], keyT8[2]);  
        case 9: {
            cout << "Selected Advanced Encryption Standard (AES)" << endl;
            keyT9 =obj.getAESCipherKey();
            return new AES("", "", keyT9);
        }
        case 0:
            processText();
            break;
        default:
            cout << "Invalid input" << endl;
            break;
    }

    return nullptr;
}

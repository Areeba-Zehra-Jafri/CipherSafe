#include "FileCryptography.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <numeric> // for std::gcd

using namespace std;

void FileCryptography::processFiles() {
    int choice;
    string inputFilePath, outputFilePath;

    while (true) {
        cout << "1-Encrypt a file" << endl;
        cout << "2-Decrypt a file" << endl;
        cout << "3-Exit" << endl;
        cin >> choice;

        if (choice == 3) {
            exit(0);
        }

        cout << "Enter the input file path: ";
        cin >> inputFilePath;
        cout << "Enter the output file path: ";
        cin >> outputFilePath;

        switch (choice) {
            case 1:
                encryptFile(inputFilePath, outputFilePath);
                break;
            case 2:
                decryptFile(inputFilePath, outputFilePath);
                break;
            default:
                cout << "Invalid input" << endl;
                break;
        }
    }
}

void FileCryptography::encryptFile(const string& inputFilePath, const string& outputFilePath) {
    ifstream inputFile(inputFilePath);
    if (!inputFile) {
        cerr << "Error opening input file: " << inputFilePath << endl;
        return;
    }

    ofstream outputFile(outputFilePath);
    if (!outputFile) {
        cerr << "Error creating output file: " << outputFilePath << endl;
        return;
    }

    Cryptography* cipher = selectCipher();
    if (!cipher) {
        return;  // User did not select a valid cipher
    }

    string line;
    while (getline(inputFile, line)) {
        cipher->set_plaintext(line);
        string encryptedLine = cipher->encrypt();
        outputFile << encryptedLine << endl;
    }

    inputFile.close();
    outputFile.close();

    delete cipher;  // Clean up dynamically allocated memory
}

void FileCryptography::decryptFile(const string& inputFilePath, const string& outputFilePath) {
    ifstream inputFile(inputFilePath);
    if (!inputFile) {
        cerr << "Error opening input file: " << inputFilePath << endl;
        return;
    }

    ofstream outputFile(outputFilePath);
    if (!outputFile) {
        cerr << "Error creating output file: " << outputFilePath << endl;
        return;
    }

    Cryptography* cipher = selectCipher();
    if (!cipher) {
        return;  // User did not select a valid cipher
    }

    string line;
    while (getline(inputFile, line)) {
        cout << "Decrypting line: " << line << endl;  // Debug: Show line to be decrypted
        cipher->set_ciphertext(line);
        string decryptedLine = cipher->decrypt();
        cout << "Decrypted line: " << decryptedLine << endl;  // Debug: Show decrypted line
        outputFile << decryptedLine << endl;
    }

    inputFile.close();
    outputFile.close();

    delete cipher;  // Clean up dynamically allocated memory
}


Cryptography* FileCryptography::selectCipher() {
    int choice;
    cout << "1-Caesar Cipher" << endl;
    cout << "2-Hill Cipher" << endl;
    cout << "3-Affine Cipher" << endl;
    cout << "4-Vigenère Cipher" << endl;
    cout << "5-Rail Fence Cipher" << endl;
    cout << "6-Monoalphabetic Cipher" << endl;
    cout << "7-Vernam Cipher" << endl;
    cout << "8-RSA Algorithm " << endl;
    cout << "9-AES" << endl;
    cout << "0-Exit" << endl;
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "Selected Caesar Cipher" << endl;
            return new CaesarCipher("", "", 3);  // Example with shift 3
        case 2:
            cout << "Selected Hill Cipher" << endl;
            return new HillCipher("","","cfik");
        case 3:
            cout << "Selected Affine Cipher" << endl;
            return new AffineCipher("","",5,8);
        case 4:
            cout << "Selected Vigenère Cipher" << endl;
           // return new VigenereCipher("", "", "KEY");  // Example key
        case 5:
            cout << "Selected Rail Fence Cipher" << endl;
            return new RailFenceCipher("", "", 3);
        case 6:
             cout << "Selected Monoalphabetic Cipher" << endl;
            // return new MonoalphabeticCipher("", "", "ZYXWVUTSRQPONMLKJIHGFEDCBA");  // Example key
        case 7:
            cout << "Selected Vernam Cipher" << endl;
            return new VernamCipher("", "", "MYNAMEISNOO");  // Example key
        case 8:
            cout << "Selected RSA Algorithm" << endl;
            return new RSA("", "", 61, 53, 17);  // Example keys
        case 9: {
            cout << "Selected Advanced Encryption Standard (AES)" << endl;
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
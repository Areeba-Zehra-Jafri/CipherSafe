#include "FileCryptography.h"
#include "CipherInput.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <numeric> 

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
                try {
                    encryptFile(inputFilePath, outputFilePath);
                } catch (const exception& e) {
                    cerr << "Encryption Error: " << e.what() << endl;
                }
                break;
            case 2:
                try {
                    decryptFile(inputFilePath, outputFilePath);
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

void FileCryptography::encryptFile(const string& inputFilePath, const string& outputFilePath) {
    ifstream inputFile(inputFilePath);
    if (!inputFile) {
        throw runtime_error("Error opening input file: " + inputFilePath);
    }

    ofstream outputFile(outputFilePath);
    if (!outputFile) {
        inputFile.close();
        throw runtime_error("Error creating output file: " + outputFilePath);
    }

    Cryptography* cipher = selectCipher();
    if (!cipher) {
        inputFile.close();
        outputFile.close();
        throw runtime_error("Invalid cipher selection.");
    }

    try {
        string line;
        while (getline(inputFile, line)) {
            cipher->set_plaintext(line);
            string encryptedLine = cipher->encrypt();
            outputFile << encryptedLine << endl;
        }
    } catch (const exception& e) {
        delete cipher;
        inputFile.close();
        outputFile.close();
        throw;  // Re-throw exception for outer handling
    }

    delete cipher;  // Clean up dynamically allocated memory
    inputFile.close();
    outputFile.close();
}

void FileCryptography::decryptFile(const string& inputFilePath, const string& outputFilePath) {
    ifstream inputFile(inputFilePath);
    if (!inputFile) {
        throw runtime_error("Error opening input file: " + inputFilePath);
    }

    ofstream outputFile(outputFilePath);
    if (!outputFile) {
        inputFile.close();
        throw runtime_error("Error creating output file: " + outputFilePath);
    }

    Cryptography* cipher = selectCipher();
    if (!cipher) {
        inputFile.close();
        outputFile.close();
        throw runtime_error("Invalid cipher selection.");
    }

    try {
        string line;
        while (getline(inputFile, line)) {
            cout << "Decrypting line: " << line << endl;  // Debug: Show line to be decrypted
            cipher->set_ciphertext(line);
            string decryptedLine = cipher->decrypt();
            cout << "Decrypted line: " << decryptedLine << endl;  // Debug: Show decrypted line
            outputFile << decryptedLine << endl;
        }
    } catch (const exception& e) {
        delete cipher;
        inputFile.close();
        outputFile.close();
        throw;  // Re-throw exception for outer handling
    }

    delete cipher;  // Clean up dynamically allocated memory
    inputFile.close();
    outputFile.close();
}

Cryptography* FileCryptography::selectCipher() {
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
    int key1,key3,key5;
    string key2,key4,key6,key7;
    vector<long long> key8;
    vector<vector<int>> key9;

    CipherInput obj;

    switch (choice) {
        case 1:
            cout << "Selected Caesar Cipher" << endl;
            key1= obj.getCaesarCipherKey();
            return new CaesarCipher("", "", key1);  // Example with shift 3
        case 2:
            cout << "Selected Hill Cipher" << endl;
            key2 = obj.getHillCipherKey();
            return new HillCipher("","",key2);
        case 3:
            cout << "Selected Affine Cipher" << endl;
            key3 = obj.getAffineCipherKey();
            return new AffineCipher("","",key3 / 100,key3 % 100);
        case 4:
            cout << "Selected Vigenère Cipher" << endl;
            key4 = obj.getVigenereCipherKey();
            return new VigenereCipher("","",key4);  // Example key
        case 5:
            cout << "Selected Rail Fence Cipher" << endl;
            key5 = obj.getRailFenceCipherKey();
            return new RailFenceCipher("", "", key5);
        case 6:
             cout << "Selected Monoalphabetic Cipher" << endl;
             key6 = obj.getMonoalphabeticCipherKey();
            return new monoalphabetic("", "", key6);  // Example key
        case 7:
            cout << "Selected Vernam Cipher" << endl;
           // key7 =obj.getVernamCipherKey();
            return new VernamCipher("", "");  // Example key
        case 8:
            cout << "Selected RSA Algorithm" << endl;
            key8 = obj.getRSACipherKey();
            return new RSA("", "", key8[0], key8[1], key8[2]);  // Example keys
        case 9: {
            cout << "Selected Advanced Encryption Standard (AES)" << endl;
            key9 =obj.getAESCipherKey();
            return new AES("", "", key9);
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

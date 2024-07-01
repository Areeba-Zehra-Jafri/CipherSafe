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
        cout << "3-Go back" << endl;
        cin >> choice;

        if (choice == 3) {
            return ;
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
            cout << "Encrypted line" << encryptedLine << endl;
            outputFile << encryptedLine << endl;
        }
    } catch (const exception& e) {
        delete cipher;
        inputFile.close();
        outputFile.close();
        throw;  
    }

    delete cipher; 
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
            cipher->set_ciphertext(line);
            string decryptedLine = cipher->decrypt();
            cout << "Decrypted line: " << decryptedLine << endl;  
            outputFile << decryptedLine << endl;
        }
    } catch (const exception& e) {
        delete cipher;
        inputFile.close();
        outputFile.close();
        throw;  
    }

    delete cipher;  
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
    cout << "0-Go back" << endl;
    cin >> choice;
    int key1,key3,key5;
    string key2,key4,key6;
    vector<long long> key8;
    vector<vector<int>> key9;

    CipherInput obj;

    switch (choice) {
        case 1:
            cout << "Selected Caesar Cipher" << endl;
            key1= obj.getCaesarCipherKey();
            return new CaesarCipher("", "", key1);
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
            return new VigenereCipher("","",key4);  
        case 5:
            cout << "Selected Rail Fence Cipher" << endl;
            key5 = obj.getRailFenceCipherKey();
            return new RailFenceCipher("", "", key5);
        case 6:
             cout << "Selected Monoalphabetic Cipher" << endl;
             key6 = obj.getMonoalphabeticCipherKey();
            return new monoalphabetic("", "", key6); 
        case 7:
            cout << "Selected Vernam Cipher" << endl;
            return new VernamCipher("", "");  
        case 8:
            cout << "Selected RSA Algorithm" << endl;
            key8 = obj.getRSACipherKey();
            return new RSA("", "", key8[0], key8[1], key8[2]);  
        case 9: {
            cout << "Selected Advanced Encryption Standard (AES)" << endl;
            key9 =obj.getAESCipherKey();
            return new AES("", "", key9);
        }
        case 0:
            processFiles();
            break;
        default:
            cout << "Invalid input" << endl;
            break;
    }

    return nullptr;
}

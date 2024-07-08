#include "FileCryptography.h"
#include "CipherInput.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <numeric>

using namespace std;

void FileCryptography::processFiles()
{
    int choice;
    string inputFilePath, outputFilePath;

    while (true)
    {
        cout << "----------------------------------------" << endl;
        cout << "1-Encrypt a file" << endl;
        cout << "2-Decrypt a file" << endl;
        cout << "3-Encrypt and Decrypt a file" <<endl;
        cout << "4-Go back" << endl;
        cout << "----------------------------------------" << endl;
        cin >> choice;

        if (choice == 4)
        {
            return;
        }

        cout << "----------------------------------------" << endl;
        cout << "Enter the input file path: ";
        cin >> inputFilePath;
        cout << "Enter the output file path: ";
        cin >> outputFilePath;
        cout << "----------------------------------------" << endl;

        switch (choice)
        {
        case 1:
            try
            {
                encryptFile(inputFilePath, outputFilePath);
                Stats.updateFilesEncrypted(Stats.getCurrentUsername());
            }
            catch (const exception &e)
            {
                cerr << "\033[1;31mEncryption Error:\033[0m " << e.what() << endl;
            }
            break;
        case 2:
            try
            {
                decryptFile(inputFilePath, outputFilePath);
                Stats.updateFilesDecrypted(Stats.getCurrentUsername());
            }
            catch (const exception &e)
            {
                cerr << "\033[1;31mDecryption Error: \033[0m" << e.what() << endl;
            }
            break;
        case 3:
            try
            {
                EncryptDecryptFile(inputFilePath, outputFilePath);
                Stats.updateFilesEncrypted(Stats.getCurrentUsername());
                Stats.updateFilesDecrypted(Stats.getCurrentUsername());
            }
            catch (const exception &e)
            {
                cerr << "\033[1;31mEncryption and Decryption Error: \033[0m" << e.what() << endl;
            }
            break;
        default:
            cout << "033[1;31mInvalid input\033[0m" << endl;
            break;
        }
    }
}

void FileCryptography::EncryptDecryptFile(const string &inputFilePath, const string &outputFilePath)
{
    string finalFile;
    cout << "Enter the final output file path: ";
    cin >> finalFile;
    cout << "----------------------------------------" << endl;

    ifstream inputFile(inputFilePath);
    if (!inputFile)
    {
        throw runtime_error("\033[1;31mError opening input file: " + inputFilePath + "\033[0m");
    }

    ofstream outputFile(outputFilePath);
    if (!outputFile)
    {
        inputFile.close();
        throw runtime_error("\033[1;31mError creating output file: " + outputFilePath + "\033[0m");
    }

    Cryptography *cipher = selectCipher();
    if (!cipher)
    {
        inputFile.close();
        outputFile.close();
        throw runtime_error("\033[1;31mInvalid cipher selection.\033[0m");
    }

    try
    {
        string line;
        while (getline(inputFile, line))
        {
            cipher->set_plaintext(line);
            string encryptedLine = cipher->encrypt();
            cout << "----------------------------------------" << endl;
            cout << "Encrypted line: " << encryptedLine << endl;
            cout << "----------------------------------------" << endl;
            outputFile << encryptedLine << endl;
        }
    }
    catch (const exception &e)
    {
        delete cipher;
        inputFile.close();
        outputFile.close();
        throw;
    }

    inputFile.close();
    outputFile.close();

    ifstream inputFile2(outputFilePath);
    if (!inputFile2)
    {
        throw runtime_error("\033[1;31mError opening input file: " + outputFilePath + "\033[0m");
    }

    ofstream outputFile2(finalFile);
    if (!outputFile2)
    {
        inputFile2.close();
        throw runtime_error("\033[1;31mError creating final output file: " + finalFile + "\033[0m");
    }

    try
    {
        string line;
        while (getline(inputFile2, line))
        {
            cipher->set_ciphertext(line);
            string decryptedLine = cipher->decrypt();
            cout << "----------------------------------------" << endl;
            cout << "Decrypted line: " << decryptedLine << endl;
            cout << "----------------------------------------" << endl;
            outputFile2 << decryptedLine << endl;
        }
    }
    catch (const exception &e)
    {
        delete cipher;
        inputFile2.close();
        outputFile2.close();
        throw;
    }

    delete cipher;
    inputFile2.close();
    outputFile2.close();
}

void FileCryptography::encryptFile(const string &inputFilePath, const string &outputFilePath)
{
    ifstream inputFile(inputFilePath);
    if (!inputFile)
    {
        throw runtime_error("\033[1;31mError opening input file: " + inputFilePath + "\033[0m");
    }

    ofstream outputFile(outputFilePath);
    if (!outputFile)
    {
        inputFile.close();
        throw runtime_error("\033[1;31mError creating output file: " + outputFilePath + "\033[0m");
    }

    Cryptography *cipher = selectCipher();
    if (!cipher)
    {
        inputFile.close();
        outputFile.close();
        throw runtime_error("\033[1;31mInvalid cipher selection.\033[0m");
    }

    try
    {
        string line;
        while (getline(inputFile, line))
        {
            cipher->set_plaintext(line);
            string encryptedLine = cipher->encrypt();
            cout << "----------------------------------------" << endl;
            cout << "Encrypted line: " << encryptedLine << endl;
            cout << "----------------------------------------" << endl;
            outputFile << encryptedLine << endl;
        }
    }
    catch (const exception &e)
    {
        delete cipher;
        inputFile.close();
        outputFile.close();
        throw;
    }

    delete cipher;
    inputFile.close();
    outputFile.close();
}

void FileCryptography::decryptFile(const string &inputFilePath, const string &outputFilePath)
{
    ifstream inputFile(inputFilePath);
    if (!inputFile)
    {
        throw runtime_error("\033[1;31mError opening input file:" + inputFilePath + "\033[0m");
    }

    ofstream outputFile(outputFilePath);
    if (!outputFile)
    {
        inputFile.close();
        throw runtime_error("\033[1;31mError creating output file: " + outputFilePath + "\033[0m ");
    }

    Cryptography *cipher = selectCipher();
    if (!cipher)
    {
        inputFile.close();
        outputFile.close();
        throw runtime_error("\033[1;31mInvalid cipher selection.\033[0m");
    }

    try
    {
        string line;
        while (getline(inputFile, line))
        {
            cipher->set_ciphertext(line);
            string decryptedLine = cipher->decrypt();
            cout << "----------------------------------------" << endl;
            cout << "Decrypted line: " << decryptedLine << endl;
            cout << "----------------------------------------" << endl;
            outputFile << decryptedLine << endl;
        }
    }
    catch (const exception &e)
    {
        delete cipher;
        inputFile.close();
        outputFile.close();
        throw;
    }

    delete cipher;
    inputFile.close();
    outputFile.close();
}

Cryptography *FileCryptography::selectCipher()
{
    int choice;
    cout << "----------------------------------------" << endl;
    cout << "1-Caesar Cipher" << endl;
    cout << "2-Hill Cipher" << endl;
    cout << "3-Affine Cipher" << endl;
    cout << "4-Vigenere Cipher" << endl;
    cout << "5-Rail Fence Cipher" << endl;
    cout << "6-Monoalphabetic Cipher" << endl;
    cout << "7-Vernam Cipher" << endl;
    cout << "8-RSA Algorithm" << endl;
    cout << "9-AES" << endl;
    cout << "0-Go back" << endl;
    cout << "----------------------------------------" << endl;
    cin >> choice;
    int key1, key3, key5;
    string key2, key4, key6, key7;
    vector<long long> key8;
    vector<vector<int>> key9;

    CipherInput obj;

    switch (choice)
    {
    case 1:
        cout << "----------------------------------------" << endl;
        cout << "Selected Caesar Cipher" << endl;
        cout << "----------------------------------------" << endl;
        key1 = obj.getCaesarCipherKey();
        return new CaesarCipher("", "", key1);
    case 2:
        cout << "----------------------------------------" << endl;
        cout << "Selected Hill Cipher" << endl;
        cout << "----------------------------------------" << endl;
        key2 = obj.getHillCipherKey();
        return new HillCipher("", "", key2);
    case 3:
        cout << "----------------------------------------" << endl;
        cout << "Selected Affine Cipher" << endl;
        cout << "----------------------------------------" << endl;
        key3 = obj.getAffineCipherKey();
        return new AffineCipher("", "", key3 / 100, key3 % 100);
    case 4:
        cout << "----------------------------------------" << endl;
        cout << "Selected Vigenere Cipher" << endl;
        cout << "----------------------------------------" << endl;
        key4 = obj.getVigenereCipherKey();
        return new VigenereCipher("", "", key4);
    case 5:
        cout << "----------------------------------------" << endl;
        cout << "Selected Rail Fence Cipher" << endl;
        cout << "----------------------------------------" << endl;
        key5 = obj.getRailFenceCipherKey();
        return new RailFenceCipher("", "", key5);
    case 6:
        cout << "----------------------------------------" << endl;
        cout << "Selected Monoalphabetic Cipher" << endl;
        cout << "----------------------------------------" << endl;
        key6 = obj.getMonoalphabeticCipherKey();
        return new monoalphabetic("", "", key6);
    case 7:
        cout << "----------------------------------------" << endl;
        cout << "Selected Vernam Cipher" << endl;
        cout << "----------------------------------------" << endl;
        key7 = obj.getVernamCipherKey();
        return new VernamCipher("", "", key7);
    case 8:
        cout << "----------------------------------------" << endl;
        cout << "Selected RSA Algorithm" << endl;
        cout << "----------------------------------------" << endl;
        key8 = obj.getRSACipherKey();
        return new RSA("", "", key8[0], key8[1], key8[2]);
    case 9:
    {
        cout << "----------------------------------------" << endl;
        cout << "Selected Advanced Encryption Standard (AES)" << endl;
        cout << "----------------------------------------" << endl;
        key9 = obj.getAESCipherKey();
        return new AES("", "", key9);
    }
    case 0:
        processFiles();
        break;
    default:
        cout << "\033[1;31mInvalid input\033[0m" << endl;
        break;
    }

    return nullptr;
}

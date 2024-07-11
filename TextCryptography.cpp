#include "TextCryptography.h"
#include "CipherInput.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib> // For srand and rand
#include <ctime>   // For time

using namespace std;

void TextCryptography::processText()
{
    int choice;

    while (true)
    {
        cout << "---------------------------------------" << endl;
        cout << "1-Encrypt text" << endl;
        cout << "2-Decrypt text" << endl;
        cout << "3-Encrypt and Decrypt text" << endl;
        cout << "4-Go back" << endl;
        cout << "---------------------------------------" << endl;
        cin >> choice;

        if (choice == 4)
        {
            return;
        }

        cin.ignore();

        switch (choice)
        {
        case 1:
            try
            {
                encryptText();
                Stats.updateTextLinesEncrypted(Stats.getCurrentUsername());
            }
            catch (const exception &e)
            {
                cerr << "\033[1;31mEncryption Error:\033[0m " << e.what() << endl;
            }
            break;
        case 2:
            try
            {
                decryptText();
                Stats.updateTextLinesDecrypted(Stats.getCurrentUsername());
            }
            catch (const exception &e)
            {
                cerr << "\033[1;31mDecryption Error:\033[0m " << e.what() << endl;
            }
            break;
        case 3:
            try
            {
                EncryptDecryptText();
                Stats.updateTextLinesEncrypted(Stats.getCurrentUsername());
                Stats.updateTextLinesDecrypted(Stats.getCurrentUsername());
            }
            catch (const exception &e)
            {
                cerr << "\033[1;31mEncryption , Decryption Error:\033[0m " << e.what() << endl;
            }
            break;
        default:
            cout << "\033[1;31mInvalid input\033[0m" << endl;
            break;
        }
    }
}

void TextCryptography::EncryptDecryptText()
{
    Cryptography *cipher = selectCipher();
    if (!cipher)
    {
        throw runtime_error("\033[1;31mInvalid cipher selection.\033[0m");
    }
    try
    {
        string text = cipher->get_plaintext();
        cipher->set_plaintext(text);
        string encryptedText = cipher->encrypt();
        cout << "-------------------" << endl;
        cout << "Encrypted text: " << encryptedText << endl;
        cout << "-------------------" << endl;
        cipher->set_ciphertext(encryptedText);
        string decryptedText = cipher->decrypt();
        cout << "-------------------" << endl;
        cout << "Decrypted text: " << decryptedText << endl;
        cout << "-------------------" << endl;
    }
    catch (const exception &e)
    {
        delete cipher;
        throw;
    }

    delete cipher;
}

void TextCryptography::encryptText()
{
    Cryptography *cipher = selectCipher();
    if (!cipher)
    {
        throw runtime_error("\033[1;31mInvalid cipher selection.\033[0m");
    }

    try
    {
        string text = cipher->get_plaintext();
        cipher->set_plaintext(text);
        string encryptedText = cipher->encrypt();
        cout << "-------------------" << endl;
        cout << "Encrypted text: " << encryptedText << endl;
        cout << "-------------------" << endl;
    }
    catch (const exception &e)
    {
        delete cipher;
        throw;
    }

    delete cipher;
}

void TextCryptography::decryptText()
{
    Cryptography *cipher = selectCipher();
    if (!cipher)
    {
        throw runtime_error("\033[1;31mInvalid cipher selection.\033[0m");
    }

    try
    {
        string text = cipher->get_ciphertext();
        cipher->set_ciphertext(text);
        string decryptedText = cipher->decrypt();
        cout << "-------------------" << endl;
        cout << "Decrypted text: " << decryptedText << endl;
        cout << "-------------------" << endl;
    }
    catch (const exception &e)
    {
        delete cipher;
        throw;
    }

    delete cipher;
}

Cryptography *TextCryptography::selectCipher()
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
    cout << "8-RSA Algorithm " << endl;
    cout << "9-AES" << endl;
    cout << "0-Go back" << endl;
    cout << "----------------------------------------" << endl;
    cin >> choice;
    int keyT1, keyT3, keyT5;
    string keyT2, keyT4, keyT6, keyT7;
    vector<long long> keyT8;
    vector<vector<int>> keyT9;

    CipherInput obj;

    switch (choice)
    {
    case 1:
        cout << "----------------------------------------" << endl;
        cout << "Selected Caesar Cipher" << endl;
        cout << "----------------------------------------" << endl;
        keyT1 = obj.getCaesarCipherKey();
        return new CaesarCipher("", "", keyT1);
    case 2:
        cout << "----------------------------------------" << endl;
        cout << "Selected Hill Cipher" << endl;
        cout << "----------------------------------------" << endl;
        keyT2 = obj.getHillCipherKey();
        return new HillCipher("", "", keyT2);
    case 3:
        cout << "----------------------------------------" << endl;
        cout << "Selected Affine Cipher" << endl;
        cout << "----------------------------------------" << endl;
        keyT3 = obj.getAffineCipherKey();
        return new AffineCipher("", "", keyT3 / 100, keyT3 % 100);
    case 4:
        cout << "----------------------------------------" << endl;
        cout << "Selected Vigenere Cipher" << endl;
        cout << "----------------------------------------" << endl;
        keyT4 = obj.getVigenereCipherKey();
        return new VigenereCipher("", "", keyT4);
    case 5:
        cout << "----------------------------------------" << endl;
        cout << "Selected Rail Fence Cipher" << endl;
        cout << "----------------------------------------" << endl;
        keyT5 = obj.getRailFenceCipherKey();
        return new RailFenceCipher("", "", keyT5);
    case 6:
        cout << "----------------------------------------" << endl;
        cout << "Selected Monoalphabetic Cipher" << endl;
        cout << "----------------------------------------" << endl;
        keyT6 = obj.getMonoalphabeticCipherKey();
        return new monoalphabetic("", "", keyT6);
    case 7:
        cout << "----------------------------------------" << endl;
        cout << "Selected Vernam Cipher" << endl;
        cout << "----------------------------------------" << endl;
        keyT7 = obj.getVernamCipherKey();
        return new VernamCipher("", "", keyT7);
    case 8:
        cout << "----------------------------------------" << endl;
        cout << "Selected RSA Algorithm" << endl;
        cout << "----------------------------------------" << endl;
        keyT8 = obj.getRSACipherKey();
        return new RSA("", "", keyT8[0], keyT8[1], keyT8[2]);
    case 9:
    {
        cout << "----------------------------------------" << endl;
        cout << "Selected Advanced Encryption Standard (AES)" << endl;
        cout << "----------------------------------------" << endl;
        keyT9 = obj.getAESCipherKey();
        return new AES("", "", keyT9);
    }
    case 0:
        processText();
        break;
    default:
        cout << "\033[1;31mInvalid input\033[0m" << endl;
        break;
    }

    return nullptr;
}

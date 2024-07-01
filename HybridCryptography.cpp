#include "HybridCryptography.h"
#include "CipherInput.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib> // For srand and rand
#include <ctime>   // For time

using namespace std;

void HybridCryptography::processTextHybrid()
{
    while (1)
    {
        int subChoice;
        cout << "----------------------------------------" << endl;
        cout << "1-Encrypt and Embed Text" << endl;
        cout << "2-Extract and Decrypt Text" << endl;
        cout << "3-Go back" << endl;
        cout << "----------------------------------------" << endl;
        cin >> subChoice;

        switch (subChoice)
        {
        case 1:
            encryptAndEmbedText();
            break;
        case 2:
            extractAndDecryptText();
            break;
        case 3:
            return;
        default:
            cout << "\033[1;31mInvalid input\033[0m" << endl;
            break;
        }
    }
}

void HybridCryptography::encryptAndEmbedText()
{
    string text, inputImage, outputImage;
    cout << "----------------------------------------" << endl;
    cout << "Enter the text to encrypt and embed: ";
    cin.ignore();
    getline(cin, text);

    Cryptography *cipher = selectTextCipher();
    if (!cipher)
    {
        cerr << "\033[1;31mInvalid cipher selection.\033[0m" << endl;
        return;
    }

    string encryptedText;
    try
    {
        cipher->set_plaintext(text);
        encryptedText = cipher->encrypt();
        cout << "--------------------------" << endl;
        cout << "Encrypted Text:" << encryptedText << endl;
        cout << "--------------------------" << endl;
        delete cipher;
    }
    catch (const exception &e)
    {
        cerr << "\033[1;31mEncryption Error: \033[0m" << e.what() << endl;
        delete cipher;
        return;
    }

    cin.ignore(); // Ignore newline left in input buffer after cin >>
    cout << "----------------------------------------" << endl;
    cout << "Enter the path of the input image: ";
    cin >> inputImage;

    cout << "Enter the path of the output image: ";
    cin >> outputImage;
    cout << "----------------------------------------" << endl;
    std::cin.ignore();
    try
    {
        stego.hideMessage(inputImage, outputImage, encryptedText);
    }
    catch(const std::exception& e)
    {
        return;
    }
    

     std::cout << "\n\033[1;34m---------------------------\n";
    cout << "Text encrypted and embedded successfully!" << endl;
     cout << "\n---------------------------\033[0m\n";
}

void HybridCryptography::extractAndDecryptText()
{
    string inputImage, extractedMessage;
    cout << "----------------------------------------" << endl;
    cout << "Enter the path of the steganographic image: ";
    cout << "----------------------------------------" << endl;
    cin.ignore(); // Ignore any newline characters left in the input buffer
    getline(cin, inputImage);

    // Extract message from image
    try
    {
        extractedMessage = stego.extractMessage(inputImage);
    }
    catch(const std::exception& e)
    {
        return;
    }
    
    cout << "----------------------------------------" << endl;
    cout << "Extracted Message: " << extractedMessage << endl;
    cout << "----------------------------------------" << endl;
    // Decrypt extracted message
    Cryptography *cipher = selectTextCipher();
    if (!cipher)
    {
        cerr << "\033[1;31mInvalid cipher selection.\033[0m" << endl;
        return;
    }

    string decryptedText;
    try
    {
        cipher->set_ciphertext(extractedMessage);
        decryptedText = cipher->decrypt();
        delete cipher;
    }
    catch (const exception &e)
    {
        cerr << "\033[1;31mDecryption Error:\033[0m " << e.what() << endl;
        delete cipher;
        return;
    }
    cout << "-------------------------------" << endl;
    cout << "Extracted and decrypted text: " << decryptedText << endl;
}

Cryptography *HybridCryptography::selectTextCipher()
{
    int choice;
    cout << "----------------------------------------" << endl;
    cout << "Select a cipher for text processing:" << endl;
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
    int keyF1, keyF3, keyF5;
    string keyF2, keyF4, keyF6,keyF7;
    vector<long long> keyF8;
    vector<vector<int>> keyF9;
    CipherInput obj;

    switch (choice)
    {
    case 1:
        cout << "----------------------------------------" << endl;
        cout << "Selected Caesar Cipher" << endl;
        cout << "----------------------------------------" << endl;
        keyF1 = obj.getCaesarCipherKey();
        return new CaesarCipher("", "", keyF1); 
    case 2:
        cout << "----------------------------------------" << endl;
        cout << "Selected Hill Cipher" << endl;
        cout << "----------------------------------------" << endl;
        keyF2 = obj.getHillCipherKey();
        return new HillCipher("", "", keyF2);
    case 3:
        cout << "----------------------------------------" << endl;
        cout << "Selected Affine Cipher" << endl;
        cout << "----------------------------------------" << endl;
        keyF3 = obj.getAffineCipherKey();
        return new AffineCipher("", "", keyF3 / 100, keyF3 % 100);
    case 4:
        cout << "----------------------------------------" << endl;
        cout << "Selected Vigenere Cipher" << endl;
        cout << "----------------------------------------" << endl;
        keyF4 = obj.getVigenereCipherKey();
        return new VigenereCipher("", "", keyF4); 
    case 5:
        cout << "----------------------------------------" << endl;
        cout << "Selected Rail Fence Cipher" << endl;
        cout << "----------------------------------------" << endl;
        keyF5 = obj.getRailFenceCipherKey();
        return new RailFenceCipher("", "", keyF5);
    case 6:
        cout << "----------------------------------------" << endl;
        cout << "Selected Monoalphabetic Cipher" << endl;
        cout << "----------------------------------------" << endl;
        keyF6 = obj.getMonoalphabeticCipherKey();
        return new monoalphabetic("", "", keyF6); 
    case 7:
        cout << "----------------------------------------" << endl;
        cout << "Selected Vernam Cipher" << endl;
        cout << "----------------------------------------" << endl;
        keyF7= obj.getVernamCipherKey();
        return new VernamCipher("", "",keyF7);
    case 8:
        cout << "----------------------------------------" << endl;
        cout << "Selected RSA Algorithm" << endl;
        cout << "----------------------------------------" << endl;
        keyF8 = obj.getRSACipherKey();
        return new RSA("", "", keyF8[0], keyF8[1], keyF8[2]); 
    case 9:
    {
        cout << "----------------------------------------" << endl;
        cout << "Selected Advanced Encryption Standard (AES)" << endl;
        cout << "----------------------------------------" << endl;
        keyF9 = obj.getAESCipherKey();
        return new AES("", "", keyF9);
    }
    case 0:
        processTextHybrid();
    default:
        cout << "\033[1;31mInvalid input\033[0m" << endl;
        break;
    }

    return nullptr;
}

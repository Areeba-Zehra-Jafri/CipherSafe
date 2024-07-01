#include "HybridCryptography.h"
#include "CipherInput.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib> // For srand and rand
#include <ctime>   // For time

using namespace std;

void HybridCryptography::processTextHybrid() {
    while(1)
    {
        int subChoice;
        cout << "1-Encrypt and Embed Text" << endl;
        cout << "2-Extract and Decrypt Text" << endl;
        cout << "3-Go back"<<endl; 
        cin >> subChoice;

        switch (subChoice) {
            case 1:
                encryptAndEmbedText();
                break;
            case 2:
                extractAndDecryptText();
                break;
            case 3:
                return ;
            default:
                cout << "Invalid input" << endl;
                break;
        }
    }
}

void HybridCryptography::encryptAndEmbedText() {
    string text,inputImage,outputImage;
    cout << "Enter the text to encrypt and embed: ";
    cin.ignore(); 
    getline(cin, text);

    Cryptography* cipher = selectTextCipher();
    if (!cipher) {
        cerr << "Invalid cipher selection." << endl;
        return;
    }

    string encryptedText;
    try {
        cipher->set_plaintext(text);
        encryptedText = cipher->encrypt();
        cout<<"Encrypted Text:"<<encryptedText<<endl;
        delete cipher;
    } catch (const exception& e) {
        cerr << "Encryption Error: " << e.what() << endl;
        delete cipher;
        return;
    }

    std::cin.ignore(); // Ignore newline left in input buffer after cin >>

        std::cout << "Enter the path of the input image: ";
        std::cin >> inputImage;

        std::cout << "Enter the path of the output image: ";
        std::cin >> outputImage;
        std::cin.ignore();

    stego.hideMessage(inputImage, outputImage, encryptedText);
    cout << "Text encrypted and embedded successfully!" << endl;
}

void HybridCryptography::extractAndDecryptText() {
    string inputImage, extractedMessage;
    cout << "Enter the path of the steganographic image: ";
    cin.ignore(); // Ignore any newline characters left in the input buffer
    getline(cin, inputImage);

    // Extract message from image
    extractedMessage = stego.extractMessage(inputImage);
    cout<<"Extracted Message"<<extractedMessage<<endl;
    // Decrypt extracted message
    Cryptography* cipher = selectTextCipher();
    if (!cipher) {
        cerr << "Invalid cipher selection." << endl;
        return;
    }

    string decryptedText;
    try {
        cipher->set_ciphertext(extractedMessage);
        decryptedText = cipher->decrypt();
        delete cipher;
    } catch (const exception& e) {
        cerr << "Decryption Error: " << e.what() << endl;
        delete cipher;
        return;
    }

    cout << "Extracted and decrypted text: " << decryptedText << endl;
}

Cryptography* HybridCryptography::selectTextCipher() {
    int choice;
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
    cout << "0-Go back"<<endl;
    cin >> choice;
    int keyF1,keyF3,keyF5;
    string keyF2,keyF4,keyF6;
    vector<long long> keyF8;
    vector<vector<int>> keyF9;
    CipherInput obj;

    switch (choice) {
        case 1:
            cout << "Selected Caesar Cipher" << endl;
            keyF1 = obj.getCaesarCipherKey();
            return new CaesarCipher("", "", keyF1);  // Example with shift 3
        case 2:
            cout << "Selected Hill Cipher" << endl;
            keyF2 = obj.getHillCipherKey();
            return new HillCipher("","",keyF2);
        case 3:
            cout << "Selected Affine Cipher" << endl;
            keyF3 = obj.getAffineCipherKey();
            return new AffineCipher("","",keyF3 / 100,keyF3 % 100);
        case 4:
            cout << "Selected Vigenère Cipher" << endl;
            keyF4 = obj.getVigenereCipherKey();
            return new VigenereCipher("","",keyF4);  // Example key
        case 5:
            cout << "Selected Rail Fence Cipher" << endl;
            keyF5 = obj.getRailFenceCipherKey();
            return new RailFenceCipher("", "", keyF5);
        case 6:
            cout << "Selected Monoalphabetic Cipher" << endl;
            keyF6 = obj.getMonoalphabeticCipherKey();
            return new monoalphabetic("", "", keyF6);  // Example key
        case 7:
            cout << "Selected Vernam Cipher" << endl;
            return new VernamCipher("", "");  // Example key
        case 8:
            cout << "Selected RSA Algorithm" << endl;
            keyF8 = obj.getRSACipherKey();
            return new RSA("", "", keyF8[0], keyF8[1], keyF8[2]);  // Example keys
        case 9: {
            cout << "Selected Advanced Encryption Standard (AES)" << endl;
            keyF9 = obj.getAESCipherKey();
            return new AES("", "", keyF9);
        }
        case 0:
            processTextHybrid();
        default:
            cout << "Invalid input" << endl;
            break;
    }

    return nullptr;
}

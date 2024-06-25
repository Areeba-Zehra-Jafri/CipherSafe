// #include <iostream>

// using namespace std;

// string message;
// string mappedKey;

// void messageAndKey(){
//     string msg;
//     cout << "Enter message: ";
//     getline(cin, msg);
//     cin.ignore();

//     //message to uppercase
//     for(int i = 0; i < msg.length(); i++){
//         msg[i] = toupper(msg[i]);
//     }

//     string key;
//     cout << "Enter key: ";
//     getline(cin, key);
//     cin.ignore();

//     //key to uppercase
//     for(int i = 0; i < key.length(); i++){
//         key[i] = toupper(key[i]);
//     }

//     //mapping key to message
//     string keyMap = "";
//     for (int i = 0,j = 0; i <msg.length();i++){
//         if(msg[i] ==32){
//             keyMap += 32;
//         } else {
//             if(j<key.length()){
//                 keyMap += key[j];
//                 j++;
//             } else {
//                 j = 0;
//                 keyMap += key[j];
//                 j++;
//             }
//         } 
//     } 

// //    cout << msg << "\n" << keyMap;
//     message = msg;
//     mappedKey = keyMap;
// }

// int tableArr[26][26];
// void createVigenereTable(){
//     for (int i = 0; i < 26; i++){
//         for (int j = 0; j < 26; j++){
//             int temp;
//             if((i+65)+j > 90){
//                 temp = ((i+65)+j) - 26;

//                 //adding ASCII of alphabet letter in table index position
//                 tableArr[i][j] = temp;
//             } else {
//                 temp = (i+65)+j;

//                 //adding ASCII of alphabet letter in table index position
//                 tableArr[i][j] = temp;
//             }
//         } // for j loop
//     } // for i loop

//     //testing the table
// //    for(int i = 0; i <26; i++){
// //        for(int j = 0; j < 26; j++){
// //            cout << (char)tableArr[i][j] << " ";
// //        }
// //        cout << endl;
// //    }
// }

// void cipherEncryption(string message, string mappedKey){
//     createVigenereTable();
//     string encryptedText = "";
//     for(int i = 0; i < message.length(); i++){
//         if(message[i] == 32 && mappedKey[i] == 32){
//             encryptedText += " ";
//         } else {
//             int x = (int)message[i]-65;
//             int y = (int)mappedKey[i]-65;
//             encryptedText += (char)tableArr[x][y];
//         }
//     }

//     cout << "Encrypted Text: " << encryptedText;
// }

// int itrCount(int key, int msg){
//     int counter = 0;
//     string result = "";

//     //starting from ASCII of letter of Key and ending at letter of message
//     // to get full 26 letters of alphabet
//     for(int i = 0; i < 26; i++){
//         if(key+i > 90){
//             result += (char)(key+(i-26));
//         } else {
//             result += (char)(key+i);
//         }
//     } //for

//     for(int i = 0; i < result.length(); i++){
//         if(result[i] == msg){
//             break;
//         } else {
//             counter++;
//         }
//     }
//     return counter;
// }


// void cipherDecryption(string message, string mappedKey){
//     string decryptedText = "";
//     for(int i = 0; i < message.length(); i++){
//         if(message[i] == 32 && mappedKey[i] == 32){
//             decryptedText += " ";
//         } else {
//             int temp = itrCount((int)mappedKey[i], (int)message[i]);
//             decryptedText += (char)(65+temp);
//         }
//     }

//     cout << "Decrypted Text: " << decryptedText;
// }


// int main()
// {
//     cout << "Message and key can only be alphabetic" << endl;
//     int choice;
//     cout << "1. Encryption\n2. Decryption\nChoose(1,2): ";
//     cin >> choice;
//     cin.ignore();

//     if (choice == 1){
//         cout << "Encryption" << endl;
//         messageAndKey();
//         cipherEncryption(message, mappedKey);

//     } else if (choice == 2){
//         cout << "Decryption" << endl;
//         messageAndKey();
//         cipherDecryption(message, mappedKey);

//     } else {
//         cout << "Wrong Choice" << endl;
//     }

//     return 0;
// }

// #include <iostream>
// #include <string>
// #include <stdexcept>
// #include "Vernam_Cipher.h"
// using namespace std;

// VernamCipher::VernamCipher(const string plaintext, const string k) : Cryptography(plaintext, ""), key(k) {}

// string VernamCipher::encrypt()
// {

//     if (plaintext.length() != key.length())
//     {
//         throw std::invalid_argument("Key must be the same length as plaintext.");
//     }
//     std::string ciphertext;
//     for (size_t i = 0; i < plaintext.length(); ++i)
//     {
//         ciphertext += (plaintext[i] ^ key[i]);
//     }
//     this->ciphertext=ciphertext;
//     return ciphertext;
// }

// // Decryption function
// string VernamCipher:: decrypt()
// {
//     if (ciphertext.length() != key.length())
//     {
//         throw std::invalid_argument("Key must be the same length as ciphertext.");
//     }
//     std::string plaintext;
//     for (size_t i = 0; i < ciphertext.length(); ++i)
//     {
//         plaintext += ciphertext[i] ^ key[i];
//     }
//     return plaintext;
// }

// string VernamCipher:: get_plain_text()
// {
//     return plaintext;
// }

// string VernamCipher:: get_cipher()
// {
//     return ciphertext;
// }






// #include <iostream>
// #include <string>
// #include <vector>
// #include "vignere.h"

// using namespace std;

//  VigenereCipher::  VigenereCipher(string plain_text,string key):Cryptography(plain_text,""),key(key)


//     int  VigenereCipher::  itrCount(int key, int plain_text) const {
//         int counter = 0;
//         string result = "";

//         for (int i = 0; i < 26; i++) {
//             if (key + i > 90) {
//                 result += (char)(key + (i - 26));
//             } else {
//                 result += (char)(key + i);
//             }
//         }

//         for (size_t i = 0; i < result.length(); i++) { // Use size_t for loop variable
//             if (result[i] == plain_text) {
//                 break;
//             } else {
//                 counter++;
//             }
//         }
//         return counter;
//     }

//     void  VigenereCipher:: createVigenereTable() {
//         tableArr.resize(26, vector<int>(26, 0));

//         // Fill the Vigenere table
//         for (int i = 0; i < 26; i++) {
//             for (int j = 0; j < 26; j++) {
//                 int temp = (i + j) % 26 + 65;
//                 tableArr[i][j] = temp;
//             }
//         }
//     }


    

//     void  VigenereCipher:: setMessageAndKey() {
//         // Convert message to uppercase
//         for (size_t i = 0; i < plain_text.length(); i++) {
//             plain_text[i] = toupper(plain_text[i]);
//         }

//         // Convert key to uppercase
//         for (size_t i = 0; i < key.length(); i++) {
//             key[i] = toupper(key[i]);
//         }

//         // Map key to message length
//         string keyMap = "";
//         for (size_t i = 0, j = 0; i < plain_text.length(); i++) {
//             if (plain_text[i] == ' ') {
//                 keyMap += ' ';
//             } else {
//                 if (j < key.length()) {
//                     keyMap += key[j];
//                     j++;
//                 } else {
//                     j = 0;
//                     keyMap += key[j];
//                     j++;
//                 }
//             }
//         }

//         key = keyMap;
//     }

//     string  VigenereCipher:: encrypt() {
//         string encryptedText = "";
//         for (size_t i = 0; i < plain_text.length(); i++) { // Use size_t for loop variable
//             if (plain_text[i] == ' ' && key[i] == ' ') {
//                 encryptedText += ' ';
//             } else {
//                 int x = (int)plain_text[i] - 65;
//                 int y = (int)key[i] - 65;
//                 encryptedText += (char)tableArr[x][y];
//             }
//         }
//         return encryptedText;
//     }

//     string  VigenereCipher:: decrypt() {
//         string decryptedText = "";
//         for (size_t i = 0; i < plain_text.length(); i++) { // Use size_t for loop variable
//             if (plain_text[i] == ' ' && key[i] == ' ') {
//                 decryptedText += ' ';
//             } else {
//                 int temp = itrCount((int)key[i], (int)plain_text[i]);
//                 decryptedText += (char)(65 + temp);
//             }
//         }
//         return decryptedText;
//     }

#include <iostream>
#include <string>
#include <vector>
#include "vignere.h"

using namespace std;

// Constructor implementation
VigenereCipher::VigenereCipher(string plaintext, string key) : Cryptography(plaintext, ""), plaintext(plaintext), key(key) {
    createVigenereTable();
    setMessageAndKey();
}

// Function to calculate the iteration count
int VigenereCipher ::itrCount(int key, int plain_text) const {
    int counter = 0;
    string result = "";

    for (int i = 0; i < 26; i++) {
        if (key + i > 90) {
            result += (char)(key + (i - 26));
        } else {
            result += (char)(key + i);
        }
    }

    for (size_t i = 0; i < result.length(); i++) {
        if (result[i] == plain_text) {
            break;
        } else {
            counter++;
        }
    }
    return counter;
}

// Function to create the Vigenere table
void VigenereCipher::createVigenereTable() {
    tableArr.resize(26, vector<int>(26, 0));

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            int temp = (i + j) % 26 + 65;
            tableArr[i][j] = temp;
        }
    }
}

// Function to set the message and key
void VigenereCipher::setMessageAndKey() {
    // Convert plaintext to uppercase
    for (size_t i = 0; i < plaintext.length(); i++) {
        plaintext[i] = toupper(plaintext[i]);
    }

    // Convert key to uppercase
    for (size_t i = 0; i < key.length(); i++) {
        key[i] = toupper(key[i]);
    }

    // Map key to the length of the plaintext
    string keyMap = "";
    for (size_t i = 0, j = 0; i < plaintext.length(); i++) {
        if (plaintext[i] == ' ') {
            keyMap += ' ';
        } else {
            if (j < key.length()) {
                keyMap += key[j];
                j++;
            } else {
                j = 0;
                keyMap += key[j];
                j++;
            }
        }
    }

    key = keyMap;
}

// Function to encrypt the plaintext
string VigenereCipher::encrypt() {
    string encryptedText = "";
    for (size_t i = 0; i < plaintext.length(); i++) {
        if (plaintext[i] == ' ') {
            encryptedText += ' ';
        } else {
            int x = (int)plaintext[i] - 65;
            int y = (int)key[i] - 65;
            encryptedText += (char)tableArr[x][y];
        }
    }
    return encryptedText;
}

// Function to decrypt the ciphertext
string VigenereCipher::decrypt() {
    string decryptedText = "";
    for (size_t i = 0; i < plaintext.length(); i++) {
        if (plaintext[i] == ' ') {
            decryptedText += ' ';
        } else {
            int temp = itrCount((int)key[i], (int)plaintext[i]);
            decryptedText += (char)(65 + temp);
        }
    }
    return decryptedText;
}



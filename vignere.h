#ifndef VIGNERECIPHER_H
#define VIGNERECIPHER_H
#include <iostream>
#include <string>
#include <vector>
#include "Cryptography.h"


using namespace std;

class VigenereCipher:public Cryptography {
    public:
    VigenereCipher(string plaintext,string key);
 int itrCount(int key, int plaintext) const ;
    
 void createVigenereTable();
  void setMessageAndKey() ;
   string encrypt() ;
      string decrypt() ;



private:

vector<vector<int>> tableArr;
    string plaintext;
    string key;

};



 #endif
 



//     vector<vector<int>> tableArr;
//     string message;
//     string mappedKey;

//     int itrCount(int key, int msg) const {
//         int counter = 0;
//         string result = "";

//         for (int i = 0; i < 26; i++) {
//             if (key + i > 90) {
//                 result += (char)(key + (i - 26));
//             } else {
//                 result += (char)(key + i);
//             }
//         }

//         for (int i = 0; i < result.length(); i++) {
//             if (result[i] == msg) {
//                 break;
//             } else {
//                 counter++;
//             }
//         }
//         return counter;
//     }

//     void createVigenereTable() {
//         tableArr.resize(26, vector<int>(26, 0));

//         // Fill the Vigenere table
//         for (int i = 0; i < 26; i++) {
//             for (int j = 0; j < 26; j++) {
//                 int temp = (i + j) % 26 + 65;
//                 tableArr[i][j] = temp;
//             }
//         }
//     }

//     // void setMessageAndKey() {
//     //     cout << "Enter message: ";
//     //     getline(cin, message);

//     //     // Convert message to uppercase
//     //     for (int i = 0; i < message.length(); i++) {
//     //         message[i] = toupper(message[i]);
//     //     }

//     //     cout << "Enter key: ";
//     //     getline(cin, mappedKey);

//     //     // Convert key to uppercase
//     //     for (int i = 0; i < mappedKey.length(); i++) {
//     //         mappedKey[i] = toupper(mappedKey[i]);
//     //     }

//     //     // Map key to message length
//     //     string keyMap = "";
//     //     for (int i = 0, j = 0; i < message.length(); i++) {
//     //         if (message[i] == ' ') {
//     //             keyMap += ' ';
//     //         } else {
//     //             if (j < mappedKey.length()) {
//     //                 keyMap += mappedKey[j];
//     //                 j++;
//     //             } else {
//     //                 j = 0;
//     //                 keyMap += mappedKey[j];
//     //                 j++;
//     //             }
//     //         }
//     //     }

//     //     message = message;
//     //     mappedKey = keyMap;
//     // }

// public:
//  VigenereCipher(string plain_text,string key );
//     VigenereCipher() {
//         createVigenereTable();
//     }
//     void setMessageAndKey() {
//         cout << "Enter message: ";
//         getline(cin, message);

//         // Convert message to uppercase
//         for (int i = 0; i < message.length(); i++) {
//             message[i] = toupper(message[i]);
//         }

//         cout << "Enter key: ";
//         getline(cin, mappedKey);

//         // Convert key to uppercase
//         for (int i = 0; i < mappedKey.length(); i++) {
//             mappedKey[i] = toupper(mappedKey[i]);
//         }

//         // Map key to message length
//         string keyMap = "";
//         for (int i = 0, j = 0; i < message.length(); i++) {
//             if (message[i] == ' ') {
//                 keyMap += ' ';
//             } else {
//                 if (j < mappedKey.length()) {
//                     keyMap += mappedKey[j];
//                     j++;
//                 } else {
//                     j = 0;
//                     keyMap += mappedKey[j];
//                     j++;
//                 }
//             }
//         }

//         message = message;
//         mappedKey = keyMap;
//     }

//     string encrypt() {
//         string encryptedText = "";
//         for (int i = 0; i < message.length(); i++) {
//             if (message[i] == ' ' && mappedKey[i] == ' ') {
//                 encryptedText += ' ';
//             } else {
//                 int x = (int)message[i] - 65;
//                 int y = (int)mappedKey[i] - 65;
//                 encryptedText += (char)tableArr[x][y];
//             }
//         }
//         return encryptedText;
//     }

//     string decrypt() {
//         string decryptedText = "";
//         for (int i = 0; i < message.length(); i++) {
//             if (message[i] == ' ' && mappedKey[i] == ' ') {
//                 decryptedText += ' ';
//             } else {
//                 int temp = itrCount((int)mappedKey[i], (int)message[i]);
//                 decryptedText += (char)(65 + temp);
//             }
//         }
//         return decryptedText;
//     }
// };

// int main() {
//     cout << "Message and key can only be alphabetic" << endl;
//     int choice;
//     cout << "1. Encryption\n2. Decryption\nChoose (1, 2): ";
//     cin >> choice;
//     cin.ignore();

//     if (choice == 1) {
//         cout << "Encryption" << endl;
//         VigenereCipher cipher;
//         cipher.setMessageAndKey();
//         cout << "Encrypted Text: " << cipher.encrypt() << endl;

//     } else if (choice == 2) {
//         cout << "Decryption" << endl;
//         VigenereCipher cipher;
//         cipher.setMessageAndKey();
//         cout << "Decrypted Text: " << cipher.decrypt() << endl;

//     } else {
//         cout << "Wrong Choice" << endl;
//     }

//     return 0;
// }

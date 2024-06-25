// #include <iostream>
// #include "AESCipher.h" // Include your AES header file here

// int main() {
//     // Sample key for AES-128 (16 bytes)
//     std::vector<std::vector<int>> key = {
//         {0x2b, 0x28, 0xab, 0x09},
//         {0x7e, 0xae, 0xf7, 0xcf},
//         {0x15, 0xd2, 0x15, 0x4f},
//         {0x16, 0xa6, 0x88, 0x3c}
//     };

//     // Test case 1
//     std::string plaintext1 = "Hello, AES!";
//     std::string ciphertext1, decryptedText1;

//     AES aes1(plaintext1, ciphertext1, key);

//     // Encrypt
//     ciphertext1 = aes1.encrypt();
//     std::cout << "Test case 1 - Encrypted text: " << ciphertext1 << std::endl;

//     // Decrypt
//     decryptedText1 = aes1.decrypt();
//     std::cout << "Test case 1 - Decrypted text: " << decryptedText1 << std::endl;

//     // Test case 2
//     std::string plaintext2 = "OpenAI GPT-3.5";
//     std::string ciphertext2, decryptedText2;

//     AES aes2(plaintext2, ciphertext2, key);

//     // Encrypt
//     ciphertext2 = aes2.encrypt();
//     std::cout << "Test case 2 - Encrypted text: " << ciphertext2 << std::endl;

//     // Decrypt
//     decryptedText2 = aes2.decrypt();
//     std::cout << "Test case 2 - Decrypted text: " << decryptedText2 << std::endl;

//     // Test case 3
//     std::string plaintext3 = "1234567890";
//     std::string ciphertext3, decryptedText3;

//     AES aes3(plaintext3, ciphertext3, key);

//     // Encrypt
//     ciphertext3 = aes3.encrypt();
//     std::cout << "Test case 3 - Encrypted text: " << ciphertext3 << std::endl;

//     // Decrypt
//     decryptedText3 = aes3.decrypt();
//     std::cout << "Test case 3 - Decrypted text: " << decryptedText3 << std::endl;

//     return 0;
// }


// #include <iostream>
// #include "rail_f.h"
// #include <string>
// #include <vector>
// using namespace std;
// int main() {
//     string plaintext, ciphertext, decrypted_text;
//     int key;
//     string cipher="";

//     cout << "Enter the plaintext: ";
//     getline(cin, plaintext);

//     cout << "Enter the number of rails: ";
//     cin >> key;
//     cin.ignore(); 

//     RailFenceCipher rail_f(plaintext, cipher , key);

    
//     ciphertext = rail_f.encrypt();
//     cout << "Cipher Text: " << ciphertext << endl;

//     decrypted_text = rail_f.decrypt();
//     cout << "Decrypted Text: " << decrypted_text << endl;

//     return 0;
// }

#include <iostream>
#include "FileCryptography.h"

int main() {
    FileCryptography fileCrypt;
    fileCrypt.processFiles();
    return 0;
}

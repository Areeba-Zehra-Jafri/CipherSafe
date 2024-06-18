#include <iostream>
#include "RSACipher.h"
using namespace std;

int main() {
    long long p = 61; 
    long long q = 53; 
    long long e = 17; 

    string plaintext, ciphertext;
    cout << "Enter the string to be encrypted: ";
    getline(cin, plaintext);

    RSA rsa(p, q, e, plaintext, ciphertext);

    cout << "Public Key (e, n): (" << rsa.getPublicKey().first << ", " << rsa.getPublicKey().second << ")" << endl;
    cout << "Private Key (d, n): (" << rsa.getPrivateKey().first << ", " << rsa.getPrivateKey().second << ")" << endl;

    string encryptedText = rsa.encrypt();
    cout << "Encrypted text: " << encryptedText << endl;

    RSA rsaDecrypt(p, q, e, "", encryptedText); 
    string decryptedText = rsaDecrypt.decrypt();
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}

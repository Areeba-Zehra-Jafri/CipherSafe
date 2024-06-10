#include "Vernam_Cipher.h"
#include<iostream>


//CaesarCipher::CaesarCipher(string p,string c,int s):Cryptography(p,c),shift(s){}

VernamCipher::VernamCipher(string plain_text,string cipher_text,string k):Cryptography(plain_text,cipher_text),key(k) {
    for (int i = 0; i < 26; ++i) {
        matrix[i] = 'A' + i;
    }
}

string VernamCipher:: get_plain_text()
{
    return plaintext;
}

string VernamCipher:: get_cipher()
{
    return ciphertext;
}

string VernamCipher:: get_decrypt()
{
    return plaintext;
}

string VernamCipher:: get_key()
{
    return key;
}

string VernamCipher::encrypt() {
    string ciphertext;
    int n = plaintext.size();
    
    for (int i = 0; i < n; ++i) {
        int plainVal = matrixValue(plaintext[i]);
        int keyVal = matrixValue(key[i]);

        vector<int> plainBin = toBinary(plainVal);
        vector<int> keyBin = toBinary(keyVal);

        vector<int> cipherBin = xorBinary(plainBin, keyBin);

        int cipherVal = toDecimal(cipherBin);
        cipherVal = cipherVal % 26;

        char cipherChar = matrix[cipherVal];
        ciphertext += cipherChar;
    }
    this->ciphertext=ciphertext;
    return ciphertext;
}

string VernamCipher::decrypt() {
    string decrypt_text;
    int n = ciphertext.size();
    //cout<<ciphertext<<endl;
    
    for (int i = 0; i < n; ++i) {
        int cipherVal = matrixValue(ciphertext[i]);
        int keyVal = matrixValue(key[i]);

        vector<int> cipherBin = toBinary(cipherVal);
        vector<int> keyBin = toBinary(keyVal);

        vector<int> plainBin = xorBinary(cipherBin, keyBin);

        int plainVal = toDecimal(plainBin);
        plainVal = plainVal % 26;

        char plainChar = matrix[plainVal];
        decrypt_text += plainChar;
    }

    return decrypt_text;
}

int VernamCipher::matrixValue(char c) {
    return c - 'A';
}

vector<int> VernamCipher::toBinary(int value) {
    vector<int> binary(5, 0);
    for (int i = 4; i >= 0; --i) {
        binary[i] = value % 2;
        value /= 2;
    }
    return binary;
}

int VernamCipher::toDecimal(const vector<int>& binary) {
    int value = 0;
    for (int i = 0; i < 5; ++i) {
        value = value * 2 + binary[i];
    }
    return value;
}

vector<int> VernamCipher::xorBinary(const vector<int>& bin1, const vector<int>& bin2) {
    vector<int> result(5, 0);
    for (int i = 0; i < 5; ++i) {
        result[i] = bin1[i] ^ bin2[i];
    }
    return result;
}

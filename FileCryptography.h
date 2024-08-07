#ifndef FILE_CRYPTOGRAPHY_H
#define FILE_CRYPTOGRAPHY_H

#include <iostream>
#include <fstream>
#include "Cryptography.h"
#include "CaesarCipher.h"
#include "HillCipher.h"
#include "AESCipher.h"
#include "AffineCipher.h"
#include "rail_f.h"
#include "RSACipher.h"
#include "Vernam_Cipher.h"
#include "VigenereCipher.h"
#include "monoalphabetic.h"
#include "login.h"

using namespace std;

class FileCryptography
{
public:
    void processFiles();

private:
    void encryptFile(const string &inputFilePath, const string &outputFilePath);
    void decryptFile(const string &inputFilePath, const string &outputFilePath);
    void EncryptDecryptFile(const string &inputFilePath, const string &outputFilePath);
    Cryptography *selectCipher();
    Management Stats;
};

#endif // FILE_CRYPTOGRAPHY_H

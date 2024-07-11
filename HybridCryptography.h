#ifndef HYBRIDCRYPTOGRAPHY_H
#define HYBRIDCRYPTOGRAPHY_H

#include "TextCryptography.h"
#include "Steganography.h"
#include "login.h"
#include <string>

class HybridCryptography
{
public:
    void encryptAndEmbedText();
    void extractAndDecryptText();
    void processTextHybrid();

private:
    TextCryptography textCrypt;
    Steganography stego;
    Management Stats;
    Cryptography *selectTextCipher();
};

#endif // HYBRIDCRYPTOGRAPHY_H

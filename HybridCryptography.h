#ifndef HYBRIDCRYPTOGRAPHY_H
#define HYBRIDCRYPTOGRAPHY_H

#include "TextCryptography.h"
#include "Steganography.h"
#include <string>

class HybridCryptography {
public:
    void encryptAndEmbedText();
    void extractAndDecryptText();
    void processTextHybrid();
private:
    TextCryptography textCrypt;
    Steganography stego;

    Cryptography* selectTextCipher();
};

#endif // HYBRIDCRYPTOGRAPHY_H

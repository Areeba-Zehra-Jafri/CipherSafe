#ifndef TEXTCRYPTOGRAPHY_H
#define TEXTCRYPTOGRAPHY_H

#include <string>
#include "Cryptography.h"
#include "CaesarCipher.h"
#include "HillCipher.h"
#include "AffineCipher.h"
#include "VigenereCipher.h"
#include "rail_f.h"
#include "Monoalphabetic.h"
#include "Vernam_Cipher.h"
#include "RSACipher.h"
#include "AESCipher.h"
#include "login.h"

class TextCryptography {
public:
    void processText();

private:
    void encryptText(const std::string& plaintext);
    void decryptText(const std::string& ciphertext);
    Cryptography* selectCipher();
    Management Stats;
};

#endif // TEXTCRYPTOGRAPHY_H

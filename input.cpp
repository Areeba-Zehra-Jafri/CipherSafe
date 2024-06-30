#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <cctype>
#include <unordered_set>
#include "Cryptography.h"
#include "AffineCipher.h"
#include "CaesarCipher.h"
#include "HillCipher.h"
#include "Rail_f.h"
#include "RSACipher.h"
#include "Vernam_Cipher.h"
#include "VigenereCipher.h"
#include "AESCipher.h"
#include "monoalphabetic.h" 

using namespace std;

class CipherInput {
public:
    static int getAffineCipherKey() {
        int a, b;
        cout << "Enter a and b for Affine Cipher: ";
        cin >> a >> b;
        if (gcd(a, 26) != 1) {
            throw invalid_argument("In Affine Cipher, 'a' must be coprime with 26.");
        }
        return a * 100 + b; 
    }

    static int getCaesarCipherKey() {
        int shift;
        cout << "Enter shift for Caesar Cipher: ";
        cin >> shift;
        if (shift < 0 || shift >= 26) {
            throw invalid_argument("In Caesar Cipher, shift must be in the range [0, 25].");
        }
        return shift;
    }

    static void validateHillCipherKey(const std::string& key) {
        if (key.length() != 4) {
            throw std::invalid_argument("In Hill Cipher, key must be 4 characters long.");
        }

        // Validate characters are within 'a' to 'z' range and convert to matrix values
        std::vector<std::vector<int>> keyMatrix(2, std::vector<int>(2));

        keyMatrix = {
            {(key[0] - 'a') % 26, (key[1] - 'a') % 26},
            {(key[2] - 'a') % 26, (key[3] - 'a') % 26}
        };
    }

    static int getRailFenceCipherKey() {
        int railKey;
        cout << "Enter rail key for Rail Fence Cipher: ";
        cin >> railKey;
        if (railKey < 2) {
            throw invalid_argument("In Rail Fence Cipher, rail key must be at least 2.");
        }
        return railKey;
    }

    static std::vector<long long> getRSACipherKey() {
        long long p, q, e;
        cout << "Enter p, q, and e for RSA: ";
        cin >> p >> q >> e;
        if (!isPrime(p) || !isPrime(q)) {
            throw invalid_argument("In RSA, both p and q must be prime numbers.");
        }
        if (e <= 1 || gcd(e, (p - 1) * (q - 1)) != 1) {
            throw invalid_argument("In RSA, e must be greater than 1 and coprime with (p-1)*(q-1).");
        }
        std::vector<long long> rsaKey = {p, q, e};
        return rsaKey;
    }

    static string getVernamCipherKey(const string& plaintext) {
        string key;
        cout << "Enter key for Vernam Cipher (length " << plaintext.length() << "): ";
        cin >> key;
        if (plaintext.length() != key.length()) {
            throw invalid_argument("In Vernam Cipher, key must be the same length as plaintext.");
        }
        return key;
    }

    static string getVigenereCipherKey() {
        string key;
        cout << "Enter key for Vigenere Cipher (uppercase letters only): ";
        cin >> key;
        for (char c : key) {
            if (!isupper(c)) {
                throw invalid_argument("In Vigenere Cipher, key must be uppercase letters only.");
            }
        }
        return key;
    }

    static std::vector<std::vector<int>> getAESCipherKey() {
        std::string keyText; // Example 128-bit key in text format
        cout << "Enter AES key (exactly 16 characters): ";
        cin >> keyText;

        // Validate key length and characters
        if (keyText.size() != 16 || !std::all_of(keyText.begin(), keyText.end(), [](char c) {
            return std::isalnum(static_cast<unsigned char>(c));
        })) {
            throw std::invalid_argument("Key must be exactly 16 alphanumeric characters.");
        }

        // Convert keyText to 2D vector in AES format
        std::vector<std::vector<int>> aesKey(4, std::vector<int>(4));

        for (int i = 0; i < 16; ++i) {
            aesKey[i % 4][i / 4] = static_cast<int>(keyText[i]);
        }

        return aesKey;
    }

    static std::string getMonoalphabeticCipherKey() {
        std::string key;
        cout << "Enter key for Monoalphabetic Cipher (26 lowercase letters): ";
        cin >> key;

        // Validate key length and characters
        if (key.length() != 26) {
            throw invalid_argument("In Monoalphabetic Cipher, key length must be 26 characters.");
        }

        unordered_set<char> charSet;
        for (char c : key) {
            if (!islower(c)) {
                throw invalid_argument("In Monoalphabetic Cipher, key must contain only lowercase alphabetic characters.");
            }
            if (charSet.find(c) != charSet.end()) {
                throw invalid_argument("In Monoalphabetic Cipher, key must not contain duplicate characters.");
            }
            charSet.insert(c);
        }

        return key;
    }

private:
    static int gcd(int a, int b) {
        while (b != 0) {
            int t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

    static bool isPrime(long long n) {
        if (n <= 1) return false;
        for (long long i = 2; i * i <= n; ++i) {
            if (n % i == 0) return false;
        }
        return true;
    }
};
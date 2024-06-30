#include "CipherInput.h"

int CipherInput::getAffineCipherKey() {
    int a, b;
    std::cout << "Enter a and b for Affine Cipher: ";
    std::cin >> a >> b;
    if (gcd(a, 26) != 1) {
        throw std::invalid_argument("In Affine Cipher, 'a' must be coprime with 26.");
    }
    return a * 100 + b;
}

int CipherInput::getCaesarCipherKey() {
    int shift;
    std::cout << "Enter shift for Caesar Cipher: ";
    std::cin >> shift;
    if (shift < 0 || shift >= 26) {
        throw std::invalid_argument("In Caesar Cipher, shift must be in the range [0, 25].");
    }
    return shift;
}

std::string CipherInput::getHillCipherKey() {
    std::string key; 
    std::cout << "Enter key for Hill Cipher: ";
    std::cin >> key;
    if (key.length() != 4) {
        throw std::invalid_argument("In Hill Cipher, key must be 4 characters long.");
    }

    return key;
}

int CipherInput::getRailFenceCipherKey() {
    int railKey;
    std::cout << "Enter rail key for Rail Fence Cipher: ";
    std::cin >> railKey;
    if (railKey < 2) {
        throw std::invalid_argument("In Rail Fence Cipher, rail key must be at least 2.");
    }
    return railKey;
}

std::vector<long long> CipherInput::getRSACipherKey() {
    long long p, q, e;
    std::cout << "Enter p, q, and e for RSA: ";
    std::cin >> p >> q >> e;
    if (!isPrime(p) || !isPrime(q)) {
        throw std::invalid_argument("In RSA, both p and q must be prime numbers.");
    }
    if (e <= 1 || gcd(e, (p - 1) * (q - 1)) != 1) {
        throw std::invalid_argument("In RSA, e must be greater than 1 and coprime with (p-1)*(q-1).");
    }
    std::vector<long long> rsaKey = {p, q, e};
    return rsaKey;
}

std::string CipherInput::getVernamCipherKey() {
    std::string key;
    std::cout << "Enter key for Vernam Cipher: ";
    std::cin >> key;
    return key;
}

std::string CipherInput::getVigenereCipherKey() {
    std::string key;
    std::cout << "Enter key for Vigenere Cipher (uppercase letters only): ";
    std::cin >> key;
    for (char c : key) {
        if (!isupper(c)) {
            throw std::invalid_argument("In Vigenere Cipher, key must be uppercase letters only.");
        }
    }
    return key;
}

std::vector<std::vector<int>> CipherInput::getAESCipherKey() {
    std::string keyText;
    std::cout << "Enter AES key (exactly 16 characters): ";
    std::cin >> keyText;

    if (keyText.size() != 16 || !std::all_of(keyText.begin(), keyText.end(), [](char c) {
        return std::isalnum(static_cast<unsigned char>(c));
    })) {
        throw std::invalid_argument("Key must be exactly 16 alphanumeric characters.");
    }

    std::vector<std::vector<int>> aesKey(4, std::vector<int>(4));

    for (int i = 0; i < 16; ++i) {
        aesKey[i % 4][i / 4] = static_cast<int>(keyText[i]);
    }

    return aesKey;
}

std::string CipherInput::getMonoalphabeticCipherKey() {
    std::string key;
    std::cout << "Enter key for Monoalphabetic Cipher (26 lowercase letters): ";
    std::cin >> key;

    if (key.length() != 26) {
        throw std::invalid_argument("In Monoalphabetic Cipher, key length must be 26 characters.");
    }

    std::unordered_set<char> charSet;
    for (char c : key) {
        if (!islower(c)) {
            throw std::invalid_argument("In Monoalphabetic Cipher, key must contain only lowercase alphabetic characters.");
        }
        if (charSet.find(c) != charSet.end()) {
            throw std::invalid_argument("In Monoalphabetic Cipher, key must not contain duplicate characters.");
        }
        charSet.insert(c);
    }

    return key;
}

int CipherInput::gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

bool CipherInput::isPrime(long long n) {
    if (n <= 1) return false;
    for (long long i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

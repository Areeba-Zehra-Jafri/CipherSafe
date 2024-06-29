#include <iostream>
#include <string>
#include <stdexcept>
#include "Cryptography.h"
#include "AffineCipher.h"
#include "CaesarCipher.h"
#include "HillCipher.h"
#include "Rail_f.h"
#include "RSACipher.h"
#include "Vernam_Cipher.h"
#include "VigenereCipher.h"
#include "AESCipher.h"

using namespace std;

class CipherInput {
public:
    static AffineCipher getAffineCipher(const string& plaintext, const string& ciphertext, int a, int b) {
        if (gcd(a, 26) != 1) {
            throw invalid_argument("In Affine Cipher, 'a' must be coprime with 26.");
        }
        return AffineCipher(plaintext, ciphertext, a, b);
    }

    static CaesarCipher getCaesarCipher(const string& plaintext, const string& ciphertext, int shift) {
        if (shift < 0 || shift >= 26) {
            throw invalid_argument("In Caesar Cipher, shift must be in the range [0, 25].");
        }
        return CaesarCipher(plaintext, ciphertext, shift);
    }

    static HillCipher getHillCipher(const string& plaintext, const string& ciphertext, const string& key) {
        if (key.length() != 4) {
            throw invalid_argument("In Hill Cipher, key must be 4 characters long.");
        }
        return HillCipher(plaintext, ciphertext, key);
    }

    static RailFenceCipher getRailFenceCipher(const string& plaintext, const string& ciphertext, int railKey) {
        if (railKey < 2) {
            throw invalid_argument("In Rail Fence Cipher, rail key must be at least 2.");
        }
        return RailFenceCipher(plaintext, ciphertext, railKey);
    }

    static RSA getRSACipher(const string& plaintext, const string& ciphertext, long long p, long long q, long long e) {
        if (!isPrime(p) || !isPrime(q)) {
            throw invalid_argument("In RSA, both p and q must be prime numbers.");
        }
        if (e <= 1 || gcd(e, (p - 1) * (q - 1)) != 1) {
            throw invalid_argument("In RSA, e must be greater than 1 and coprime with (p-1)*(q-1).");
        }
        return RSA(plaintext, ciphertext, p, q, e);
    }

    static VernamCipher getVernamCipher(const string& plaintext, const string& ciphertext, const string& key) {
        if (plaintext.length() != key.length()) {
            throw invalid_argument("In Vernam Cipher, key must be the same length as plaintext.");
        }
        return VernamCipher(plaintext, ciphertext, key);
    }

    static VigenereCipher getVigenereCipher(const string& plaintext, const string& ciphertext, const string& key) {
        for (char c : key) {
            if (!isupper(c)) {
                throw invalid_argument("In Vigenere Cipher, key must be uppercase letters only.");
            }
        }
        return VigenereCipher(plaintext, ciphertext, key);
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

int main() {
    try {
        string plaintext, ciphertext;
        int a, b, shift, railKey;
        long long p, q, e;
        string key, vernamKey, vigenereKey;

        cout << "Enter plaintext for Affine Cipher: ";
        getline(cin, plaintext);
        cout << "Enter a and b for Affine Cipher: ";
        cin >> a >> b;
        cin.ignore(); 
        AffineCipher ac = CipherInput::getAffineCipher(plaintext, "", a, b);
        cout << "Affine Cipher Encrypted: " << ac.encrypt() << endl;
        cout << "Affine Cipher Decrypted: " << ac.decrypt() << endl;

        cout << "Enter plaintext for Caesar Cipher: ";
        getline(cin, plaintext);
        cout << "Enter shift for Caesar Cipher: ";
        cin >> shift;
        cin.ignore(); 
        CaesarCipher cc = CipherInput::getCaesarCipher(plaintext, "", shift);
        cout << "Caesar Cipher Encrypted: " << cc.encrypt() << endl;
        cout << "Caesar Cipher Decrypted: " << cc.decrypt() << endl;

        cout << "Enter plaintext for Hill Cipher: ";
        getline(cin, plaintext);
        cout << "Enter key for Hill Cipher: ";
        getline(cin, key);
        HillCipher hc = CipherInput::getHillCipher(plaintext, "", key);
        cout << "Hill Cipher Encrypted: " << hc.encrypt() << endl;
        cout << "Hill Cipher Decrypted: " << hc.decrypt() << endl;

        cout << "Enter plaintext for Rail Fence Cipher: ";
        getline(cin, plaintext);
        cout << "Enter rail key for Rail Fence Cipher: ";
        cin >> railKey;
        cin.ignore(); 
        RailFenceCipher rfc = CipherInput::getRailFenceCipher(plaintext, "", railKey);
        cout << "Rail Fence Cipher Encrypted: " << rfc.encrypt() << endl;
        cout << "Rail Fence Cipher Decrypted: " << rfc.decrypt() << endl;

        cout << "Enter p, q, and e for RSA: ";
        cin >> p >> q >> e;
        cin.ignore(); 
        RSA rsa = CipherInput::getRSACipher(plaintext, ciphertext, p, q, e);
        cout << "Enter plaintext for RSA: ";
        getline(cin, plaintext);
        rsa.set_plaintext(plaintext);
        rsa.set_ciphertext("");
        cout << "RSA Encrypted: " << rsa.encrypt() << endl;
        cout << "RSA Decrypted: " << rsa.decrypt() << endl;

        cout << "Enter plaintext for Vernam Cipher: ";
        getline(cin, plaintext);
        cout << "Enter key for Vernam Cipher: ";
        getline(cin, vernamKey);
        VernamCipher vc = CipherInput::getVernamCipher(plaintext, ciphertext, vernamKey);
        cout << "Vernam Cipher Encrypted: " << vc.encrypt() << endl;
        cout << "Vernam Cipher Decrypted: " << vc.decrypt() << endl;

        cout << "Enter plaintext for Vigenere Cipher: ";
        getline(cin, plaintext);
        cout << "Enter key for Vigenere Cipher: ";
        getline(cin, vigenereKey);
        VigenereCipher vigc = CipherInput::getVigenereCipher(plaintext, "", vigenereKey);
        cout << "Vigenere Cipher Encrypted: " << vigc.encrypt() << endl;
        cout << "Vigenere Cipher Decrypted: " << vigc.decrypt() << endl;

    } catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    } catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}

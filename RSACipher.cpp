#include "RSACipher.h"
#include <cmath>
#include <random>
#include <sstream>
using namespace std;

RSA::RSA(const string& plaintext, const string& ciphertext,long long p, long long q, long long e)
    : p(p), q(q), e(e), plaintext(plaintext), ciphertext(ciphertext) , Cryptography(plaintext, ciphertext) {
    n = p * q;
    phi = (p - 1) * (q - 1);
    d = modInverse(e, phi);
}

long long generatePrime() {
    static std::random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<long long> dis(100, 999);

    long long prime;
    while (true) {
        prime = dis(gen);
        bool isPrime = true;
        for (long long i = 2; i <= sqrt(prime); ++i) {
            if (prime % i == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) break;
    }
    return prime;
}

long long RSA::gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long RSA::modInverse(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

long long RSA::modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

pair<long long, long long> RSA::getPublicKey() {
    return {e, n};
}

pair<long long, long long> RSA::getPrivateKey() {
    return {d, n};
}

string RSA::encrypt() {
    vector<long long> plainNums = stringToInt(plaintext);
    vector<long long> cipherNums;
    for (long long num : plainNums) {
        cipherNums.push_back(modExp(num, e, n));
    }

    ostringstream oss;
    for (long long num : cipherNums) {
        oss << num << " ";
    }
    return oss.str();
}

string RSA::decrypt() {
    istringstream iss(ciphertext);
    vector<long long> cipherNums;
    long long num;
    while (iss >> num) {
        cipherNums.push_back(num);
    }

    vector<long long> plainNums;
    for (long long num : cipherNums) {
        plainNums.push_back(modExp(num, d, n));
    }

    return intToString(plainNums);
}

vector<long long> RSA::stringToInt(const string &str) {
    vector<long long> result;
    for (char c : str) {
        result.push_back(static_cast<long long>(c));
    }
    return result;
}

string RSA::intToString(const vector<long long> &nums) {
    string result;
    for (long long num : nums) {
        result += static_cast<char>(num);
    }
    return result;
}
void RSA::set_plaintext(const string& p)
{
    plaintext=p;
}
void RSA::set_ciphertext(const string& c)
{
    ciphertext=c;
}
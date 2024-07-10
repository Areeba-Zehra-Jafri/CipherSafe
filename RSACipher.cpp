#include "RSACipher.h"
#include <cmath>
#include <random>
#include <sstream>
#include <stdexcept>
#include <chrono>  // Include the chrono library
#include <cstdlib> // For srand and rand
#include <ctime>   // For time

using namespace std;

RSA::RSA(const string &plaintext, const string &ciphertext, long long p, long long q, long long e)
    : p(p), q(q), e(e), plaintext(plaintext), ciphertext(ciphertext), Cryptography(plaintext, ciphertext)
{
    n = p * q;
    phi = (p - 1) * (q - 1);
    try
    {
        d = modInverse(e, phi);
    }
    catch (const std::exception &e)
    {
        cerr << "\033[1;31mInvalid parameters for RSA encryption.\033[0m" << endl;
    }
}

long long generatePrime()
{
    static std::random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<long long> dis(100, 999);

    long long prime;
    while (true)
    {
        prime = dis(gen);
        bool isPrime = true;
        for (long long i = 2; i <= sqrt(prime); ++i)
        {
            if (prime % i == 0)
            {
                isPrime = false;
                break;
            }
        }
        if (isPrime)
            break;
    }
    return prime;
}

long long RSA::gcd(long long a, long long b)
{
    while (b != 0)
    {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long RSA::modInverse(long long a, long long m)
{
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1)
    {
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

long long RSA::modExp(long long base, long long exp, long long mod)
{
    long long result = 1;
    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

pair<long long, long long> RSA::getPublicKey()
{
    return {e, n};
}

pair<long long, long long> RSA::getPrivateKey()
{
    return {d, n};
}

string RSA::get_plaintext()
{

    cout << "==INPUT RULES==\n";
    cout << "Input must contain only alphanumeric characters (no spaces)." << endl;
    cout << "\n--------------------\n";
    cout << "Enter the plaintext : ";
    cin >> plaintext;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n--------------------\n";

    return plaintext;
}

// string RSA::get_ciphertext()
// {
//     cout << "\n-----------------------------------------------\n";
//     cout << "Enter the ciphertext (only numbers separated by spaces): ";
//     cin >> ciphertext;
//     cout << "\n-----------------------------------------------\n";

//     return ciphertext;
// }
string RSA::get_ciphertext()
{
    cout << "\n-----------------------------------------------\n";
    cout << "Enter the ciphertext (only numbers separated by spaces): ";
    cin.ignore(); // Ignore the remaining newline character from the previous input
    getline(cin, ciphertext);
    cout << "\n-----------------------------------------------\n";

    return ciphertext;
}

string RSA::encrypt()
{
    try
    {
        if (plaintext.empty())
        {
            throw invalid_argument("\033[1;31mPlaintext cannot be empty.\033[0m");
        }

        vector<long long> plainNums = stringToInt(plaintext);
        vector<long long> cipherNums;

        srand(time(0));                                    // Seed the random number generator
        auto start = chrono::high_resolution_clock::now(); // Start time

        for (long long num : plainNums)
        {
            cipherNums.push_back(modExp(num, e, n));

            // Introduce an artificial delay
            int delay = rand() % 100 + 1; // Random delay between 1 and 100 nanoseconds
            auto delay_start = chrono::high_resolution_clock::now();
            while (chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - delay_start).count() < delay)
                ;
        }

        ostringstream oss;
        for (long long num : cipherNums)
        {
            oss << num << " ";
        }
        ciphertext = oss.str();

        auto end = chrono::high_resolution_clock::now(); // End time
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
        cout << "\n---------------------------\n";
        cout << "Encryption time: " << duration.count() << " ns" << endl; // Print the duration in nanoseconds
        cout << "---------------------------\n"
             << endl;

        cout << "\n\033[1;34m---------------------------\n";
        cout << "Encryption successful." << endl;
        cout << "\n---------------------------\033[0m\n"
             << endl;

        return ciphertext;
    }
    catch (const exception &e)
    {
        throw;
    }
}

string RSA::decrypt()
{
    try
    {

        if (ciphertext.empty())
        {
            throw invalid_argument("\033[1;31mCiphertext cannot be empty.\033[0m");
        }
        istringstream iss(ciphertext);
        vector<long long> cipherNums;
        long long num;
        while (iss >> num)
        {
            cipherNums.push_back(num);
        }

        vector<long long> plainNums;

        srand(time(0));                                    // Seed the random number generator
        auto start = chrono::high_resolution_clock::now(); // Start time

        for (long long num : cipherNums)
        {
            plainNums.push_back(modExp(num, d, n));

            // Introduce an artificial delay
            int delay = rand() % 100 + 1; // Random delay between 1 and 100 nanoseconds
            auto delay_start = chrono::high_resolution_clock::now();
            while (chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - delay_start).count() < delay)
                ;
        }

        plaintext = intToString(plainNums);

        auto end = chrono::high_resolution_clock::now(); // End time
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
        cout << "\n---------------------------\n";
        cout << "Decryption time: " << duration.count() << " ns" << endl; // Print the duration in nanoseconds
        cout << "---------------------------\n"
             << endl;

        cout << "\n\033[1;34m---------------------------\n";
        cout << "Decryption successful." << endl;
        cout << "\n---------------------------\033[0m\n"
             << endl;

        return plaintext;
    }
    catch (const std::exception &e)
    {
        throw;
    }
}

vector<long long> RSA::stringToInt(const string &str)
{
    vector<long long> result;
    for (char c : str)
    {
        result.push_back(static_cast<long long>(c));
    }
    return result;
}

string RSA::intToString(const vector<long long> &nums)
{
    string result;
    for (long long num : nums)
    {
        result += static_cast<char>(num);
    }
    return result;
}

void RSA::set_plaintext(const string &p)
{

    try
    {

        for (char c : p)
        {
            if (!isalnum(c))
            {
                throw invalid_argument("Plaintext should only contain alphanumeric characters.");
            }
        }

        plaintext = p;
    }

    catch (const exception &e)
    {
        throw;
    }
}

void RSA::set_ciphertext(const string &c)
{
    try
    {

        istringstream iss(c);
        long long num;
        while (iss >> num)
        {
            if (iss.peek() == ' ')
                iss.ignore();

            if (iss.fail())
            {
                throw invalid_argument("Ciphertext should only contain numbers separated by spaces.");
            }
        }

        ciphertext = c;
    }
    catch (const exception &e)
    {
       throw;
    }
}

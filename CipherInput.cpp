#include "CipherInput.h"
#include<string>
#include<vector>

using namespace std;

int CipherInput::getAffineCipherKey()
{
    int a, b;
    string input;

    // Input and validate 'a'
    cout << "==INPUT RULES\n";
    cout << "1. 'a' must be coprime with 26.\n";
    cout << "\n---------------------------\n";
    cout << "Input a and b for Affine Cipher:\n";
    cout << "Enter a: ";
    while (true)
    {
        cin >> input;
        if (cin.fail() || !all_of(input.begin(), input.end(), ::isdigit))
        {
            cout << "\033[1;31mInvalid input: 'a' must be a numeric value. Please enter again: \033[0m";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            a = stoi(input);
            break;
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Input and validate 'b'
    cout << "Enter b: ";
    while (true)
    {
        cin >> input;
        if (cin.fail() || !all_of(input.begin(), input.end(), ::isdigit))
        {
            cout << "\033[1;31mInvalid input: 'b' must be a numeric value. Please enter again: \033[0m";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            b = stoi(input);
            break;
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n---------------------------\n";

    // Validate 'a' is coprime with 26
    if (gcd(a, 26) != 1)
    {
        throw invalid_argument("\033[1;31mIn Affine Cipher, 'a' must be coprime with 26.\033[0m");
    }

    return a * 100 + b;
}

int CipherInput::getCaesarCipherKey()
{
    int shift;
    cout << "==INPUT RULES==\n";
    cout << "1. Enter a positive integer between 1 and 25 \n";
    cout << "\n---------------------------\n";
    cout << "Enter shift for Caesar Cipher: ";
    cout << "\n---------------------------\n";
    string input;
    cin >> input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    bool isNumeric = true;
    for (char c : input)
    {
        if (!isdigit(c))
        {
            isNumeric = false;
            break;
        }
    }

    if (!isNumeric)
    {
        throw invalid_argument("\033[1;31mInvalid input: Shift must be a numeric value.\033[0m");
    }

    shift = std::stoi(input);

    if (shift < 0 || shift >= 26)
    {
        throw invalid_argument("\033[1;31mIn Caesar Cipher, shift must be in the range [0, 25].\033[0m");
    }
    return shift;
}

std::string CipherInput::getHillCipherKey()
{
    string key;
    cout << "==INPUT RULES==\n";
    cout << "1. The key must be exactly 4 alphabetic characters.\n";
    cout << "2. No uppercase , spaces or special characters are allowed.\n";
    cout << "3. lowercase letters are accepted.\n";
    cout << "\n---------------------------\n";
    cout << "Enter key for Hill Cipher: ";
    cout << "\n---------------------------\n";
    cin >> key;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (key.length() != 4)
    {
        throw invalid_argument("\033[1;31mIn Hill Cipher, key must be 4 characters long.\033[0m");
    }

    return key;
}

int CipherInput::getRailFenceCipherKey()
{
    int railKey;
    string input;

    cout << "==INPUT RULES==\n";
    cout << "1. The key must be at least 2.\n";
    cout << "\n-------------------------------------\n";
    cout << "Enter rail key for Rail Fence Cipher: ";
    cout << "\n-------------------------------------\n";

    while (true)
    {
        cin >> input;
        if (cin.fail() || !all_of(input.begin(), input.end(), ::isdigit))
        {
            cout << "\033[1;31mInvalid input: Rail key must be a numeric value. Please enter again: \033[0m";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            railKey = stoi(input);
            if (railKey < 2)
            {
                cout << "\033[1;31mIn Rail Fence Cipher, rail key must be at least 2. Please enter again: \033[0m";
            }
            else
            {
                break;
            }
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n-------------------------------------\n";
    return railKey;
}

vector<long long> CipherInput::getRSACipherKey()
{
    long long p, q, e;
    string input;

    // Input and validate 'p'

    cout << "==INPUT RULES==\n";
    cout << "1. 'p' and 'q' must be prime numbers.\n";
    cout << "2. 'e' must be greater than 1 and coprime with (p-1)*(q-1).\n";
    cout << "\n---------------------------\n";
    cout << "Input p, q, and e for RSA:\n";
    cout << "Enter p: ";
    while (true)
    {
        cin >> input;
        if (cin.fail() || !all_of(input.begin(), input.end(), ::isdigit))
        {
            cout << "\033[1;31mInvalid input: 'p' must be a numeric value. Please enter again: \033[0m";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            p = stoll(input);
            break;
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Input and validate 'q'
    cout << "Enter q: ";
    while (true)
    {
        cin >> input;
        if (cin.fail() || !all_of(input.begin(), input.end(), ::isdigit))
        {
            cout << "\033[1;31mInvalid input: 'q' must be a numeric value. Please enter again: \033[0m";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            q = stoll(input);
            break;
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Input and validate 'e'
    cout << "Enter e: ";
    while (true)
    {
        cin >> input;
        if (cin.fail() || !all_of(input.begin(), input.end(), ::isdigit))
        {
            cout << "\033[1;31mInvalid input: 'e' must be a numeric value. Please enter again: \033[0m";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            e = stoll(input);
            break;
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n---------------------------\n";

    // Validate 'p' and 'q' are prime
    if (!isPrime(p) || !isPrime(q))
    {
        throw invalid_argument("\033[1;31mIn RSA, both p and q must be prime numbers.\033[0m");
    }

    // Validate 'e' is greater than 1 and coprime with (p-1)*(q-1)
    if (e <= 1 || gcd(e, (p - 1) * (q - 1)) != 1)
    {
        throw invalid_argument("\033[1;31mIn RSA, e must be greater than 1 and coprime with (p-1)*(q-1).\033[0m");
    }

    vector<long long> rsaKey = {p, q, e};
    return rsaKey;
}

string CipherInput::getVigenereCipherKey()
{
    string key;
    cout << "==INPUT RULES==\n";
    cout << "1. The key must be a string of uppercase letters only .\n";
    cout << "\n-------------------------------------------------------\n";
    cout << "Enter key for Vigenere Cipher (uppercase letters only): ";
    cout << "\n-------------------------------------------------------\n";
    cin >> key;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (char c : key)
    {
        if (!isupper(c))
        {
            throw invalid_argument("\033[1;31mIn Vigenere Cipher, key must be uppercase letters only.\033[0m");
        }
    }
    return key;
}

vector<vector<int>> CipherInput::getAESCipherKey()
{
    string keyText;
    cout << "==INPUT RULES==\n";
    cout << "1. The AES key must be exactly 16 alphanumeric characters.\n";
    cout << "\n-------------------------------------\n";
    cout << "Enter AES key (exactly 16 characters): ";
    cout << "\n-------------------------------------\n";
    cin >> keyText;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (keyText.size() != 16 || !std::all_of(keyText.begin(), keyText.end(), [](char c)
                                             { return std::isalnum(static_cast<unsigned char>(c)); }))
    {
        throw invalid_argument("\033[1;31mKey must be exactly 16 alphanumeric characters.\033[0m");
    }

    vector<vector<int>> aesKey(4, vector<int>(4));

    for (int i = 0; i < 16; ++i)
    {
        aesKey[i % 4][i / 4] = static_cast<int>(keyText[i]);
    }

    return aesKey;
}

string CipherInput::getMonoalphabeticCipherKey()
{
    string key;
    cout << "==INPUT RULES==\n";
    cout << "1. The key must be a string of 26 lowercase letters.\n";
    cout << "2. The key must not contain duplicate characters.\n";
    cout << "\n----------------------------------------------------------\n";
    cout << "Enter key for Monoalphabetic Cipher (26 lowercase letters): ";
    cout << "\n----------------------------------------------------------\n";
    cin >> key;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (key.length() != 26)
    {
        throw invalid_argument("\033[1;31mIn Monoalphabetic Cipher, key length must be 26 characters.\033[0m");
    }

    unordered_set<char> charSet;
    for (char c : key)
    {
        if (!islower(c))
        {
            throw invalid_argument("\033[1;31mIn Monoalphabetic Cipher, key must contain only lowercase alphabetic characters.\033[0m");
        }
        if (charSet.find(c) != charSet.end())
        {
            throw invalid_argument("\033[1;31mIn Monoalphabetic Cipher, key must not contain duplicate characters.\033[0m");
        }
        charSet.insert(c);
    }

    return key;
}

int CipherInput::gcd(int a, int b)
{
    while (b != 0)
    {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

bool CipherInput::isPrime(long long n)
{
    if (n <= 1)
        return false;
    for (long long i = 2; i * i <= n; ++i)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}
string CipherInput::getVernamCipherKey()
{
    string key;
    cout << "==INPUT RULES==\n";
    cout << "1. The key must be a string of uppercase letters A-Z.\n";
    cout << "------------------------------------------\n";
    cout << "Enter the key for Vernam Cipher (A-Z only): ";
    cout << "\n--------------------------------------------\n";
    cin >> key;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Validate key (should contain only uppercase letters A-Z)
    for (char c : key)
    {
        if (!(c >= 'A' && c <= 'Z'))
        {
            throw invalid_argument("\033[1;31mInvalid key. Key should contain only uppercase letters A-Z.\033[0m");
        }
    }

    return key;
}
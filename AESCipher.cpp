#include "AESCipher.h"
#include <vector>
#include <stdexcept>
#include <cctype>
#include <iostream>
#include <cstdint>
#include <iomanip>

using namespace std;

// Rijndael S-box
const uint8_t sbox[256] = {
    // S-box values
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};

// Rijndael Inverse S-box
const uint8_t rsbox[256] = {
    // Inverse S-box values
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d};

// Rcon values
const uint8_t Rcon[11] = {
    0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};

// Constructor implementation
AES::AES(const string &p, const string &c, const vector<vector<int>> &k) : Cryptography(p, c), key(k)
{
    // padPlaintext();
}

// // Padding function
// void AES::padPlaintext() {
//     size_t padding = 16 - (plaintext.size() % 16);
//     plaintext.append(padding, static_cast<char>(padding));
// }

// Substitute bytes using the S-box
void AES::subBytes(vector<uint8_t> &state)
{
    for (auto &byte : state)
    {
        byte = sbox[byte];
    }
}

void AES::shiftRows(vector<uint8_t> &state)
{
    uint8_t temp;

    // Row 0: no shift needed

    // Row 1: rotate 1 position to the left
    temp = state[4];
    state[4] = state[5];
    state[5] = state[6];
    state[6] = state[7];
    state[7] = temp;

    // Row 2: rotate 2 positions to the left
    temp = state[8];
    state[8] = state[10];
    state[10] = temp;
    temp = state[9];
    state[9] = state[11];
    state[11] = temp;

    // Row 3: rotate 3 positions to the left
    temp = state[12];
    state[12] = state[13];
    state[13] = state[14];
    state[14] = state[15];
    state[15] = temp;
}

uint8_t AES::gmul(uint8_t a, uint8_t b)
{
    uint8_t p = 0;
    uint8_t hi_bit_set;
    for (int counter = 0; counter < 8; counter++)
    {
        if (b & 1)
        {
            p ^= a;
        }
        hi_bit_set = (a & 0x80);
        a <<= 1;
        if (hi_bit_set)
        {
            a ^= 0x1b; // x^8 + x^4 + x^3 + x + 1
        }
        b >>= 1;
    }
    return p;
}

uint8_t AES::gmul_02(uint8_t x)
{
    return gmul(x, 0x02);
}

uint8_t AES::gmul_03(uint8_t x)
{
    return gmul(x, 0x03);
}

void AES::mixColumns(vector<uint8_t> &state)
{
    uint8_t temp_state[16];
    for (int i = 0; i < 16; i++)
    {
        temp_state[i] = state[i];
    }

    for (int i = 0; i < 4; i++)
    {
        state[i * 4] = gmul_02(temp_state[i * 4]) ^ gmul_03(temp_state[i * 4 + 1]) ^ temp_state[i * 4 + 2] ^ temp_state[i * 4 + 3];
        state[i * 4 + 1] = temp_state[i * 4] ^ gmul_02(temp_state[i * 4 + 1]) ^ gmul_03(temp_state[i * 4 + 2]) ^ temp_state[i * 4 + 3];
        state[i * 4 + 2] = temp_state[i * 4] ^ temp_state[i * 4 + 1] ^ gmul_02(temp_state[i * 4 + 2]) ^ gmul_03(temp_state[i * 4 + 3]);
        state[i * 4 + 3] = gmul_03(temp_state[i * 4]) ^ temp_state[i * 4 + 1] ^ temp_state[i * 4 + 2] ^ gmul_02(temp_state[i * 4 + 3]);
    }
}

// Add round key
void AES::addRoundKey(vector<uint8_t> &state, const vector<uint8_t> &roundKey)
{
    for (size_t i = 0; i < state.size(); ++i)
    {
        state[i] ^= roundKey[i];
    }
}

// Key expansion
vector<uint8_t> AES::keyExpansion(const vector<vector<int>> &key)
{
    vector<uint8_t> expandedKey(176); // AES-128 bit key expands to 176 bytes
    int i = 0;

    // The first 16 bytes of the expanded key are the original key
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            expandedKey[i++] = key[row][col];
        }
    }

    // Generate the remaining bytes
    uint8_t temp[4];
    while (i < 176)
    {
        // Store previous 4 bytes in temp
        for (int j = 0; j < 4; ++j)
        {
            temp[j] = expandedKey[i - 4 + j];
        }

        // Perform the key schedule core once every 16 bytes
        if (i % 16 == 0)
        {
            // Rotate left
            uint8_t k = temp[0];
            temp[0] = temp[1];
            temp[1] = temp[2];
            temp[2] = temp[3];
            temp[3] = k;

            // Substitute with S-box
            for (int j = 0; j < 4; ++j)
            {
                temp[j] = sbox[temp[j]];
            }

            // XOR with round constant
            temp[0] ^= Rcon[i / 16];
        }

        // XOR with 16 bytes before
        for (int j = 0; j < 4; ++j)
        {
            expandedKey[i] = expandedKey[i - 16] ^ temp[j];
            ++i;
        }
    }

    return expandedKey;
}

string AES::get_plaintext()
{

    cout << "==INPUT RULES==\n";
    cout << " Plaintext must be exactly 16 bytes long" << endl;
    cout << "\n------------------\n";
    cout << "Enter plaintext :\n ";
    cout << "\n------------------\n";
    cin >> plaintext;

    return plaintext;
}

string AES::get_ciphertext()
{
    cout << "\n------------------\n";
    cout << "Enter Ciphertext :\n ";
    cout << "\n------------------\n";
    cin >> ciphertext;

    return ciphertext;
}
// Encrypt function
string AES::encrypt()
{
    // Convert plaintext to state array
    vector<uint8_t> state(plaintext.begin(), plaintext.end());

    // Expand the key
    vector<uint8_t> expandedKey = keyExpansion(key);

    // Initial round key addition
    addRoundKey(state, vector<uint8_t>(expandedKey.begin(), expandedKey.begin() + 16));

    // Main rounds
    for (int round = 1; round < 10; ++round)
    {
        subBytes(state);
        shiftRows(state);
        mixColumns(state);
        addRoundKey(state, vector<uint8_t>(expandedKey.begin() + 16 * round, expandedKey.begin() + 16 * (round + 1)));
    }

    // Final round
    subBytes(state);
    shiftRows(state);
    addRoundKey(state, vector<uint8_t>(expandedKey.begin() + 160, expandedKey.begin() + 176));

    // Convert state array to ciphertext
    ciphertext.clear();
    for (uint8_t byte : state)
    {
        char buffer[3];
        sprintf(buffer, "%02x", byte);
        ciphertext.append(buffer);
    }

    cout << "\n\033[1;34m---------------------------\n";
    cout << "Encryption successful." << endl;
    cout << "\n---------------------------\033[0m\n"
         << endl;

    return ciphertext;
}

// Inverse substitute bytes
void AES::invSubBytes(vector<uint8_t> &state)
{
    for (auto &byte : state)
    {
        byte = rsbox[byte];
    }
}

// Shift rows to the right
void AES::invShiftRows(vector<uint8_t> &state)
{
    uint8_t temp;

    // Row 0: no shift needed

    // Row 1: rotate 1 position to the right
    temp = state[7];
    state[7] = state[6];
    state[6] = state[5];
    state[5] = state[4];
    state[4] = temp;

    // Row 2: rotate 2 positions to the right
    temp = state[8];
    state[8] = state[10];
    state[10] = temp;
    temp = state[9];
    state[9] = state[11];
    state[11] = temp;

    // Row 3: rotate 3 positions to the right
    temp = state[15];
    state[15] = state[14];
    state[14] = state[13];
    state[13] = state[12];
    state[12] = temp;
}

uint8_t AES::gmul_09(uint8_t x)
{
    return gmul(x, 0x09);
}

uint8_t AES::gmul_0b(uint8_t x)
{
    return gmul(x, 0x0b);
}

uint8_t AES::gmul_0d(uint8_t x)
{
    return gmul(x, 0x0d);
}

uint8_t AES::gmul_0e(uint8_t x)
{
    return gmul(x, 0x0e);
}

void AES::invMixColumns(vector<uint8_t> &state)
{
    uint8_t temp_state[16];
    for (int i = 0; i < 16; i++)
    {
        temp_state[i] = state[i];
    }

    for (int i = 0; i < 4; i++)
    {
        state[i * 4] = gmul_0e(temp_state[i * 4]) ^ gmul_0b(temp_state[i * 4 + 1]) ^ gmul_0d(temp_state[i * 4 + 2]) ^ gmul_09(temp_state[i * 4 + 3]);
        state[i * 4 + 1] = gmul_09(temp_state[i * 4]) ^ gmul_0e(temp_state[i * 4 + 1]) ^ gmul_0b(temp_state[i * 4 + 2]) ^ gmul_0d(temp_state[i * 4 + 3]);
        state[i * 4 + 2] = gmul_0d(temp_state[i * 4]) ^ gmul_09(temp_state[i * 4 + 1]) ^ gmul_0e(temp_state[i * 4 + 2]) ^ gmul_0b(temp_state[i * 4 + 3]);
        state[i * 4 + 3] = gmul_0b(temp_state[i * 4]) ^ gmul_0d(temp_state[i * 4 + 1]) ^ gmul_09(temp_state[i * 4 + 2]) ^ gmul_0e(temp_state[i * 4 + 3]);
    }
}

// Decrypt function
string AES::decrypt()
{
    // Convert ciphertext to state array
    vector<uint8_t> state;
    for (size_t i = 0; i < ciphertext.size(); i += 2)
    {
        uint8_t byte = stoi(ciphertext.substr(i, 2), nullptr, 16);
        state.push_back(byte);
    }

    // Expand the key
    vector<uint8_t> expandedKey = keyExpansion(key);

    // Initial round key addition
    addRoundKey(state, vector<uint8_t>(expandedKey.end() - 16, expandedKey.end()));

    // Main rounds
    for (int round = 9; round > 0; --round)
    {
        invShiftRows(state);
        invSubBytes(state);
        addRoundKey(state, vector<uint8_t>(expandedKey.begin() + 16 * round, expandedKey.begin() + 16 * (round + 1)));
        invMixColumns(state);
    }

    // Final round
    invShiftRows(state);
    invSubBytes(state);
    addRoundKey(state, vector<uint8_t>(expandedKey.begin(), expandedKey.begin() + 16));

    // Convert state array to plaintext
    plaintext.clear();
    for (uint8_t byte : state)
    {
        plaintext.push_back(static_cast<char>(byte));
    }

    // // Remove padding
    // int padding = plaintext.back();
    // plaintext.erase(plaintext.end() - padding, plaintext.end());

    return plaintext;
}

void AES::set_plaintext(const string &p)
{
    if (p.size() == 16)
    {
        for (char c : p)
        {
            if (!isalnum(c))
            {
                throw invalid_argument("\033[1;31mInvalid plaintext. Please enter exactly 16 alphanumeric characters.\033[0m");
            }
        }

        plaintext = p;
    }
    else
    {
        throw invalid_argument("\033[1;31mInvalid plaintext length. Please enter exactly 16 alphanumeric characters.\033[0m");
    }
}

void AES::set_ciphertext(const string &c)
{
    for (char ch : c)
    {
        if (!isxdigit(ch))
        {
            throw invalid_argument("\033[1;31mCiphertext should only contain hexadecimal characters (0-9, A-F).\033[0m");
        }
    }

    ciphertext = c;
}
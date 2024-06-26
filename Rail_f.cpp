#include <iostream>
#include "rail_f.h"
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

RailFenceCipher::RailFenceCipher(const string& p,const string& c, int railKey) : Cryptography(p,c), key(railKey) {}

// Function to encrypt plaintext using rail fence cipher
string RailFenceCipher::encrypt() {
    try {
        if (key == 1 || key >= plaintext.length()) {
            return plaintext;
        }

        vector<string> rail(key);
        int dir = 1;
        int row = 0;

        for (char c : plaintext) {
            rail[row] += c;
            if (row == 0) {
                dir = 1;
            } else if (row == key - 1) {
                dir = -1;
            }
            row += dir;
        }

        string result;
        for (const std::string& r : rail) {
            result += r;
        }

        ciphertext = result;
        return ciphertext;
    }
    catch (const exception& e) {
        cerr << "Exception caught in encrypt(): " << e.what() << endl;
        return ""; // Return empty string or handle the error accordingly
    }
}

// Function to decrypt rail fence cipher
string RailFenceCipher::decrypt() {
    try {
        if (key == 1 || key >= ciphertext.length()) {
            return ciphertext;
        }

        vector<vector<char>> rail(key, vector<char>(ciphertext.length(), '\n'));
        int dir;
        int row = 0, col = 0;

        for (int i = 0; i < ciphertext.length(); ++i) {
            if (row == 0) {
                dir = 1;
            }
            if (row == key - 1) {
                dir = -1;
            }
            rail[row][col++] = '*';
            row += dir;
        }

        int index = 0;
        for (int i = 0; i < key; ++i) {
            for (int j = 0; j < ciphertext.length(); ++j) {
                if (rail[i][j] == '*' && index < ciphertext.length()) {
                    rail[i][j] = ciphertext[index++];
                }
            }
        }

        string result;
        row = 0, col = 0;
        for (int i = 0; i < ciphertext.length(); ++i) {
            if (row == 0) {
                dir = 1;
            }
            if (row == key - 1) {
                dir = -1;
            }
            if (rail[row][col] != '*') {
                result += rail[row][col++];
            }
            row += dir;
        }

        plaintext = result;
        return plaintext;
    }
    catch (const exception& e) {
        cerr << "Exception caught in decrypt(): " << e.what() << endl;
        return ""; // Return empty string or handle the error accordingly
    }
}

void RailFenceCipher::set_plaintext(const string& p) {
    plaintext = p;
}

void RailFenceCipher::set_ciphertext(const string& c) {
    ciphertext = c;
}

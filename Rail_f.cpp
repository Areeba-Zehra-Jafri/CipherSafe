#include <iostream>
#include "rail_f.h"
#include <string>
#include <vector>
using namespace std;

    RailFenceCipher::RailFenceCipher(const std::string& p,string& c, int railKey) : Cryptography(p,c), key(railKey) {}

    // Function to encrypt plaintext using rail fence cipher
    string RailFenceCipher::encrypt() {
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

    // Function to decrypt rail fence cipher
    string RailFenceCipher::decrypt() {
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



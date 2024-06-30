#include <iostream>
#include "rail_f.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <chrono> // Include the chrono library
#include <cstdlib> // For srand and rand
#include <ctime>   // For time

using namespace std;

RailFenceCipher::RailFenceCipher(const string& p, const string& c, int railKey) : Cryptography(p, c), key(railKey) {
    srand(time(0)); // Seed the random number generator
}

string RailFenceCipher::encrypt() {
    try {
        if (key == 1 || key >= plaintext.length()) {
            return plaintext;
        }

        auto start = chrono::high_resolution_clock::now(); // Start time

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

            // Introduce an artificial delay
            int delay = rand() % 100 + 1; // Random delay between 1 and 100 nanoseconds
            auto delay_start = chrono::high_resolution_clock::now();
            while (chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - delay_start).count() < delay);
        }

        string result;
        for (const string& r : rail) {
            result += r;
        }

        ciphertext = result;

        auto end = chrono::high_resolution_clock::now(); // End time
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
        cout << "Encryption time: " << duration.count() << " ns" << endl; // Print the duration in nanoseconds

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

        auto start = chrono::high_resolution_clock::now(); // Start time

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

        // Introduce an artificial delay
        int delay = rand() % 100 + 1; // Random delay between 1 and 100 nanoseconds
        auto delay_start = chrono::high_resolution_clock::now();
        while (chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - delay_start).count() < delay);

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

            // Introduce an artificial delay
            delay = rand() % 100 + 1; // Random delay between 1 and 100 nanoseconds
            delay_start = chrono::high_resolution_clock::now();
            while (chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - delay_start).count() < delay);
        }

        plaintext = result;

        auto end = chrono::high_resolution_clock::now(); // End time
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
        cout << "Decryption time: " << duration.count() << " ns" << endl; // Print the duration in nanoseconds

        return plaintext;
    }
    catch (const exception& e) {
        cerr << "Exception caught in decrypt(): " << e.what() << endl;
        return ""; // Return empty string or handle the error accordingly
    }
}

void RailFenceCipher::set_plaintext(const string& p) {
     for (char c : p) {
        if (!isalpha(c)) {
            throw invalid_argument("Invalid character found in plaintext. Only alphabetic characters are allowed.");
        }
    } 
    plaintext = p;
}

void RailFenceCipher::set_ciphertext(const string& c) {
    ciphertext = c;
}

#include "Steganography.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <bitset>

void Steganography::readImage(const string &filename, vector<unsigned char> &header, vector<unsigned char> &data) {
    ifstream file(filename, ios::binary | ios::ate);
    if (!file) {
        cerr << "Error: Could not open the file " << filename << endl;
        return;
    }

    streamsize fileSize = file.tellg();
    file.seekg(0, ios::beg);

    header.resize(54);
    file.read(reinterpret_cast<char*>(header.data()), 54);

    data.resize(static_cast<size_t>(fileSize) - 54);
    file.read(reinterpret_cast<char*>(data.data()), fileSize - 54);
}

void Steganography::writeImage(const string &filename, const vector<unsigned char> &header, const vector<unsigned char> &data) {
    ofstream file(filename, ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return;
    }

    file.write(reinterpret_cast<const char*>(header.data()), header.size());
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
}

void Steganography::hideMessage(const string &inputImage, const string &outputImage, const string &message) {
    vector<unsigned char> header, data;
    readImage(inputImage, header, data);

    string binaryMessage;
    for (char c : message) {
        binaryMessage += bitset<8>(c).to_string();
    }
    binaryMessage += bitset<8>(0).to_string(); // Null terminator

    if (binaryMessage.size() > data.size()) {
        cerr << "Error: Message is too large to be hidden in the image." << endl;
        return;
    }

    for (size_t i = 0; i < binaryMessage.size(); ++i) {
        data[i] = (data[i] & 0xFE) | (binaryMessage[i] - '0');
    }

    writeImage(outputImage, header, data);
    cout << "Message hidden successfully!" << endl;
}

string Steganography::extractMessage(const string &image) {
    vector<unsigned char> header, data;
    readImage(image, header, data);

    string binaryMessage;
    for (unsigned char byte : data) {
        binaryMessage += (byte & 1) + '0';
    }

    string message;
    for (size_t i = 0; i < binaryMessage.size(); i += 8) {
        bitset<8> bits(binaryMessage.substr(i, 8));
        char c = static_cast<char>(bits.to_ulong());
        if (c == '\0') break; // Null terminator
        message += c;
    }

    return message;
}

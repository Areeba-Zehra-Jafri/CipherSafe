#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H

#include <string>
#include <vector>
#include "login.h"
using namespace std;

class Steganography
{
public:
    void hideMessage(const string &inputImage, const string &outputImage, const string &message);
    string extractMessage(const string &image);
    void runSteganography(Steganography &stego);

private:
    void readImage(const string &filename, vector<unsigned char> &header, vector<unsigned char> &data);
    void writeImage(const string &filename, const vector<unsigned char> &header, const vector<unsigned char> &data);
    Management Stats;
};

#endif // STEGANOGRAPHY_H

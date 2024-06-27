#include "Steganography.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    Steganography stego;
    string inputImage = "input.bmp";
    string outputImage = "output.bmp";
    cout<<"Enter the message to hide"<<endl;
    string message;
    getline(cin, message);

    stego.hideMessage(inputImage, outputImage, message);

    string extractedMessage = stego.extractMessage(outputImage);
    cout << "Extracted Message: " << extractedMessage << endl;

    return 0;
}

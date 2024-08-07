#include "Steganography.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <bitset>
#include <stdexcept>

void Steganography::runSteganography(Steganography &stego)
{
    int choice;
    string inputImage, outputImage;
    string message, extractedMessage;

    while (true)
    {
        cout << "----------------------------------------" << endl;
        cout << "1-Hide message" << endl;
        cout << "2-Extract message" << endl;
        cout << "3-Go back" << endl;
        cout << "----------------------------------------" << endl;
        cin >> choice;
        cin.ignore();

        if (choice == 3)
        {
            return;
        }
        try
        {
            switch (choice)
            {
            case 1:
                cout << "----------------------------------------" << endl;
                cout << "Enter the path of the input image: ";
                cin >> inputImage;

                cout << "Enter the path of the output image: ";
                cin >> outputImage;
                cout << "----------------------------------------" << endl;
                cin.ignore();
                cout << "--------------------------------------" << endl;
                cout << "Enter the message to hide: ";
                getline(cin, message);
                stego.hideMessage(inputImage, outputImage, message);
                Stats.updateTextEmbeddedCount(Stats.getCurrentUsername());
                break;
            case 2:
                cout << "Enter the path of the input image: ";
                cin >> outputImage;
                cout << "----------------------------------------" << endl;
                cin.ignore();
                extractedMessage = stego.extractMessage(outputImage);
                Stats.updateTextExtractedCount(Stats.getCurrentUsername());
                cout << "----------------------------------------" << endl;
                cout << "Extracted Message: " << extractedMessage << endl;
                cout << "----------------------------------------" << endl;
                break;
            default:
                cout << "\033[1;31mInvalid input\033[0m" << endl;
                break;
            }
        }
        catch (const exception &e)
        {
            cerr << "\033[1;31mError: \033[0m" << e.what() << endl;
        }
    }
}

void Steganography::readImage(const string &filename, vector<unsigned char> &header, vector<unsigned char> &data)
{
    ifstream file(filename, ios::binary | ios::ate);
    if (!file)
    {
        throw std::runtime_error("Could not open the file: " + filename);
    }

    streamsize fileSize = file.tellg();
    file.seekg(0, ios::beg);

    header.resize(54);
    file.read(reinterpret_cast<char *>(header.data()), 54);

    data.resize(static_cast<size_t>(fileSize) - 54);
    file.read(reinterpret_cast<char *>(data.data()), fileSize - 54);
}

void Steganography::writeImage(const string &filename, const vector<unsigned char> &header, const vector<unsigned char> &data)
{
    ofstream file(filename, ios::binary);
    if (!file)
    {
        throw std::runtime_error("Could not open the file: " + filename);
    }

    file.write(reinterpret_cast<const char *>(header.data()), header.size());
    file.write(reinterpret_cast<const char *>(data.data()), data.size());
}

void Steganography::hideMessage(const string &inputImage, const string &outputImage, const string &message)
{
    try
    {
        vector<unsigned char> header, data;
        readImage(inputImage, header, data);

        string binaryMessage;
        for (char c : message)
        {
            binaryMessage += bitset<8>(c).to_string();
        }
        binaryMessage += bitset<8>(0).to_string();

        if (binaryMessage.size() > data.size())
        {
            throw runtime_error("Message is too large to be hidden in the image.");
        }

        for (size_t i = 0; i < binaryMessage.size(); ++i)
        {
            data[i] = (data[i] & 0xFE) | (binaryMessage[i] - '0');
        }

        writeImage(outputImage, header, data);
        cout << "\n\033[1;34m---------------------------\n";
        cout << "Message hidden successfully!" << endl;
        cout << "\n---------------------------\033[0m\n";
    }
    catch (const exception &e)
    {
        throw;
    }
}

string Steganography::extractMessage(const string &image)
{
    try
    {
        vector<unsigned char> header, data;
        readImage(image, header, data);

        string binaryMessage;
        for (unsigned char byte : data)
        {
            binaryMessage += (byte & 1) + '0';
        }

        string message;
        for (size_t i = 0; i < binaryMessage.size(); i += 8)
        {
            bitset<8> bits(binaryMessage.substr(i, 8));
            char c = static_cast<char>(bits.to_ulong());
            if (c == '\0')
                break;
            message += c;
        }

        return message;
    }
    catch (const exception &e)
    {
        throw;
    }
}

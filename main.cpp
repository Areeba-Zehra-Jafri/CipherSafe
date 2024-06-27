
// #include "Steganography.h"
// #include <iostream>
// #include <string>

// int main() {
//     Steganography stego;
//     std::string inputImage = "input.bmp";
//     std::string outputImage = "output.bmp";
    
//     // Read the message from the user
//     std::string message;
//     std::cout << "Enter the message to hide: ";
//     std::getline(std::cin, message);

//     stego.hideMessage(inputImage, outputImage, message);

//     std::string extractedMessage = stego.extractMessage(outputImage);
//     std::cout << "Extracted Message: " << extractedMessage << std::endl;

//     return 0;
// }
#include "Steganography.h"
#include <iostream>
#include <string>

int main() {
    Steganography stego;
    int choice;
    std::string inputImage, outputImage;
    std::string message, extractedMessage;

    while (true) {
        std::cout << "1-Encrypt a file" << std::endl;
        std::cout << "2-Decrypt a file" << std::endl;
        std::cout << "3-Exit" << std::endl;
        std::cin >> choice;
        std::cin.ignore(); // Ignore newline left in input buffer after cin >>

        if (choice == 3) {
            exit(0);
        }

        std::cout << "Enter the path of the input image: ";
        cin>>inputImage;
        //std::getline(std::cin, inputImage);

        std::cout << "Enter the path of the output image: ";
        //std::getline(std::cin, outputImage);
        cin>>outputImage;
        cin.ignore();

        switch (choice) {
            case 1:
                std::cout << "Enter the message to hide: ";
                std::getline(std::cin, message);
                stego.hideMessage(inputImage, outputImage, message);
                break;
            case 2:
                extractedMessage = stego.extractMessage(outputImage);
                std::cout << "Extracted Message: " << extractedMessage << std::endl;
                break;
            default:
                std::cout << "Invalid input" << std::endl;
                break;
        }
    }

    return 0;
}

// #include "Steganography.h"
// #include <iostream>

// int main() {
//     Steganography stegoEmbed, stegoExtract;

//     // Hide message using stegoEmbed instance
//     stegoEmbed.hideMessage("input.bmp", "output.bmp", "This is a secret message.");

//     // Extract message using stegoExtract instance
//     string extractedMessage = stegoExtract.extractMessage("output.bmp");
//     cout << "Extracted Message: " << extractedMessage << endl;

//     return 0;
// }

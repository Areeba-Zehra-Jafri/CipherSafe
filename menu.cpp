#include <iostream>
#include <cstdlib>
#include <fstream>
#include <windows.h>
#include "functions.h"

using namespace std;

void welcome_screen(void)
{
    system("cls");
    char login;
    cout << "Pattern Project:" << std::endl;
    cout << "Enter S/s to start and E/e to exit" << std::endl;
    cin >> login;
    if (login == 'S' || login == 's')

    {
        system("cls");
        password_screen();
    }
    else if (login == 'E' || login == 'e')
    {
        exit(0);
    }
    else
    {
        cout << "Invalid input" << std::endl;
        welcome_screen();
    }
    cin.get();
}

void main_screen(void)
{
    system("cls");
    int choice;
    while (1)
    {
        cout << "1-Start" << std::endl;
        cout << "2-Instructions" << std::endl;
        cout << "3-Exit" << std::endl;
        cout << "4-Change login id" << std::endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "start" << std::endl;
            start_screen();
            break;
        case 2:
            cout << "instructions" << std::endl;
            instructions();
            break;
        case 3:
            exit(0);
            break;
        case 4:
            password_screen();
            break;
        default:
            cout << "Invalid input" << std::endl;
            break;
        }
    }
    cin.get();
}

void start_screen(void)
{
    system("cls");
    int choice;
    while (1)
    {
        cout << "Select one of the following: " << endl;
        cout << "1-Text Encryption/Decryption" << endl;
        cout << "2-File Encryption/Decryption" << endl;
        cout << "3-Image Encryption/Decryption (Steganography)" << endl;
        cout << "4-Go back to main" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            //cout << "Customizable Patterns" << endl;
            // customizable_screen();
            break;
        case 2:
            //cout << "Constant patterns" << endl;
            // constants_screen();
            break;
        case 3:
            //cout << "Surprise Patterns" << endl;
            // surprise_screen();
            break;
        case 4:
            main_screen();
            break;
        default:
            cout << "Invalid input" << endl;
            break;
        }
    }
    cin.get();
}

void instructions(void)
{
    system("cls");
    string line;
    ifstream in;
    in.open("instructions.txt");
    while (in.eof() == 0)
    {
        getline(in, line);
        cout << line << std::endl;
    }
    in.close();
    cin.get();
    cin.get();
}
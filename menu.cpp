#include <iostream>
#include <cstdlib>
#include <fstream>
#include <windows.h>
#include "functions.h"
#include "login.h"
#include "FileCryptography.h"
#include "Steganography.h"
#include "TextCryptography.h"
#include "HybridCryptography.h"

using namespace std;

void welcome_screen(void)
{
    system("cls");
    char login;
    cout << "  ___  __  ____  _  _  ____  ____    ____   __   ____  ____" << endl;
    cout << " / __)(  )(  _ \\/ )( \\(  __)(  _ \\  / ___) / _\\ (  __)(  __)" << endl;
    cout << "( (__  )(  ) __/) __ ( ) _)  )   /  \\___ \\/    \\ ) _)  ) _) " << endl;
    cout << " \\___)(__)(__)  \\_)(_/(____)(__\\_)  (____/\\_/\\_/(__)  (____)" << endl;
    cout << "============================================================" << endl;
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
        cout << "\033[1;31mInvalid input\033[0m" << std::endl;
        welcome_screen();
    }
    cin.get();
}

void password_screen()
{
    try
    {
        system("cls");
        Management m1;
        m1.load_accounts("data.txt");
        string username, password;
        int choice;
        while (true)
        {
            cout << "=== Password Management ===" << endl;
            cout << "1. Sign up" << endl;
            cout << "2. Change password" << endl;
            cout << "3. Login" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore();
            switch (choice)
            {
            case 1:
                cout << "=== Sign Up ===" << endl;
                cout << "--------------------" << endl;
                cout << "Enter your username: ";
                cin>>username;
                cout << "--------------------" << endl;
                cout << "--------------------" << endl;
                cout << "Enter your password: ";
                cin.ignore();
                cin>>password;
                cout << "--------------------" << endl;
                m1.sign_up(username, password);
                m1.save_accounts("data.txt");
                break;
            case 2:
                cout << "=== Change Password ===" << endl;
                cout << "--------------------" << endl;
                cout << "Enter your username: ";
                cin>>username;
                cout << "--------------------" << endl;
                cout << "--------------------" << endl;
                cout << "Enter your password: ";
                cin>>password;
                cout << "--------------------" << endl;
                m1.change_password(username, password);
                break;
            case 3:
                cout << "=== Login ===" << endl;
                cout << "--------------------" << endl;
                cout << "Enter your username: ";
                cin>>username;
                cout << "--------------------" << endl;
                cout << "--------------------" << endl;
                cout << "Enter your password: ";
                cin>>password;
                cout << "--------------------" << endl;
                m1.login(username, password);
                break;
            case 4:
                exit(0);
            default:
                cout << "\033[1;31mInvalid input.\033[0m Try again." << std::endl;
                break;
            }
        }
    }
    catch (const exception &e)
    {
        cerr << "\033[1;31mException caught in password_screen:\033[0m " << e.what() << endl;
    }
}

void main_screen(void)
{
    system("cls");
    int choice;
    while (1)
    {
        cout << "=== Main Menu ===" << endl;
        cout << "1. Start" << endl;
        cout << "2. Instructions" << endl;
        cout << "3. Exit" << endl;
        cout << "4. Change login id" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "=== Start Menu ===" << endl;
            start_screen();
            break;
        case 2:
            cout << "=== Instructions ===" << endl;
            instructions();
            break;
        case 3:
            exit(0);
            break;
        case 4:
            password_screen();
            break;
        default:
            cout << "\033[1;31mInvalid input\033[0m" << std::endl;
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
        cout << "=== Start Menu ===" << endl;
        cout << "Select one of the following: " << endl;
        cout << "1-Text Encryption/Decryption" << endl;
        cout << "2-File Encryption/Decryption" << endl;
        cout << "3-Image Encryption/Decryption (Steganography)" << endl;
        cout << "4-Hybrid Encryption/Decryption" << endl;
        cout << "5-Go back to main" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "=== Text Encryption/Decryption ===" << endl;
            TextCryptography textCrypt;
            textCrypt.processText();
            break;
        case 2:
            cout << "=== File Encryption/Decryption ===" << endl;
            FileCryptography fileCrypt;
            fileCrypt.processFiles();
            break;
        case 3:
            cout << "=== Image Encryption/Decryption (Steganography) ===" << endl;
            Steganography stego;
            stego.runSteganography(stego);
            break;
        case 4:
            cout << "=== Hybrid Encryption/Decryption ===" << endl;
            HybridCryptography hybrid;
            hybrid.processTextHybrid();
            break;
        case 5:
            main_screen();
            break;
        default:
            cout << "\033[1;31mInvalid input\033[0m" << endl;
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
    in.open("instruction.txt");
    while (in.eof() == 0)
    {
        getline(in, line);
        cout << line << std::endl;
    }
    in.close();
    cin.get();
    cin.get();
}
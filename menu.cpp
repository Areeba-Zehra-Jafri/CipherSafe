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
    cout << " / __)(  )(  _ \\/ )( \\(  __)(  _ \\  / ___) / _\\ (  __)(  __)"<< endl;
    cout << "( (__  )(  ) __/) __ ( ) _)  )   /  \\___ \\/    \\ ) _)  ) _) "<<endl;
    cout << " \\___)(__)(__)  \\_)(_/(____)(__\\_)  (____/\\_/\\_/(__)  (____)" <<endl; 
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
            cout << "1. Sign_up\n2. Change password\n3. Login\n4. Exit\nEnter choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                cout << "Enter your username: ";
                cin >> username;
                cout << "Enter your password: ";
                cin >> password;
                m1.sign_up(username, password);
                m1.save_accounts("data.txt");
                break;
            case 2:
                cout << "Enter your username: ";
                cin >> username;
                cout << "Enter your password: ";
                cin >> password;
                m1.change_password(username, password);
                break;
            case 3:
                cout << "Enter your username: ";
                cin >> username;
                cout << "Enter your password: ";
                cin >> password;
                m1.login(username, password);
                break;
            case 4:
                exit(0);
            default:
                cout << "Invalid input. Try again." << std::endl;
                break;
            }
        }
    }
    catch (const exception &e)
    {
        cerr << "Exception caught in password_screen: " << e.what() << endl;
    }
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
        cout << "4-Hybrid Encryption/Decryption" << endl;
        cout << "6-Go back to main" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Text Encryption/Decryption" << endl;
            TextCryptography textCrypt;
            textCrypt.processText();
            break;
        case 2:
            cout << "File Encryption/Decryption" << endl;
            FileCryptography fileCrypt;
            fileCrypt.processFiles();
            break;
        case 3:
            cout << "Image Encryption/Decryption (Steganography)" << endl;
            Steganography stego;
            stego.runSteganography(stego);
            break;
        case 4:
            cout << "Hybrid Encryption/Decryption" << endl;
            HybridCryptography hybrid;
            hybrid.processTextHybrid();
            break;
        case 6:
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
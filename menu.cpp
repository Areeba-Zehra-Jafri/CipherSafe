#include <iostream>
#include <cstdlib>
#include <fstream>
#include <windows.h>
#include <conio.h> // For _getch()
#include <regex> // For regex and regex_match
#include <limits>
#include "functions.h"
#include "login.h"
#include "FileCryptography.h"
#include "Steganography.h"
#include "TextCryptography.h"
#include "HybridCryptography.h"
#include "login.h"

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

// void password_screen()
// {
//     try
//     {
//         system("cls");
//         Management m1;
//         string username, password;
//         int choice;
//         while (true)
//         {
//             cout << "\033[1;33m=== Password Management ===\033[0m" << endl;
//             cout << "1. Sign up" << endl;
//             cout << "2. Change password" << endl;
//             cout << "3. Login" << endl;
//             cout << "4. Exit" << endl;
//             cout << "Enter choice: ";
//             cin >> choice;
//             cin.ignore();
//             switch (choice)
//             {
//             case 1:
//                 cout << "\033[1;33m=== Sign Up ===\033[0m" << endl;
//                 cout << "--------------------" << endl;
//                 cout << "Enter your username: ";
//                 cin >> username;
//                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
//                 cout << "--------------------" << endl;
//                 cout << "--------------------" << endl;
//                 cout << "Enter your password: ";
//                 cin >> password;
//                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
//                 // cin.ignore();
//                 cout << "--------------------" << endl;
//                 m1.sign_up(username, password);
//                 break;
//             case 2:
//                 cout << "\033[1;33m=== Change Password ===\033[0m" << endl;
//                 cout << "--------------------" << endl;
//                 cout << "Enter your username: ";
//                 cin >> username;
//                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
//                 cout << "--------------------" << endl;
//                 cout << "--------------------" << endl;
//                 cout << "Enter your password: ";
//                 cin >> password;
//                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
//                 cout << "--------------------" << endl;
//                 m1.change_password(username, password);
//                 break;
//             case 3:
//                 cout << "\033[1;33m=== Login ===\033[0m" << endl;
//                 cout << "--------------------" << endl;
//                 cout << "Enter your username: ";
//                 cin >> username;
//                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
//                 cout << "--------------------" << endl;
//                 cout << "--------------------" << endl;
//                 cout << "Enter your password: ";
//                 cin >> password;
//                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
//                 cout << "--------------------" << endl;
//                 m1.login(username, password);
//                 break;
//             case 4:
//                 exit(0);
//             default:
//                 cout << "\033[1;31mInvalid input.\033[0m Try again." << std::endl;
//                 break;
//             }
//         }
//     }
//     catch (const exception &e)
//     {
//         cerr << "\033[1;31mException caught in password_screen:\033[0m " << e.what() << endl;
//     }
// }

// Function to validate the password
bool validate_password(const string &password) {
    if (password.length() < 8)
        return false;
    bool has_upper = false, has_digit = false, has_special = false;
    for (char c : password) {
        if (isupper(c)) has_upper = true;
        if (isdigit(c)) has_digit = true;
        if (ispunct(c)) has_special = true;
    }
    return has_upper && has_digit && has_special;
}

// Function to get the password input with masking
string get_password() {
    string password;
    char ch;
    cout << "Enter your password: ";
    while (true) {
        ch = _getch(); // Read a character without echoing it
        if (ch == 13) break; // Enter key pressed
        if (ch == 8) { // Backspace key pressed
            if (!password.empty()) {
                cout << "\b \b"; // Remove the last '*' from console
                password.pop_back(); // Remove last character from password string
            }
        } else {
            password.push_back(ch);
            cout << '*'; // Print '*' instead of the actual character
        }
    }
    cout << endl;

    if (!validate_password(password)) {
        cout << "\033[1;31mPassword must be at least 8 characters long, contain at least one uppercase letter, one digit, and one special character.\033[0m" << endl;
        return get_password();
    }
    return password;
}

void password_screen() {
    try {
        system("cls");
        Management m1;
        string username, password;
        int choice;
        while (true) {
            cout << "\033[1;33m=== Password Management ===\033[0m" << endl;
            cout << "1. Sign up" << endl;
            cout << "2. Change password" << endl;
            cout << "3. Login" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore();
            switch (choice) {
            case 1:
                cout << "\033[1;33m=== Sign Up ===\033[0m" << endl;
                cout << "--------------------" << endl;
                cout << "Enter your username: ";
                cin >> username;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "--------------------" << endl;
                password = get_password();
                cout << "--------------------" << endl;
                m1.sign_up(username, password);
                break;
            case 2:
                cout << "\033[1;33m=== Change Password ===\033[0m" << endl;
                cout << "--------------------" << endl;
                cout << "Enter your username: ";
                cin >> username;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "--------------------" << endl;
                password = get_password();
                cout << "--------------------" << endl;
                m1.change_password(username, password);
                break;
            case 3:
                cout << "\033[1;33m=== Login ===\033[0m" << endl;
                cout << "--------------------" << endl;
                cout << "Enter your username: ";
                cin >> username;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "--------------------" << endl;
                password = get_password();
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
    } catch (const exception &e) {
        cerr << "\033[1;31mException caught in password_screen:\033[0m " << e.what() << endl;
    }
}

void main_screen(void)
{
    system("cls");
    int choice;
    while (1)
    {
        cout << "\033[1;33m=== Main Menu ===\033[0m" << endl;
        cout << "1. Start" << endl;
        cout << "2. Instructions" << endl;
        cout << "3. Display User Stats" << endl;
        cout << "4. Log Out" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "\033[1;33m=== Start Menu ===\033[0m" << endl;
            start_screen();
            break;
        case 2:
            cout << "\033[1;33m=== Instructions ===\033[0m" << endl;
            instructions();
            break;
        case 3:
            Management m1;
            m1.displayCurrentStats(m1.getCurrentUsername());
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
        cout << "\033[1;33m=== Start Menu ===\033[0m" << endl;
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
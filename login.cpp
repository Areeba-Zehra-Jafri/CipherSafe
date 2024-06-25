#include <iostream>
#include "functions.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Management
{
private:
    struct Account
    {
        string username;
        string password;
    };

public:
    vector<Account> accounts;

    void load_accounts(const string &filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        Account temp;
        while (file >> temp.username >> temp.password)
        {
            accounts.push_back(temp);
        }

        file.close();
    }

    void save_accounts(const std::string &filename)
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        for (const auto &acc : accounts)
        {
            file << acc.username << " " << acc.password << endl;
        }

        file.close();
    }

    void sign_up(const string &username, const string &password)
    {
        system("cls");
        for (const auto &acc : accounts)
        {
            if (acc.username == username)
            {
                cout << "This username already exists. Please choose a different username" << endl;
                return;
            }
        }
        Account new_account;
        new_account.username = username;
        new_account.password = password;
        accounts.push_back(new_account);
        cout << "Account created successfully!" << std::endl;
    }

    void change_password(const std::string &username, const std::string &password)
    {
        system("cls");
        string pass;
        for (auto it = accounts.begin(); it != accounts.end(); ++it)
        {
            if (it->username == username)
            {
                if (it->password == password)
                {
                    cout << "Enter your new password: ";
                    cin >> pass;
                    it->password = pass;
                    cout << "Password changed successfully!" << endl;
                    return;
                }
                else
                {
                    cout << "Invalid password";
                    return;
                }
            }
        }
        cout << "Account not found." << std::endl;
    }

    void login(const string &username, const string &password)
    {
        system("cls");
        for (const auto &acc : accounts)
        {
            if (acc.username == username && acc.password == password)
            {
                cout << "Login successful!" << std::endl;
                main_screen();
                return;
            }
        }
        cout << "Invalid username or password. Try again." << endl;
    }
};

void password_screen(void)
{
    system("cls");
    Management m1;
    m1.load_accounts("data.txt");
    string username, password;
    int choice;
    while (1)
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
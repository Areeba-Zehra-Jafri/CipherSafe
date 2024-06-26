#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include "functions.h"
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
        try
        {
            ifstream file(filename);
            if (!file.is_open())
            {
                throw runtime_error("Error opening file: " + filename);
            }

            Account temp;
            while (file >> temp.username >> temp.password)
            {
                accounts.push_back(temp);
            }

            file.close();
        }
        catch (const exception &e)
        {
            cerr << "Exception caught in load_accounts: " << e.what() << endl;
        }
    }

    void save_accounts(const std::string &filename)
    {
        try
        {
            ofstream file(filename);
            if (!file.is_open())
            {
                throw runtime_error("Error opening file: " + filename);
            }

            for (const auto &acc : accounts)
            {
                file << acc.username << " " << acc.password << endl;
            }

            file.close();
        }
        catch (const exception &e)
        {
            cerr << "Exception caught in save_accounts: " << e.what() << endl;
        }
    }

    void sign_up(const string &username, const string &password)
    {
        try
        {
            system("cls");
            for (const auto &acc : accounts)
            {
                if (acc.username == username)
                {
                    throw runtime_error("This username already exists. Please choose a different username.");
                }
            }
            Account new_account;
            new_account.username = username;
            new_account.password = password;
            accounts.push_back(new_account);
            cout << "Account created successfully!" << std::endl;
        }
        catch (const exception &e)
        {
            cerr << "Exception caught in sign_up: " << e.what() << endl;
        }
    }

    void change_password(const std::string &username, const std::string &password)
    {
        try
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
                        throw invalid_argument("Invalid password.");
                    }
                }
            }
            throw runtime_error("Account not found.");
        }
        catch (const exception &e)
        {
            cerr << "Exception caught in change_password: " << e.what() << endl;
        }
    }

    void login(const string &username, const string &password)
    {
        try
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
            throw runtime_error("Invalid username or password. Try again.");
        }
        catch (const exception &e)
        {
            cerr << "Exception caught in login: " << e.what() << endl;
        }
    }
};

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

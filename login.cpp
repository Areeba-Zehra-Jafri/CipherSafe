#include "login.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

void Management::load_accounts(const std::string &filename)
{
    try
    {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open())
        {
            throw std::runtime_error("\033[1;31mError opening file: " + filename + "\033[0m");
        }

        Account temp;
        while (file.peek() != EOF)
        {
            deserialize(temp, file);
            accounts.push_back(temp);
        }

        file.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << "\033[1;31mException caught in load_accounts: " << e.what() << "\033[0m" << std::endl;
    }
}

void Management::save_accounts(const std::string &filename)
{
    try
    {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open())
        {
            throw std::runtime_error("\033[1;31mError opening file: " + filename + "\033[0m");
        }

        for (const auto &acc : accounts)
        {
            serialize(acc, file);
        }

        file.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << "\033[1;31mException caught in save_accounts: " << e.what() << "\033[0m" << std::endl;
    }
}

void Management::sign_up(const std::string &username, const std::string &password)
{
    try
    {
        system("cls");
        for (const auto &acc : accounts)
        {
            if (acc.username == username)
            {
                throw std::runtime_error("\033[1;31mThis username already exists. Please choose a different username.\033[0m");
            }
        }
        Account new_account;
        new_account.username = username;
        new_account.password = password;
        accounts.push_back(new_account);
        std::cout << "\n\033[1;34m---------------------------\n";
        std::cout << " Account created successfully! ";
        std::cout << "\n---------------------------\033[0m\n"
                  << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "\033[1;31mException caught in sign_up: " << e.what() << "\033[0m" << std::endl;
    }
}

void Management::change_password(const std::string &username, const std::string &password)
{
    try
    {
        system("cls");
        std::string pass;
        for (auto it = accounts.begin(); it != accounts.end(); ++it)
        {
            if (it->username == username)
            {
                if (it->password == password)
                {
                    std::cout << "Enter your new password: ";
                    std::cin >> pass;
                    it->password = pass;
                    std::cout << "\n\033[1;34m---------------------------\n";
                    std::cout << " Password changed successfully! ";
                    std::cout << "\n---------------------------\033[0m\n"
                              << std::endl;
                    return;
                }
                else
                {
                    throw std::invalid_argument("\033[1;31mInvalid password.\033[0m");
                }
            }
        }
        throw std::runtime_error("\033[1;31mAccount not found.\033[0m");
    }
    catch (const std::exception &e)
    {
        std::cerr << "\033[1;31mException caught in change_password: " << e.what() << "\033[0m" << std::endl;
    }
}

void Management::login(const std::string &username, const std::string &password)
{
    try
    {
        system("cls");
        for (const auto &acc : accounts)
        {
            if (acc.username == username && acc.password == password)
            {
                std::cout << "\n\033[1;34m---------------------------\n";
                std::cout << " Login successfull! ";
                std::cout << "\n---------------------------\033[0m\n"
                          << std::endl;
                main_screen();
                return;
            }
        }
        throw std::runtime_error("\033[1;31mInvalid username or password. Try again.\033[0m");
    }
    catch (const std::exception &e)
    {
        std::cerr << "\033[1;31mException caught in login: " << e.what() << "\033[0m" << std::endl;
    }
}

void Management::serialize(const Account &account, std::ofstream &file)
{
    size_t username_size = account.username.size();
    file.write(reinterpret_cast<const char *>(&username_size), sizeof(username_size));
    file.write(account.username.c_str(), username_size);

    size_t password_size = account.password.size();
    file.write(reinterpret_cast<const char *>(&password_size), sizeof(password_size));
    file.write(account.password.c_str(), password_size);
}

void Management::deserialize(Account &account, std::ifstream &file)
{
    size_t username_size;
    file.read(reinterpret_cast<char *>(&username_size), sizeof(username_size));
    account.username.resize(username_size);
    file.read(&account.username[0], username_size);

    size_t password_size;
    file.read(reinterpret_cast<char *>(&password_size), sizeof(password_size));
    account.password.resize(password_size);
    file.read(&account.password[0], password_size);
}

#include "login.h"

void Management::load_accounts(const std::string &filename)
{
    try
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Error opening file: " + filename);
        }

        Account temp;
        while (file >> temp.username >> temp.password)
        {
            accounts.push_back(temp);
        }

        file.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception caught in load_accounts: " << e.what() << std::endl;
    }
}

void Management::save_accounts(const std::string &filename)
{
    try
    {
        std::ofstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Error opening file: " + filename);
        }

        for (const auto &acc : accounts)
        {
            file << acc.username << " " << acc.password << std::endl;
        }

        file.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception caught in save_accounts: " << e.what() << std::endl;
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
                throw std::runtime_error("This username already exists. Please choose a different username.");
            }
        }
        Account new_account;
        new_account.username = username;
        new_account.password = password;
        accounts.push_back(new_account);
        std::cout << "Account created successfully!" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception caught in sign_up: " << e.what() << std::endl;
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
                    std::cout << "Password changed successfully!" << std::endl;
                    return;
                }
                else
                {
                    throw std::invalid_argument("Invalid password.");
                }
            }
        }
        throw std::runtime_error("Account not found.");
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception caught in change_password: " << e.what() << std::endl;
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
                std::cout << "Login successful!" << std::endl;
                main_screen();
                return;
            }
        }
        throw std::runtime_error("Invalid username or password. Try again.");
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception caught in login: " << e.what() << std::endl;
    }
}

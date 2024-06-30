// #ifndef MANAGEMENT_H
// #define MANAGEMENT_H

// #include <iostream>
// #include <string>
// #include <vector>
// #include <fstream>
// #include <stdexcept>
// #include"functions.h"

// class Management
// {
// private:
//     struct Account
//     {
//         std::string username;
//         std::string password;
//     };

// public:
//     std::vector<Account> accounts;

//     void load_accounts(const std::string &filename);
//     void save_accounts(const std::string &filename);
//     void sign_up(const std::string &username, const std::string &password);
//     void change_password(const std::string &username, const std::string &password);
//     void login(const std::string &username, const std::string &password);
// };

// #endif // MANAGEMENT_H

#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include "functions.h"

struct Account {
    std::string username;
    std::string password;
};

class Management {
private:
    std::vector<Account> accounts;
    void serialize(const Account& account, std::ofstream& file);
    void deserialize(Account& account, std::ifstream& file);

public:
    void load_accounts(const std::string &filename);
    void save_accounts(const std::string &filename);
    void sign_up(const std::string &username, const std::string &password);
    void change_password(const std::string &username, const std::string &password);
    void login(const std::string &username, const std::string &password);
};

#endif // LOGIN_H

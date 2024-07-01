#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include "functions.h"

using namespace std;

struct Account {
    string username;
    string password;
};

class Management {
private:
    vector<Account> accounts;
    void serialize(const Account& account, ofstream& file);
    void deserialize(Account& account, ifstream& file);

public:
    void load_accounts(const string &filename);
    void save_accounts(const string &filename);
    void sign_up(const string &username, const string &password);
    void change_password(const string &username, const string &password);
    void login(const string &username, const string &password);
};

#endif 

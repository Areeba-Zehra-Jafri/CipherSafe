// #ifndef LOGIN_H
// #define LOGIN_H

// #include <string>
// #include <vector>
// #include <fstream>
// #include <iostream>
// #include <stdexcept>
// #include <cstdlib>
// #include "functions.h"

// using namespace std;

// struct Account {
//     string username;
//     string password;
// };

// class Management {
// private:
//     vector<Account> accounts;
//     void serialize(const Account& account, ofstream& file);
//     void deserialize(Account& account, ifstream& file);

// public:
//     void load_accounts(const string &filename);
//     void save_accounts(const string &filename);
//     void sign_up(const string &username, const string &password);
//     void change_password(const string &username, const string &password);
//     void login(const string &username, const string &password);
// };

// #endif 
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
    int filesEncrypted=0;
    int filesDecrypted=0;
    int textLinesEncrypted=0;
    int textLinesDecrypted=0;
    int textEmbeddedCount=0;
    int textExtractedCount=0;
    int textEncryptedEmbedded=0;
    int textDecryptedExtracted=0;
};

class Management {
public:
    void sign_up(const string &username, const string &password);
    void change_password(const string &username, const string &password);
    void login(const string &username, const string &password);
    void updateFilesEncrypted(const string &username);
    void updateFilesDecrypted(const string &username);
    void updateTextLinesEncrypted(const string &username);
    void updateTextLinesDecrypted(const string &username);
    void updateTextEmbeddedCount(const string &username);
    void updateTextExtractedCount(const string &username);
    void updateTextEncryptedEmbedded(const std::string &username);
    void updateTextDecryptedExtracted(const std::string &username);
    void displayCurrentStats(const string &username) ;
    static void setCurrentUsername(const string &username);
    static string getCurrentUsername() ;

private:
    void serialize(const Account &account, ostream &file) const;
    void deserialize(Account &account, istream &file);
    static string currentUsername;
};


#endif 

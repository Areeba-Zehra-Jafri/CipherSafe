#include "login.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

string Management::currentUsername = "";

void Management::sign_up(const std::string &username, const std::string &password)
{
    try
    {
        // Check if the username already exists
        std::ifstream file_read("accounts.bin", std::ios::binary);
        if (!file_read.is_open())
        {
            throw std::runtime_error("\033[1;31mError opening file: accounts.bin\033[0m");
        }

        Account temp;
        while (file_read.peek() != EOF)
        {
            deserialize(temp, file_read);
            if (temp.username == username)
            {
                file_read.close();
                throw std::runtime_error("\033[1;31mThis username already exists. Please choose a different username.\033[0m");
            }
        }
        file_read.close();

        // Add the new account
        std::ofstream file_write("accounts.bin", std::ios::binary | std::ios::app);
        if (!file_write.is_open())
        {
            throw std::runtime_error("\033[1;31mError opening file: accounts.bin\033[0m");
        }

        Account new_account;
        new_account.username = username;
        new_account.password = password;
        serialize(new_account, file_write);
        file_write.close();

        std::cout << "\n\033[1;34m---------------------------\n";
        std::cout << " Account created successfully! ";
        std::cout << "\n---------------------------\033[0m\n" << std::endl;
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
        std::fstream file("accounts.bin", std::ios::in | std::ios::out | std::ios::binary);
        if (!file.is_open())
        {
            throw std::runtime_error("\033[1;31mError opening file: accounts.bin\033[0m");
        }

        Account temp;
        std::streampos pos;
        bool account_found = false;
        while (file.peek() != EOF)
        {
            pos = file.tellg();
            deserialize(temp, file);
            if (temp.username == username)
            {
                if (temp.password == password)
                {
                    std::cout << "Enter your new password: ";
                    std::string new_password;
                    std::cin >> new_password;
                    temp.password = new_password;

                    file.seekp(pos);
                    serialize(temp, file);

                    std::cout << "\n\033[1;34m---------------------------\n";
                    std::cout << " Password changed successfully! ";
                    std::cout << "\n---------------------------\033[0m\n" << std::endl;

                    account_found = true;
                    break;
                }
                else
                {
                    throw std::invalid_argument("\033[1;31mInvalid password.\033[0m");
                }
            }
        }
        file.close();

        if (!account_found)
        {
            throw std::runtime_error("\033[1;31mAccount not found.\033[0m");
        }
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
        std::ifstream file("accounts.bin", std::ios::binary);
        if (!file.is_open())
        {
            throw std::runtime_error("\033[1;31mError opening file: accounts.bin\033[0m");
        }

        bool login_successful = false;
        Account temp;
        while (file.peek() != EOF)
        {
            deserialize(temp, file);
            if (temp.username == username && temp.password == password)
            {
                std::cout << "\n\033[1;34m---------------------------\n";
                std::cout << " Login successful! ";
                std::cout << "\n---------------------------\033[0m\n" << std::endl;
                login_successful = true;
                setCurrentUsername(username);
                main_screen();
                break;
            }
        }
        file.close();

        if (!login_successful)
        {
            throw std::runtime_error("\033[1;31mInvalid username or password. Try again.\033[0m");
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "\033[1;31mException caught in login: " << e.what() << "\033[0m" << std::endl;
    }
}

void Management::updateFilesEncrypted(const std::string &username)
{
    try
    {
        std::fstream file("accounts.bin", std::ios::in | std::ios::out | std::ios::binary);
        if (!file.is_open())
        {
            throw std::runtime_error("\033[1;31mError opening file: accounts.bin\033[0m");
        }

        Account temp;
        std::streampos pos;
        while (file.peek() != EOF)
        {
            pos = file.tellg();
            deserialize(temp, file);
            if (temp.username == username)
            {
                temp.filesEncrypted++;
                file.seekp(pos);
                serialize(temp, file);
                file.close();
                return;
            }
        }
        file.close();
        throw std::runtime_error("Account not found.");
    }
    catch (const std::exception &e)
    {
        std::cerr << "\033[1;31mException caught in updateFilesEncrypted: " << e.what() << "\033[0m" << std::endl;
    }
}

void Management::updateFilesDecrypted(const std::string &username)
{
    try
    {
        std::fstream file("accounts.bin", std::ios::in | std::ios::out | std::ios::binary);
        if (!file.is_open())
        {
            throw std::runtime_error("\033[1;31mError opening file: accounts.bin\033[0m");
        }

        Account temp;
        std::streampos pos;
        while (file.peek() != EOF)
        {
            pos = file.tellg();
            deserialize(temp, file);
            if (temp.username == username)
            {
                temp.filesDecrypted++;
                file.seekp(pos);
                serialize(temp, file);
                file.close();
                return;
            }
        }
        file.close();
        throw std::runtime_error("Account not found.");
    }
    catch (const std::exception &e)
    {
        std::cerr << "\033[1;31mException caught in updateFilesDecrypted: " << e.what() << "\033[0m" << std::endl;
    }
}

void Management::updateTextLinesEncrypted(const std::string &username)
{
    try
    {
        std::fstream file("accounts.bin", std::ios::in | std::ios::out | std::ios::binary);
        if (!file.is_open())
        {
            throw std::runtime_error("\033[1;31mError opening file: accounts.bin\033[0m");
        }

        Account temp;
        std::streampos pos;
        while (file.peek() != EOF)
        {
            pos = file.tellg();
            deserialize(temp, file);
            if (temp.username == username)
            {
                temp.textLinesEncrypted++;
                file.seekp(pos);
                serialize(temp, file);
                file.close();
                return;
            }
        }
        file.close();
        throw std::runtime_error("Account not found.");
    }
    catch (const std::exception &e)
    {
        std::cerr << "\033[1;31mException caught in updateTextLinesEncrypted: " << e.what() << "\033[0m" << std::endl;
    }
}

void Management::updateTextLinesDecrypted(const std::string &username)
{
    try
    {
        std::fstream file("accounts.bin", std::ios::in | std::ios::out | std::ios::binary);
        if (!file.is_open())
        {
            throw std::runtime_error("\033[1;31mError opening file: accounts.bin\033[0m");
        }

        Account temp;
        std::streampos pos;
        while (file.peek() != EOF)
        {
            pos = file.tellg();
            deserialize(temp, file);
            if (temp.username == username)
            {
                temp.textLinesDecrypted++;
                file.seekp(pos);
                serialize(temp, file);
                file.close();
                return;
            }
        }
        file.close();
        throw std::runtime_error("Account not found.");
    }
    catch (const std::exception &e)
    {
        std::cerr << "\033[1;31mException caught in updateTextLinesDecrypted: " << e.what() << "\033[0m" << std::endl;
    }
}

void Management::updateTextEmbeddedCount(const std::string &username)
{
    try
    {
        std::fstream file("accounts.bin", std::ios::in | std::ios::out | std::ios::binary);
        if (!file.is_open())
        {
            throw std::runtime_error("\033[1;31mError opening file: accounts.bin\033[0m");
        }

        Account temp;
        std::streampos pos;
        while (file.peek() != EOF)
        {
            pos = file.tellg();
            deserialize(temp, file);
            if (temp.username == username)
            {
                temp.textEmbeddedCount++;
                file.seekp(pos);
                serialize(temp, file);
                file.close();
                return;
            }
        }
        file.close();
        throw std::runtime_error("Account not found.");
    }
    catch (const std::exception &e)
    {
        std::cerr << "\033[1;31mException caught in updateTextEmbeddedCount: " << e.what() << "\033[0m" << std::endl;
    }
}

void Management::updateTextExtractedCount(const std::string &username)
{
    try
    {
        std::fstream file("accounts.bin", std::ios::in | std::ios::out | std::ios::binary);
        if (!file.is_open())
        {
            throw std::runtime_error("\033[1;31mError opening file: accounts.bin\033[0m");
        }

        Account temp;
        std::streampos pos;
        while (file.peek() != EOF)
        {
            pos = file.tellg();
            deserialize(temp, file);
            if (temp.username == username)
            {
                temp.textExtractedCount++;
                file.seekp(pos);
                serialize(temp, file);
                file.close();
                return;
            }
        }
        file.close();
        throw std::runtime_error("Account not found.");
    }
    catch (const std::exception &e)
    {
        std::cerr << "\033[1;31mException caught in updateTextExtractedCount: " << e.what() << "\033[0m" << std::endl;
    }
}

void Management::updateTextEncryptedEmbedded(const std::string &username)
{
    try
    {
        std::fstream file("accounts.bin", std::ios::in | std::ios::out | std::ios::binary);
        if (!file.is_open())
        {
            throw std::runtime_error("\033[1;31mError opening file: accounts.bin\033[0m");
        }

        Account temp;
        std::streampos pos;
        while (file.peek() != EOF)
        {
            pos = file.tellg();
            deserialize(temp, file);
            if (temp.username == username)
            {
                // Increment the count for text encrypted and embedded
                temp.textEncryptedEmbedded++;
                
                file.seekp(pos);
                serialize(temp, file);
                file.close();
                return;
            }
        }
        file.close();
        throw std::runtime_error("Account not found.");
    }
    catch (const std::exception &e)
    {
        std::cerr << "\033[1;31mException caught in updateTextEncryptedEmbedded: " << e.what() << "\033[0m" << std::endl;
    }
}

void Management::updateTextDecryptedExtracted(const std::string &username)
{
    try
    {
        std::fstream file("accounts.bin", std::ios::in | std::ios::out | std::ios::binary);
        if (!file.is_open())
        {
            throw std::runtime_error("\033[1;31mError opening file: accounts.bin\033[0m");
        }

        Account temp;
        std::streampos pos;
        while (file.peek() != EOF)
        {
            pos = file.tellg();
            deserialize(temp, file);
            if (temp.username == username)
            {
                // Increment the count for text decrypted and extracted
                temp.textDecryptedExtracted++;
                
                file.seekp(pos);
                serialize(temp, file);
                file.close();
                return;
            }
        }
        file.close();
        throw std::runtime_error("Account not found.");
    }
    catch (const std::exception &e)
    {
        std::cerr << "\033[1;31mException caught in updateTextDecryptedExtracted: " << e.what() << "\033[0m" << std::endl;
    }
}


void Management::serialize(const Account &account, ostream &file) const
{
    size_t username_size = account.username.size();
    file.write(reinterpret_cast<const char *>(&username_size), sizeof(username_size));
    file.write(account.username.c_str(), username_size);

    size_t password_size = account.password.size();
    file.write(reinterpret_cast<const char *>(&password_size), sizeof(password_size));
    file.write(account.password.c_str(), password_size);

    file.write(reinterpret_cast<const char *>(&account.filesEncrypted), sizeof(account.filesEncrypted));
    file.write(reinterpret_cast<const char *>(&account.filesDecrypted), sizeof(account.filesDecrypted));
    file.write(reinterpret_cast<const char *>(&account.textLinesEncrypted), sizeof(account.textLinesEncrypted));
    file.write(reinterpret_cast<const char *>(&account.textLinesDecrypted), sizeof(account.textLinesDecrypted));
    file.write(reinterpret_cast<const char *>(&account.textEmbeddedCount), sizeof(account.textEmbeddedCount));
    file.write(reinterpret_cast<const char *>(&account.textExtractedCount), sizeof(account.textExtractedCount));
}

void Management::deserialize(Account &account, istream &file)
{
    size_t username_size;
    file.read(reinterpret_cast<char *>(&username_size), sizeof(username_size));
    account.username.resize(username_size);
    file.read(&account.username[0], username_size);

    size_t password_size;
    file.read(reinterpret_cast<char *>(&password_size), sizeof(password_size));
    account.password.resize(password_size);
    file.read(&account.password[0], password_size);

    file.read(reinterpret_cast<char *>(&account.filesEncrypted), sizeof(account.filesEncrypted));
    file.read(reinterpret_cast<char *>(&account.filesDecrypted), sizeof(account.filesDecrypted));
    file.read(reinterpret_cast<char *>(&account.textLinesEncrypted), sizeof(account.textLinesEncrypted));
    file.read(reinterpret_cast<char *>(&account.textLinesDecrypted), sizeof(account.textLinesDecrypted));
    file.read(reinterpret_cast<char *>(&account.textEmbeddedCount), sizeof(account.textEmbeddedCount));
    file.read(reinterpret_cast<char *>(&account.textExtractedCount), sizeof(account.textExtractedCount));
}

void Management::displayCurrentStats(const string &username)
{
    try
    {
        ifstream file("accounts.bin", ios::binary);
        if (!file.is_open())
        {
            throw runtime_error("\033[1;31mError opening file: accounts.bin\033[0m");
        }

        bool found = false;
        Account temp; // Object to deserialize into
        while (file.peek() != EOF)
        {
            deserialize(temp, file); // Deserialize into temp
            if (temp.username == username)
            {
                found = true;
                cout << "\n\033[1;34m---------------------------\n";
                cout << " Current Statistics for " << username << " ";
                cout << "\n---------------------------\033[0m\n" << endl;
                cout << "Username: " << temp.username << endl;
                cout << "Files Encrypted: " << temp.filesEncrypted << endl;
                cout << "Files Decrypted: " << temp.filesDecrypted << endl;
                cout << "Text Lines Encrypted: " << temp.textLinesEncrypted << endl;
                cout << "Text Lines Decrypted: " << temp.textLinesDecrypted << endl;
                cout << "Text Embedded Count: " << temp.textEmbeddedCount << endl;
                cout << "Text Extracted Count: " << temp.textExtractedCount << endl;
                cout << "Text Encrypted and Embedded Count " <<temp.textEncryptedEmbedded << endl;
                cout << "Text Decrypted and Extracted Count " <<temp.textDecryptedExtracted << endl;
                cout << "---------------------------" << endl;
                break; // Exit loop once found
            }
        }

        file.close();

        if (!found)
        {
            cerr << "\033[1;31mUser " << username << " not found.\033[0m" << endl;
        }
    }
    catch (const exception &e)
    {
        cerr << "\033[1;31mException caught in displayCurrentStats: " << e.what() << "\033[0m" << endl;
    }
}

void Management::setCurrentUsername(const string &username)
{
    currentUsername = username;
}

// Getter implementation
string Management::getCurrentUsername() 
{
    return currentUsername;
}


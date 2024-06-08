
#include<string>
#ifndef _VERNAMCIPHER_
#define _VERNAMCIPHER_

using namespace std;

class vernamcipher
{
    private:
    //key given by user
    string key;

    /*char normalizeChar(char c) const;
    char denormalizeChar(char c) const;
*/
    public:

    //Constructor
    vernamcipher(const string &key);

    //Encryption function

    string encrypt(const string &plaintext)const ;

    //Decryption function

    string decrypt(const string &encryptedtext) const;

    //Encryption of a file

    void encryptFile(const string& inputFilePath, const string& outputFilePath) const ;

    //Decryption of a file

    void decryptFile(const string& inputFilePath, const string& outputFilePath) const    ;


};


#endif
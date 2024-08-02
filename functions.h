#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include<string>
#include<vector>

using namespace std;

void welcome_screen(void);
void password_screen();
void main_screen(void);
void start_screen(void);
void instructions(void);
string get_password();
bool validate_password(const string &password);

#endif
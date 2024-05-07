#pragma once
#include"Thu_vien.h"
#include"Send.h"

void FixConsoleWindow();
void setcolor(int backgound_color, int text_color);
void gotoXY(int column, int line);
void hideCursor();
void showCursor();
void Sign_In(char username[], char password[], char sender[], char MailSever[], int& portSMTP, int& portPop3, int& AutoLoad, char address_downloaded_file[]);
void Write_Config_TO_xml(char username[], char password[], char sender[], char MailServer[], int portSMTP, int portPop3, int AutoLoad, char address_downloaded_file[]);
void Sign_Up(char username[], char password[], char sender[], char MailSever[], int& portSMTP, int& portPop3, int& AutoLoad, char address_downloaded_file[]);
string seclectmchat();
void Menu(char username[], char password[], char sender[], char MailSever[], int& portSMTP, int& portPop3, int& AutoLoad, char address_downloaded_file[], char recipient[], char subject[], char body[], char CC[], char BCC[], link_file L[], int& count_file);
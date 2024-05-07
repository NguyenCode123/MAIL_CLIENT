#pragma once
#include"Thu_vien.h"

struct link_file
{
	char link[100];
};

void Data_Entry(char recipient[], char subject[], char body[], char CC[], char BCC[], link_file L[], int& count_file);
void Send_Email(const char* server, int port, const char* username, const char* sender, char* recipient, const char* subject, char* CC, char* BCC, char* body, link_file L[], int count_file);
string read_binary_file(const string& filename);
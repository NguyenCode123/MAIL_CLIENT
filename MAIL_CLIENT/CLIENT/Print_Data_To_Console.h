#pragma once
#include"Thu_vien.h"

struct Find_txt_mail_content
{
	char dia_chi[200];
	char number[200];
	char subject[200];
};

string base64_decode(const string& input);
void Return_Unsername_Folder_Address(const char* sender, char file_name[], int Command);
void Print_Name_The_Sender_And_Subject(const char* sender, Find_txt_mail_content Find[], int& count, int number_folder);
void Command_To_Choose_File(const char* sender, Find_txt_mail_content Find[], int number_folder, char address_downloaded_file[]);
void thread_Auto_Download_Mail(const char* server, int port, const char* username, const char* password, int AutoLoad);
void Read_And_Print_Content_File(const char* sender, Find_txt_mail_content Find[], int Command, string file_downloaded_address, int number_folder);
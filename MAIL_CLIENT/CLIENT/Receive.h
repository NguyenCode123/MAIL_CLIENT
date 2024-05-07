#pragma once
#include"Thu_vien.h"

void Process_List_Response(char* response, int result[], int& m, const char* sender);
void Receive_Email(const char* server, int port, const char* username, const char* password);
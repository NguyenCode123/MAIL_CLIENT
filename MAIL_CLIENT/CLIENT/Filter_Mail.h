#pragma once
#include"Thu_vien.h"
struct text {
	string ct;
	string id;
	string sj;
	string cc;
	string to;
};

int posidsender(string sender);
string giveidsender(string& sender);
void read(string content[], int& m, string file);
void savecontent(text& contentsave, string content[], int m);
bool checksubject(string sub, string request);
bool checkid(string idsender, string idrequest);
string classify(text contentsave, string project[], string important[], string work[], string spam[], int np, int ni, int nw, int ns);
string Filer_Folder(string filename);
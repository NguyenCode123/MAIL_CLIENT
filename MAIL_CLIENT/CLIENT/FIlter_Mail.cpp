#include"Filter_Mail.h"

int posidsender(string sender)
{
	size_t pos = sender.find(" : ");
	return pos + 3;
}

string giveidsender(string& sender)
{
	string sendername = sender.substr(posidsender(sender), sender.length());
	return sendername;
}

void read(string content[], int& m, string file)
{
	fstream input;
	input.open(file, ios::in);
	while (!input.eof())
	{
		getline(input, content[m], '\n');
		m++;
	}
}

void savecontent(text& contentsave, string content[], int m)
{
	contentsave.id = content[0];
	contentsave.to = content[1];
	contentsave.cc = content[2];
	contentsave.sj = content[3];

	for (int i = 5; i < m; i++)
	{
		contentsave.ct += (content[i] + '\n');
	}
}

bool checksubject(string sub, string request)
{
	if (sub.length() < request.length())
		return false;
	for (int i = 0; i <= sub.length() - request.length(); i++)
	{
		int dem = 0;
		for (int j = 0; j < request.length(); j++)
		{
			if (sub[j + i] == request[j])
				dem++;
		}
		if (dem == request.length())
			return true;
	}
	return false;
}

bool checkid(string idsender, string idrequest)
{
	if (idsender == idrequest)
		return true;
	return false;
}

string classify(text contentsave, string project[], string important[], string work[], string spam[], int np, int ni, int nw, int ns)
{
	string pj = "Project";
	string ip = "Important";
	string wk = "Work";
	string sp = "Spam";
	string ib = "Inbox";
	for (int i = 0; i < np; i++)
	{
		string s = contentsave.id;
		s = giveidsender(contentsave.id);
		if (checkid(s, project[i]))
			return pj;
	}
	for (int i = 0; i < ni; i++)
	{
		string s = giveidsender(contentsave.sj);
		for (int j = 0; j < ns; j++)
		{
			if (checksubject(s, spam[j]))
				return sp;
		}
		if (checksubject(s, important[i]))
			return ip;
	}
	for (int i = 0; i < nw; i++)
	{
		string s = contentsave.ct;
		for (int j = 0; j < ns; j++)
		{
			if (checksubject(s, spam[j]))
				return sp;
		}
		if (checksubject(s, work[i]))
			return wk;
	}
	return ib;
}

string Filer_Folder(string filename) 
{
	int m = 0;
	text contentsave;
	int np = 2;
	int ni = 2;
	int nw = 2;
	int ns = 3;
	string project[2] = { "ahihi@testing.com","ahuu@testing.com" };
	string important[2] = { "urgent","ASAP" };
	string work[2] = { "report", "meeting" };
	string spam[3] = { "virus","hack","crack" };
	string content[1064];
	read(content, m, filename);
	savecontent(contentsave, content, m);
	string result = classify(contentsave, project, important, work, spam, np, ni, nw, ns);
	return result;
}
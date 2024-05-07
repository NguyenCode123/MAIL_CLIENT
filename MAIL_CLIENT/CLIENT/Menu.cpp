#include"Menu.h"
#include"Receive.h"
#include"Print_Data_To_Console.h"

int Y = 37;
int Z = 18;
int T = 12;
int X = 6;
bool flag = true;
string mail_chat="Send Mail";
string choose_folder;
int flag_turn_menu = -1;
int flag_sign_in_up = -1;

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void setcolor(int backgound_color, int text_color)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	int color_code = backgound_color * 16 + text_color;
	SetConsoleTextAttribute(hStdout, color_code);
}

void gotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void MenuFolder()
{

	gotoXY(46, 3); setcolor(14, 16); cout << "Choose Folder to open";
	gotoXY(45, 3); setcolor(8, 8); cout << char(220);
	gotoXY(67, 3); setcolor(8, 8); cout << char(220);
	gotoXY(68, 4); setcolor(8, 8); cout << char(220);
	gotoXY(44, 4); setcolor(8, 8); cout << char(220);
	gotoXY(44, 5); setcolor(8, 8); cout << char(220);
	gotoXY(44, 6); setcolor(8, 8); cout << char(220); gotoXY(54, 6); setcolor(14, 16); cout << "Inbox";
	gotoXY(44, 7); setcolor(8, 8); cout << char(220);
	gotoXY(44, 8); setcolor(8, 8); cout << char(220);
	gotoXY(44, 9); setcolor(8, 8); cout << char(220); gotoXY(52, 9); setcolor(14, 16); cout << "Important";
	gotoXY(44, 10); setcolor(8, 8); cout << char(220);
	gotoXY(44, 11); setcolor(8, 8); cout << char(220);
	gotoXY(44, 12); setcolor(8, 8); cout << char(220); gotoXY(54, 12); setcolor(14, 16); cout << "Work";
	gotoXY(44, 13); setcolor(8, 8); cout << char(220);
	gotoXY(44, 14); setcolor(8, 8); cout << char(220);
	gotoXY(44, 15); setcolor(8, 8); cout << char(220); gotoXY(53, 15); setcolor(14, 16); cout << "Project";
	gotoXY(44, 16); setcolor(8, 8); cout << char(220);
	gotoXY(44, 17); setcolor(8, 8); cout << char(220);
	gotoXY(44, 18); setcolor(8, 8); cout << char(220); gotoXY(54, 18); setcolor(14, 16); cout << "Spam";
	gotoXY(44, 19); setcolor(8, 8); cout << char(220);
	gotoXY(44, 20); setcolor(8, 8); cout << char(220);

	for (int i = 0; i < 25; i++)
	{
		gotoXY(44 + i, 20); setcolor(8, 8); cout << char(221);
	}
	for (int i = 1; i < 17; i++)
	{
		gotoXY(68, 3 + i); setcolor(8, 8); cout << char(220);
	}
	for (int i = 0; i < 21; i++)
	{
		gotoXY(46 + i, 2); setcolor(8, 8); cout << char(221);
	}
	for (int i = 0; i < 25; i++)
	{
		gotoXY(44 + i, 4); setcolor(8, 8); cout << char(221);
	}

}

void Moveup()
{
	setcolor(14, 16);
	X -= 3;
	if (X < 6)
	{
		choose_folder = "Spam";
		X = 18;
		gotoXY(58, X); cout << char(174);
		gotoXY(59, 6); cout << " ";
	}
	if (X == 6)
	{
		choose_folder = "Inbox";
		gotoXY(59, X); cout << char(174);
		gotoXY(61, 9); cout << " ";
	}
	if (X == 9)
	{
		choose_folder = "Important";
		gotoXY(61, X); cout << char(174);
		gotoXY(58, 12); cout << " ";
	}
	if (X == 12)
	{
		choose_folder = "Work";
		gotoXY(58, X); cout << char(174);
		gotoXY(60, 15); cout << " ";
	}
	if (X == 15)
	{
		choose_folder = "Project";
		gotoXY(60, X); cout << char(174);
		gotoXY(58, 18); cout << " ";
	}
}

void Movedown()
{
	setcolor(14, 16);
	X += 3;
	if (X > 18)
	{
		choose_folder = "Inbox";
		X = 6;
		gotoXY(59, X); cout << char(174);
		gotoXY(58, 18); cout << " ";
	}
	if (X == 18)
	{
		choose_folder = "Spam";
		gotoXY(58, X); cout << char(174);
		gotoXY(60, 15); cout << " ";
	}
	if (X == 9)
	{
		choose_folder = "Important";
		gotoXY(61, X); cout << char(174);
		gotoXY(59, 6); cout << " ";
	}
	if (X == 12)
	{
		choose_folder = "Work";
		gotoXY(58, X); cout << char(174);
		gotoXY(61, 9); cout << " ";
	}
	if (X == 15)
	{
		choose_folder = "Project";
		gotoXY(60, X); cout << char(174);
		gotoXY(58, 12); cout << " ";
	}
}

void hideCursor() {
	CONSOLE_CURSOR_INFO cursorInfo;
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	// Lấy thông tin con trỏ
	GetConsoleCursorInfo(hConsoleOutput, &cursorInfo);

	// Ẩn con trỏ
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsoleOutput, &cursorInfo);
}

void showCursor() {
	CONSOLE_CURSOR_INFO cursorInfo;
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	// Lấy thông tin con trỏ
	GetConsoleCursorInfo(hConsoleOutput, &cursorInfo);

	// Ẩn con trỏ
	cursorInfo.bVisible = true;
	SetConsoleCursorInfo(hConsoleOutput, &cursorInfo);
}

string Folder()
{
	MenuFolder();
	bool validEnter = true;//ki?m tra nh?n phím enter
	while (1)
	{
		int _COMMAND = toupper(_getch());
		if (_COMMAND == 27)
		{
			return NULL;
		}
		else
		{
			if (_COMMAND == 'W')
			{
				Moveup();
			}
			else if (_COMMAND == 'S')
			{
				Movedown();
			}
			else if (choose_folder == "Inbox" && _COMMAND == 13)
			{
				return "Inbox";
			}
			else if (choose_folder == "Important" && _COMMAND == 13)
			{
				return "Important";
			}
			else if (choose_folder == "Work" && _COMMAND == 13)
			{
				return "Work";
			}
			else if (choose_folder == "Project" && _COMMAND == 13)
			{
				return "Project";
			}
			else if (choose_folder == "Spam" && _COMMAND == 13)
			{
				return "Spam";
			}
		}
	}
}

void Moverigth()
{
	//setcolor(14, 16);
	Y += 36;
	if (Y == 73)
	{
		flag = false;
		gotoXY(Y, 23); cout << char(175);
		gotoXY(Y + 14, 23); cout << char(174);
		gotoXY(37, 23); cout << " "; gotoXY(51, 23); cout << " ";
	}
	if (Y > 73)
	{
		flag = true;
		Y = 37;
		gotoXY(Y, 23); cout << char(175);
		gotoXY(Y + 14, 23); cout << char(174);
		gotoXY(73, 23); cout << " "; gotoXY(87, 23); cout << " ";

	}


}

void Moveleft()
{
	//setcolor(14, 16);
	Y -= 36;
	if (Y < 37)
	{
		flag = false;
		Y = 73;
		gotoXY(Y, 23); cout << char(175);
		gotoXY(Y + 14, 23); cout << char(174);
		gotoXY(37, 23); cout << " "; gotoXY(51, 23); cout << " ";

	}
	if (Y == 37)
	{
		flag = true;
		gotoXY(Y, 23); cout << char(175);
		gotoXY(Y + 14, 23); cout << char(174);
		gotoXY(73, 23); cout << " "; gotoXY(87, 23); cout << " ";
	}

}

void MenuSignin()
{
	gotoXY(60, 5); cout << "SIGN IN";
	setcolor(8, 8);
	for (int i = 0; i < 28; i++)
	{
		gotoXY(59 - i, 5); cout << char(220);
	}
	for (int i = 0; i < 28; i++)
	{
		gotoXY(67 + i, 5); cout << char(220);
	}
	for (int i = 0; i < 22; i++)
	{
		gotoXY(32, 6 + i); cout << char(220);
	}
	for (int i = 0; i < 22; i++)
	{
		gotoXY(94, 6 + i); cout << char(220);
	}
	for (int i = 0; i < 63; i++)
	{
		gotoXY(32 + i, 27); cout << char(220);
	}
}

void MenuSignup()
{
	gotoXY(60, 5); cout << "SIGN UP";
	setcolor(8, 8);
	for (int i = 0; i < 28; i++)
	{
		gotoXY(59 - i, 5); cout << char(220);
	}
	for (int i = 0; i < 28; i++)
	{
		gotoXY(67 + i, 5); cout << char(220);
	}
	for (int i = 0; i < 22; i++)
	{
		gotoXY(32, 6 + i); cout << char(220);
	}
	for (int i = 0; i < 22; i++)
	{
		gotoXY(94, 6 + i); cout << char(220);
	}
	for (int i = 0; i < 63; i++)
	{
		gotoXY(32 + i, 27); cout << char(220);
	}
}

bool selectsignin(char username[], char password[], char sender[], char MailSever[], int& portSMTP, int& portPop3, int& AutoLoad, char address_downloaded_file[])
{
	setcolor(8,8);
	gotoXY(38, 22); cout << char(220); gotoXY(50, 22); cout << char(220);
	gotoXY(38, 23); cout << char(220); gotoXY(50, 23); cout << char(220);
	gotoXY(38, 24); cout << char(220); gotoXY(50, 24); cout << char(220);
	for (int i = 0; i < 12; i++)
	{
		gotoXY(38 + i, 22); cout << char(220);
		gotoXY(38 + i, 24); cout << char(220);
	}
	gotoXY(74, 22); cout << char(220); gotoXY(86, 22); cout << char(220);
	gotoXY(74, 23); cout << char(220); gotoXY(86, 23); cout << char(220);
	gotoXY(74, 24); cout << char(220); gotoXY(86, 24); cout << char(220);
	for (int i = 0; i < 11; i++)
	{
		gotoXY(75 + i, 22); cout << char(220);
		gotoXY(75 + i, 24); cout << char(220);
	}
	setcolor(14, 16); gotoXY(40, 23); cout << "Try Again";
	gotoXY(77, 23); cout << "Sign Up";
	bool validEnter = true;//ki?m tra nh?n phím enters
	//setcolor(0, 12);
	while (1)
	{
		int key = toupper(_getch());
		if (key == 27)
		{
			return false;
		}
		else
		{
			if (key == 'A')
			{
				Moveleft();
			}
			else if (key == 'D')
			{

				Moverigth();
			}
			else if (flag ==false && key == 13)
			{
				system("cls");
				setcolor(15, 0);
				MenuSignup();
				Sign_Up(username, password, sender, MailSever, portSMTP, portPop3, AutoLoad, address_downloaded_file);
				break;
				return true;
			}
			else if (flag == true && key == 13)
			{
				return false;
			}
		}
	}
}

void exitmenu()
{
	setcolor(8, 8);
	for (int i = 0; i < 20; i++)
	{
		gotoXY(20 + i, 20); cout << char(220);
		gotoXY(20 + i, 24); cout << char(220);
	}
	for (int i = 0; i < 5; i++)
	{
		gotoXY(19, 20 + i); cout << char(220);
		gotoXY(40, 20 + i); cout << char(220);
	}
	for (int i = 0; i < 20; i++)
	{
		gotoXY(80 + i, 20); cout << char(220);
		gotoXY(80 + i, 24); cout << char(220);
	}
	for (int i = 0; i < 5; i++)
	{
		gotoXY(79, 20 + i); cout << char(220);
		gotoXY(100, 20 + i); cout << char(220);
	}
	setcolor(14, 16);
	gotoXY(88, 22); cout << "Menu";
	gotoXY(25, 22); cout << "Turn Back";
}

void mailchat()
{
	setcolor(14, 16);
	gotoXY(55, 5); cout << "Mail Chat";
	gotoXY(55, 12); cout << "Send Mail";
	gotoXY(54, 18); cout << "Receive Mail";
	gotoXY(58, 24); cout << "Exit";
	setcolor(8, 8);
	for (int j = 0; j < 13; j += 6)
	{
		for (int i = 0; i < 15; i++)
		{
			gotoXY(53 + i, 11 + j); cout << char(220);
			gotoXY(53 + i, 13 + j); cout << char(220);
		}
	}
	gotoXY(53, 12); cout << char(220); gotoXY(67, 12); cout << char(220);
	gotoXY(53, 18); cout << char(220); gotoXY(67, 18); cout << char(220);
	gotoXY(53, 24); cout << char(220); gotoXY(67, 24); cout << char(220);
	for (int i = 0; i < 15; i++)
	{
		gotoXY(54 - i, 5); cout << char(220);
		gotoXY(64 + i, 5); cout << char(220);
	}
	for (int i = 0; i < 23; i++)
	{
		gotoXY(40, 6 + i); cout << char(220);
		gotoXY(78, 6 + i); cout << char(220);
	}
	for (int i = 0; i < 38; i++)
	{
		gotoXY(40 + i, 28); cout << char(220);
	}

}

void movemchatup()
{
	T -= 6;
	if (T < 12)
	{
		mail_chat = "Exit";
		T = 24;
		gotoXY(52, T); cout << char(175); gotoXY(68, T); cout << char(174);
		gotoXY(52, 12); cout << " "; gotoXY(68, 12); cout << " ";
	}
	else if (T == 18)
	{
		mail_chat = "Receive Mail";
		gotoXY(52, T); cout << char(175); gotoXY(68, T); cout << char(174);
		gotoXY(52, 24); cout << " "; gotoXY(68, 24); cout << " ";
	}
	else if (T == 12)
	{
		mail_chat = "Send Mail";
		gotoXY(52, T); cout << char(175); gotoXY(68, T); cout << char(174);
		gotoXY(52, 18); cout << " "; gotoXY(68, 18); cout << " ";
	}
}

void movemchatdown()
{
	T += 6;
	if (T > 24)
	{
		mail_chat = "Send Mail";
		T = 12;
		gotoXY(52, T); cout << char(175); gotoXY(68, T); cout << char(174);
		gotoXY(52, 24); cout << " "; gotoXY(68, 24); cout << " ";
	}
	else if (T == 18)
	{
		mail_chat = "Receive Mail";
		gotoXY(52, T); cout << char(175); gotoXY(68, T); cout << char(174);
		gotoXY(52, 12); cout << " "; gotoXY(68, 12); cout << " ";
	}
	else if (T == 24)
	{
		mail_chat = "Exit";
		gotoXY(52, T); cout << char(175); gotoXY(68, T); cout << char(174);
		gotoXY(52, 18); cout << " "; gotoXY(68, 18); cout << " ";
	}
}

string seclectmchat()
{
	mailchat();
	bool validEnter = true;//ki?m tra nh?n phím enters
	setcolor(14, 16);
	while (1)
	{
		int key = toupper(_getch());
		if (key == 27)
		{
			return NULL;
		}
		else
		{
			if (key == 'W')
			{

				movemchatup();
			}
			else if (key == 'S')
			{
				movemchatdown();
			}
			else if (mail_chat =="Send Mail" && key == 13)
			{
				return "Send Mail";
			}
			else if (mail_chat == "Receive Mail" && key == 13)
			{
				return "Receive Mail";
			}
			else if (mail_chat == "Exit" && key == 13)
			{
				return "Exit";
			}
		}
	}
}

void signupmenu()
{
	//M
	setcolor(4, 4);
	gotoXY(35, 3); cout << char(221); gotoXY(36, 3); cout << char(220); gotoXY(38, 3); cout << char(220);
	gotoXY(35, 4); cout << char(221); gotoXY(37, 4); cout << char(220);
	gotoXY(35, 5); cout << char(221);
	gotoXY(35, 6); cout << char(221);
	gotoXY(39, 3); cout << char(221);
	gotoXY(39, 4); cout << char(220);
	gotoXY(39, 5); cout << char(220);
	gotoXY(39, 6); cout << char(220);
	//A
	gotoXY(45, 3); cout << char(220);
	gotoXY(44, 4); cout << char(220); gotoXY(46, 4); cout << char(220); gotoXY(45, 4); cout << char(220);
	gotoXY(43, 4); cout << char(220); gotoXY(47, 4); cout << char(220);
	gotoXY(42, 5); cout << char(220); gotoXY(48, 5); cout << char(220);
	gotoXY(42, 6); cout << char(220); gotoXY(48, 6); cout << char(220);
	//I
	gotoXY(50, 3); cout << char(220);
	gotoXY(50, 4); cout << char(220);
	gotoXY(50, 5); cout << char(220);
	gotoXY(50, 6); cout << char(220);
	//L
	gotoXY(53, 3); cout << char(220);
	gotoXY(53, 4); cout << char(220);
	gotoXY(53, 5); cout << char(220);
	gotoXY(53, 6); cout << char(220); gotoXY(54, 6); cout << char(221); gotoXY(55, 6); cout << char(220);
	//C
	gotoXY(62, 3); cout << char(220); gotoXY(63, 3); cout << char(220); gotoXY(64, 3); cout << char(220); gotoXY(65, 3); cout << char(220);
	gotoXY(62, 4); cout << char(220);
	gotoXY(62, 5); cout << char(220);
	gotoXY(62, 6); cout << char(220); gotoXY(63, 6); cout << char(220); gotoXY(64, 6); cout << char(220); gotoXY(65, 6); cout << char(220);
	//H
	gotoXY(68, 3); cout << char(220); gotoXY(72, 3); cout << char(220);
	gotoXY(68, 4); cout << char(220); gotoXY(72, 4); cout << char(220);
	gotoXY(68, 5); cout << char(220); gotoXY(72, 5); cout << char(220);
	gotoXY(68, 6); cout << char(220); gotoXY(72, 6); cout << char(220);
	gotoXY(69, 5); cout << char(220); gotoXY(70, 5); cout << char(220); gotoXY(71, 5); cout << char(220);
	//A
	gotoXY(78, 3); cout << char(220);
	gotoXY(77, 4); cout << char(220); gotoXY(79, 4); cout << char(220); gotoXY(78, 4); cout << char(220);
	gotoXY(76, 4); cout << char(220); gotoXY(80, 4); cout << char(220);
	gotoXY(75, 5); cout << char(220); gotoXY(81, 5); cout << char(220);
	gotoXY(75, 6); cout << char(220); gotoXY(81, 6); cout << char(220);
	//T
	gotoXY(85, 3); cout << char(220); gotoXY(84, 3); cout << char(220); gotoXY(86, 3); cout << char(220);
	gotoXY(85, 4); cout << char(220);
	gotoXY(85, 5); cout << char(220);
	gotoXY(85, 6); cout << char(220);
	setcolor(4, 4);
	gotoXY(20, 22); cout << char(220); gotoXY(33, 22); cout << char(220);
	gotoXY(20, 23); cout << char(220); gotoXY(33, 23); cout << char(220);
	gotoXY(20, 24); cout << char(220); gotoXY(33, 24); cout << char(220);
	for (int i = 0; i < 12; i++)
	{
		gotoXY(21 + i, 22); cout << char(220);
		gotoXY(21 + i, 24); cout << char(220);
	}
	gotoXY(90, 22); cout << char(220); gotoXY(102, 22); cout << char(220);
	gotoXY(90, 23); cout << char(220); gotoXY(102, 23); cout << char(220);
	gotoXY(90, 24); cout << char(220); gotoXY(102, 24); cout << char(220);
	for (int i = 0; i < 11; i++)
	{
		gotoXY(91 + i, 22); cout << char(220);
		gotoXY(91 + i, 24); cout << char(220);
	}
	setcolor(15, 0); gotoXY(23, 23); cout << "Sign In";
	gotoXY(93, 23); cout << "Sign Up";
}

void movesigupr()
{
	Z += 70;
	if (Z == 89)
	{
		flag_sign_in_up = 1;
		gotoXY(Z, 23); cout << char(175);
		gotoXY(Z + 15, 23); cout << char(174);
		gotoXY(19, 23); cout << " "; gotoXY(34, 23); cout << " ";
	}
	if (Z > 89)
	{
		flag_sign_in_up = -1;
		Z = 19;
		gotoXY(Z, 23); cout << char(175);
		gotoXY(Z + 15, 23); cout << char(174);
		gotoXY(89, 23); cout << " "; gotoXY(104, 23); cout << " ";

	}
}

void movesigupl()
{
	Z -= 70;
	if (Z == 19)
	{
		flag_sign_in_up = -1;
		gotoXY(Z, 23); cout << char(175);
		gotoXY(Z + 15, 23); cout << char(174);
		gotoXY(89, 23); cout << " "; gotoXY(104, 23); cout << " ";
	}
	if (Z < 19)
	{
		flag_sign_in_up = 1;
		Z = 89;
		gotoXY(Z, 23); cout << char(175);
		gotoXY(Z + 15, 23); cout << char(174);
		gotoXY(19, 23); cout << " "; gotoXY(34, 23); cout << " ";

	}
}

string selectsigup()
{
	signupmenu();
	bool validEnter = true;//ki?m tra nh?n phím enters
	//setcolor(0, 12);
	while (1)
	{
		int key = toupper(_getch());
		if (key == 27)
		{
			return NULL;
		}
		else
		{
			if (key == 'A')
			{

				movesigupl();
			}
			else if (key == 'D')
			{
				movesigupr();
			}
			else if (flag_sign_in_up==-1 && key == 13)
			{
				return "Sign In";
			}
			else if (flag_sign_in_up == 1 && key == 13)
			{
				return "Sign Up";
			}
		}
	}
}

void Write_Config_TO_xml(char username[], char password[], char sender[], char MailServer[], int portSMTP, int portPop3, int AutoLoad, char address_downloaded_file[])
{
	pugi::xml_document doc;

	// Tạo nút gốc
	pugi::xml_node root = doc.append_child("Configuration");

	// Tạo và thêm các nút con
	root.append_child("Username").text().set(username);
	root.append_child("Sender").text().set(sender);
	root.append_child("Password").text().set(password);
	root.append_child("MailServer").text().set(MailServer);
	root.append_child("SMTP").text().set(portSMTP);
	root.append_child("POP3").text().set(portPop3);
	root.append_child("Autoload").text().set(AutoLoad);
	root.append_child("Address_downloaded_file").text().set(address_downloaded_file);

	// Lưu tài liệu XML vào file
	char file_name[100] = "";
	strcat(file_name, sender);
	strcat(file_name, " ");
	strcat(file_name, password);
	strcat(file_name, ".xml");
	doc.save_file(file_name);
}

void Sign_Up (char username[], char password[], char sender[], char MailSever[], int& portSMTP, int& portPop3, int& AutoLoad, char address_downloaded_file[])
{
	MenuSignup();
	setcolor(15, 0);
	showCursor();
	gotoXY(40, 10); cout << "Username: ";
	gotoXY(40, 11); cout << "Password: ";
	gotoXY(40, 12); cout << "Your Mail Address: ";
	gotoXY(40, 13); cout << "Mail Server:  ";
	gotoXY(40, 14); cout << "Port SMTP: ";
	gotoXY(40, 15); cout << "Port POP3: ";
	gotoXY(40, 16); cout << "AutoLoad(s): ";
	gotoXY(40, 17); cout << "Address to save file downloaded: ";
	gotoXY(50, 10); cin.getline(username, 50);
	gotoXY(50, 11); cin.getline(password, 50);
	gotoXY(59, 12); cin.getline(sender, 50);
	gotoXY(53, 13); cin.getline(MailSever, 50);
	gotoXY(51, 14); cin >> portSMTP;
	gotoXY(51, 15); cin >> portPop3;
	gotoXY(53, 16); cin >> AutoLoad;

	cin.ignore();
	gotoXY(74, 17); cin.getline(address_downloaded_file, 100);
	hideCursor();
	Write_Config_TO_xml(username, password, sender, MailSever, portSMTP, portPop3, AutoLoad, address_downloaded_file);
	CreateDirectoryA(sender, NULL);
	ofstream Open;
	char temp[100];
	Open.open(sender);

	strcpy(temp, sender);
	strcat(temp, "\\Inbox");
	CreateDirectoryA(temp, NULL);

	strcpy(temp, sender);
	strcat(temp, "\\Project");
	CreateDirectoryA(temp, NULL);

	strcpy(temp, sender);
	strcat(temp, "\\Important");
	CreateDirectoryA(temp, NULL);

	strcpy(temp, sender);
	strcat(temp, "\\Work");
	CreateDirectoryA(temp, NULL);

	strcpy(temp, sender);
	strcat(temp, "\\Spam");
	CreateDirectoryA(temp, NULL);
	Open.close();
	setcolor(11, 1);
	gotoXY(50, 20); cout << "Dang ki tai khoan thanh cong";
	gotoXY(55, 22); cout << "Nhan Enter de den Menu";
	_getch();
	setcolor(15,0);
	system("cls");
}

void Sign_In(char username[], char password[], char sender[], char MailSever[], int& portSMTP, int& portPop3, int& AutoLoad, char address_downloaded_file[])
{
	while (true)
	{
		setcolor(15, 0);
		system("cls");
		MenuSignin();
		setcolor(15, 0);
		showCursor();
		gotoXY(40, 12); cout << "Your Mail Address: ";
		gotoXY(40, 14); cout << "Password: ";
		gotoXY(59, 12); cin.getline(sender, 50);
		gotoXY(50, 14); cin.getline(password, 50);
		hideCursor();
		char file_name[100] = "";
		strcat(file_name, sender);
		strcat(file_name, " ");
		strcat(file_name, password);
		strcat(file_name, ".xml");
		pugi::xml_document doc;

		// Load tài liệu từ file XML
		pugi::xml_parse_result result = doc.load_file(file_name);

		if (!result) {
			gotoXY(53, 18);
			setcolor(11, 1);
			cout << "Tai khoan chua dang ki";
			if (selectsignin(username, password, sender, MailSever, portSMTP, portPop3, AutoLoad, address_downloaded_file))
				break;
			continue;
		}
		pugi::xml_node root = doc.child("Configuration");

		// Kiểm tra xem phần tử gốc có tồn tại hay không
		int count = 1;
		if (root) 
		{
			// Truy cập các phần tử con
			for (pugi::xml_node element = root.first_child(); element; element = element.next_sibling())
			{
				// Lấy tên và giá trị của mỗi phần tử con
				if (count == 1)
				{
					strcpy(username, element.child_value());
				}
				if (count == 2)
				{
					strcpy(sender, element.child_value());
				}
				if (count == 3)
				{
					strcpy(password, element.child_value());
				}
				if (count == 4)
				{
					strcpy(MailSever, element.child_value());
				}
				if (count == 5)
				{
					portSMTP = atoi(element.child_value());
				}
				if (count == 6)
				{
					portPop3 = atoi(element.child_value());
				}
				if (count == 7)
				{
					AutoLoad = atoi(element.child_value());
				}
				if (count == 8)
				{
					strcpy(address_downloaded_file, element.child_value());
				}
				count++;
			}
			setcolor(15, 0);
			system("cls");
			break;
		}
	}
}

void Menu(char username[], char password[], char sender[], char MailSever[], int& portSMTP, int& portPop3, int& AutoLoad, char address_downloaded_file[], char recipient[], char subject[], char body[], char CC[], char BCC[], link_file L[], int& count_file)
{
	hideCursor();
	int Command;
	string temp_1 = selectsigup();
	if (temp_1 == "Sign In")
	{
		setcolor(15, 0);
		system("cls");
		Sign_In(username, password, sender, MailSever, portSMTP, portPop3, AutoLoad, address_downloaded_file);
	}
	else if (temp_1 == "Sign Up")
	{
		setcolor(15, 0);
		system("cls");
		Sign_Up(username, password, sender, MailSever, portSMTP, portPop3, AutoLoad, address_downloaded_file);
	}
	thread t1(thread_Auto_Download_Mail, MailSever, portPop3, sender, password, AutoLoad);
	t1.detach();
	while (true)
	{
		string temp_2 = seclectmchat();
		if (temp_2 == "Send Mail")
		{
			count_file = 0;
			setcolor(15, 0);
			system("cls");
			Data_Entry(recipient, subject, body, CC, BCC, L, count_file);
			Send_Email(MailSever, portSMTP, username, sender, recipient, subject, CC, BCC, body, L, count_file);
			setcolor(11, 0);
			cout << endl << "Da gui mail thanh cong";
			Command = toupper(_getch());
			while (Command != 13)
			{
				Command = toupper(_getch());
			}
			setcolor(15, 0);
			system("cls");
		}
		else if (temp_2 == "Receive Mail")
		{
			setcolor(15, 0);
			system("cls");
			Find_txt_mail_content Find[200];
			setcolor(15, 0);
			system("cls");
			temp_2 = Folder();
			if (temp_2 == "Inbox")
			{
				setcolor(15, 0);
				system("cls");
				Command_To_Choose_File(sender, Find, 1, address_downloaded_file);
				setcolor(11, 0);
				cout << endl << "Nhan Enter de quay lai MENU";
				Command = toupper(_getch());
				while (Command != 13)
				{
					Command = toupper(_getch());
				}
				setcolor(15, 0);
				system("cls");
			}
			else if (temp_2 == "Important")
			{
				setcolor(15, 0);
				system("cls");
				Command_To_Choose_File(sender, Find, 2, address_downloaded_file);
				setcolor(11, 0);
				cout << endl << "Nhan Enter de quay lai MENU";
				Command = toupper(_getch());
				while (Command != 13)
				{
					Command = toupper(_getch());
				}
				setcolor(15, 0);
				system("cls");
			}
			else if (temp_2 == "Project")
			{
				setcolor(15, 0);
				system("cls");
				Command_To_Choose_File(sender, Find, 3, address_downloaded_file);
				setcolor(11, 0);
				cout << endl << "Nhan Enter de quay lai MENU";
				Command = toupper(_getch());
				while (Command != 13)
				{
					Command = toupper(_getch());
				}
				setcolor(15, 0);
				system("cls");
			}
			else if (temp_2 == "Work")
			{
				setcolor(15, 0);
				system("cls");
				Command_To_Choose_File(sender, Find, 4, address_downloaded_file);
				setcolor(11, 0);
				cout << endl << "Nhan Enter de quay lai MENU";
				Command = toupper(_getch());
				while (Command != 13)
				{
					Command = toupper(_getch());
				}
				setcolor(15, 0);
				system("cls");
			}
			else if (temp_2 == "Spam")
			{
				setcolor(15, 0);
				system("cls");
				Command_To_Choose_File(sender, Find, 5, address_downloaded_file);
				setcolor(11, 0);
				cout << endl << "Nhan Enter de quay lai MENU";
				Command = toupper(_getch());
				while (Command != 13)
				{
					Command = toupper(_getch());
				}
				setcolor(15, 0);
				system("cls");
			}
		}
		else if (temp_2 == "Exit")
		{
			setcolor(15, 0);
			system("cls");
			break;
		}
	}
}
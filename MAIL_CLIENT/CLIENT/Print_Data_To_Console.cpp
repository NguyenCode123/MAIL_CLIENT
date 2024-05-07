#include"Print_Data_To_Console.h"
#include"Menu.h"

string base64_decode(const string& input) {
	// Sử dụng iterator để decode dữ liệu
	auto base64Decode = [](char c) -> unsigned char {
		const char base64Chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
		auto result = find(begin(base64Chars), end(base64Chars), c);
		return static_cast<unsigned char>(distance(begin(base64Chars), result));
	};

	string decodedData;
	auto inputBegin = input.begin();
	auto inputEnd = input.end();

	while (inputBegin != inputEnd) {
		// Lấy 4 ký tự Base64
		char char1 = *(inputBegin++);
		char char2 = (inputBegin != inputEnd) ? *(inputBegin++) : 0;
		char char3 = (inputBegin != inputEnd) ? *(inputBegin++) : 0;
		char char4 = (inputBegin != inputEnd) ? *(inputBegin++) : 0;

		// Chia 4 ký tự thành 3 byte và decode
		unsigned char byte1 = (base64Decode(char1) << 2) | (base64Decode(char2) >> 4);
		unsigned char byte2 = ((base64Decode(char2) & 0x0F) << 4) | (base64Decode(char3) >> 2);
		unsigned char byte3 = ((base64Decode(char3) & 0x03) << 6) | base64Decode(char4);

		// Thêm 3 byte đã giải mã vào dữ liệu kết quả
		decodedData += byte1;

		if (char3 != '=' && char3 != 0)
			decodedData += byte2;

		if (char4 != '=' && char4 != 0)
			decodedData += byte3;
	}

	return decodedData;
}

void write_binary_file(const string& filename, const string& data) {
	ofstream file(filename, ios::binary);
	if (file) {
		file.write(data.c_str(), data.size());
	}
}

void Return_Unsername_Folder_Address(const char* sender, char file_name[], int Command)
{
	string folder;
	if (Command == 1)
	{
		folder = "Inbox";
	}
	else if (Command == 2)
	{
		folder = "Important";
	}
	else if (Command == 3)
	{
		folder = "Project";
	}
	else if (Command == 4)
	{
		folder = "Work";
	}
	else if (Command == 5)
	{
		folder = "Spam";
	}
	strcat(file_name, sender);
	strcat(file_name, "\\");
	strcat(file_name, folder.c_str());
	strcat(file_name, "\\");
}

void Print_Name_The_Sender_And_Subject(const char* sender, Find_txt_mail_content Find[], int& count, int number_folder)
{
	char file_name[100] = ""; char temp[100]="";
	Return_Unsername_Folder_Address(sender, file_name, number_folder);
	strcat(temp, sender);
	strcat(temp, "_received_username_mail.txt");
	strcat(file_name, temp);
	ifstream File_input;
	File_input.open(file_name);
	if (!File_input.is_open())
	{
		cout << "Khong co file nhan nao";
		return;
	}
	while (!File_input.eof())
	{
		File_input.getline(Find[count].dia_chi, 200);
		File_input.getline(Find[count].subject, 200);
		File_input.getline(Find[count].number, 200);
		count++;
	}
	File_input.close();
	string s;
	for (int i = 0; i < count -1; i++)
	{
		string dia_chi_txt(Find[i].dia_chi);
		size_t start_pos = dia_chi_txt.find_first_of('<');
		size_t end_pos = dia_chi_txt.find_first_of('>', start_pos + 1);
		// Tạo chuỗi con dia chi mới
		string temp = dia_chi_txt.substr(start_pos + 1, end_pos - start_pos - 1);

		char file_name_1[100] = "";
		Return_Unsername_Folder_Address(sender, file_name_1, number_folder);
		strcat(file_name_1, Find[i].number);
		strcat(file_name_1, ".");
		strcat(file_name_1, temp.c_str());
		strcat(file_name_1, ".txt");
		File_input.open(file_name_1);
		while (getline(File_input, s));
		cout << i + 1 << ". " << Find[i].dia_chi;
		if (s == "YES")
		{
			cout << "   ";
			setcolor(11, 0);
		    cout << "DA DOC" << endl;
		}
		else if (s == "NO")
		{
			cout << "   ";
			setcolor(12, 0);
			cout << "CHUA DOC" << endl;
		}
		setcolor(15, 0);
		File_input.close();
		cout << "   " << Find[i].subject << endl;
	}
}

void Draw_For_Receive_mail()
{
	setcolor(15, 0);
	for (int i = 2; i < 12; i = i + 3)
	{
		gotoXY(0, i);
		for (int i = 0; i < 120; i++)
			printf("%c", 223);
	}
}

void Read_And_Print_Content_File(const char* sender, Find_txt_mail_content Find[], int Command, string file_downloaded_address, int number_folder)
{
	system("cls");
	Draw_For_Receive_mail();
	char file_name[100] = "";
	ifstream File_input;
	ofstream File_output;
	Return_Unsername_Folder_Address(sender, file_name, number_folder);
	strcat(file_name, Find[Command - 1].number);
	strcat(file_name, ".");

	string dia_chi_txt(Find[Command - 1].dia_chi);
	size_t start_pos = dia_chi_txt.find_first_of('<');
	size_t end_pos = dia_chi_txt.find_first_of('>', start_pos + 1);
	// Tạo chuỗi con dia chi mới
	string temp = dia_chi_txt.substr(start_pos + 1, end_pos - start_pos - 1);

	strcat(file_name, temp.c_str());
	strcat(file_name, ".txt");
	File_input.open(file_name);
	string s;
	bool flag = false;
	int count = 0;
	while (getline(File_input, s))
	{
		if (s == "NO")
			break;
		if (s == "Content-Type: text/plain; charset=UTF-8;format=flowed" || s == "Content-Transfer-Encoding:7bit")
			continue;
		if (s == "Content-Transfer-Encoding: base64")
		{
			string file_encode = "";
			getline(File_input, s);
			string file_name;
			int bien_chay = 0, bien_dau, bien_cuoi;
			for (bien_chay; s[bien_chay] != '"'; bien_chay++);
			bien_chay += 1; bien_dau = bien_chay;
			for (bien_chay; s[bien_chay] != '"'; bien_chay++);
			bien_cuoi = bien_chay;
			file_name = s.substr(bien_dau, bien_cuoi - bien_dau); //Lay duoc file name
			getline(File_input, s);
			while (getline(File_input, s))
			{
				if (s == "")
					break;
				file_encode = file_encode + s;
			}

			string decodedFileName = file_downloaded_address + "/";
			decodedFileName = decodedFileName + file_name;
			string decodedData = base64_decode(file_encode);
			write_binary_file(decodedFileName, decodedData);
			setcolor(11, 0);
			cout << "Da tai file: ";
			setcolor(15, 0);
			cout << file_name << endl;
		}
		else
		{
			if (count <= 12)
			{
				gotoXY(0, count);
				count += 3;
			}
			cout << s << endl;
		}
	}

	while (!File_input.eof())
	{
		getline(File_input, s);
	}
	if (s == "NO")
	{
		File_output.open(file_name, ios::app);
		File_output << endl << "YES";
		File_output.close();
	}
	File_input.close();
}

void Command_To_Choose_File(const char* sender,Find_txt_mail_content Find[], int number_folder, char address_downloaded_file[])
{
	int Command;
	int count=0;
	Print_Name_The_Sender_And_Subject(sender, Find, count, number_folder);
	if (count == 0)
		return;
	while (true)
	{
		showCursor();
		cout << "Chon so thu tu file ban muon doc (Nhan 0 de thoat): "; cin >> Command;
		hideCursor();
		if (Command >= count || Command < 0)
		{
			cout << "Ban nhap so khong hop le: " << endl;

			continue;
		}
		else if (Command == 0)
		{
			return;
		}
		else
		{
			Read_And_Print_Content_File(sender, Find, Command, address_downloaded_file, number_folder);
			break;
		}
	}
}
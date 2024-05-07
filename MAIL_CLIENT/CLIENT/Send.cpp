#include"Send.h"
#include"Menu.h"

int calculate_parity(unsigned char value) {
    int parity = 0;
    while (value) {
        parity ^= value & 1;
        value >>= 1;
    }
    return parity;
}

//Mã hóa 7bit
string encode7bit(const string& input) {
    string encodedData;

    // Mã hóa 7 bit thành 8 bit (với bit kiểm tra)
    for (char c : input) {
        char encodedChar = c & 0x7F;  // Giữ 7 bit thấp
        encodedChar |= calculate_parity(encodedChar) << 7;  // Thêm bit kiểm tra
        encodedData += encodedChar;
    }

    return encodedData;
}

//Mã hóa Base 64
string base64_encode(const string& input) {
    // Sử dụng iterator để encode dữ liệu
    auto base64Encode = [](unsigned char c) -> char {
        const char base64Chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        return base64Chars[c & 0x3F];
    };

    string encodedData;
    auto inputBegin = input.begin();
    auto inputEnd = input.end();

    while (inputBegin != inputEnd) {
        // Lấy 3 byte từ dữ liệu đầu vào
        unsigned char byte1 = *(inputBegin++);
        unsigned char byte2 = (inputBegin != inputEnd) ? *(inputBegin++) : 0;
        unsigned char byte3 = (inputBegin != inputEnd) ? *(inputBegin++) : 0;

        // Chia 3 byte thành 4 nhóm 6 bit và mã hóa thành các ký tự Base64
        encodedData += base64Encode(byte1 >> 2);
        encodedData += base64Encode(((byte1 & 0x03) << 4) | (byte2 >> 4));
        encodedData += base64Encode(((byte2 & 0x0F) << 2) | (byte3 >> 6));
        encodedData += base64Encode(byte3 & 0x3F);
    }

    // Thêm ký tự padding nếu cần thiết
    size_t padding = input.length() % 3;
    if (padding > 0) {
        encodedData.replace(encodedData.length() - padding, padding, padding, '=');
    }

    return encodedData;
}

string read_binary_file(const string& filename) {
    ifstream file(filename, ios::binary);
    if (file) {
        ostringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }
    return "";
}

void Draw_For_Send_mail()
{
    setcolor(15, 0);
    for (int i = 2; i < 14; i = i + 3)
    {
        gotoXY(0, i);
        for (int i = 0; i < 120; i++)
            printf("%c", 223);
    }
}

// Function to send email using SMTP
void Data_Entry(char recipient[], char subject[], char body[], char CC[], char BCC[], link_file L[], int& count_file)
{
    Draw_For_Send_mail();
    setcolor(15, 0);
    showCursor();
    gotoXY(0, 0); cout << "To: "; 
    gotoXY(0, 3); cout << "CC: "; 
    gotoXY(0, 6); cout << "BCC: "; 
    gotoXY(0, 9); cout << "Subject: ";
    setcolor(11, 0);
    gotoXY(0, 12); cout << "(Nhap \"End.\" neu ban muon ngung nhap) ";
    setcolor(15, 0);
    gotoXY(4, 0); cin.getline(recipient, 200);
    gotoXY(4, 3); cin.getline(CC, 200);
    gotoXY(5, 6); cin.getline(BCC, 200);
    gotoXY(8, 9); cin.getline(subject, 100);
    gotoXY(0, 13);
    cout << endl;
    char body_temp[1000];
    while (true)
    {
        cin.getline(body_temp, 1000);
        if (strcmp(body_temp,"End.")==0)
            break;
        strcat(body, body_temp);
        strcat(body, "\n");
    }
    ifstream Input_check;
    string check_1, check_2;
    char enter[100];
    cout << endl;
    while (true)
    {
        setcolor(11, 0);
        cout << "Choose link file " << count_file + 1  << " you want to send (Press '<No>' if you don't want): "; 
        setcolor(15, 0);
        cin.getline(enter, 100);
        if (strcmp(enter, "<No>") == 0)
        {
            break;
        }
        Input_check.open(enter);
        if (!Input_check.is_open())
        {
            cout << "Khong tim thay file";
            Input_check.close();
            continue;
        }
        Input_check.close();
        check_1 = read_binary_file(enter);
        check_2 = base64_encode(check_1);
        if (check_2.length() > 3000000)
        {
            setcolor(12, 0);
            cout << "The capacity of file " << enter << " exceeds 3MB so it is unacceptable" << endl;
            continue;
        }
        strcpy(L[count_file].link, enter);
        ++count_file;
    }
    hideCursor();
}

void Send_Email(const char* server, int port, const char* username, const char* sender, char* recipient, const char* subject, char* CC, char* BCC, char* body, link_file L[], int count_file)
{
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "Failed to initialize Winsock." << std::endl;
        return;
    }

    // Create a socket for SMTP
    SOCKET smtpSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (smtpSocket == INVALID_SOCKET) {
        cout << "Failed to create socket." << std::endl;
        WSACleanup();
        return;
    }

    // Connect to the SMTP server
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(server);
    
    if (connect(smtpSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect to SMTP server." << std::endl;
        closesocket(smtpSocket);
        WSACleanup();
        return;
    }

    char buffer[MAX_BUFFER_SIZE];
    recv(smtpSocket, buffer, sizeof(buffer), 0);

    //Gửi lệnh EHLO
    const char* ehloCommand = "EHLO\r\n";
    send(smtpSocket, ehloCommand, strlen(ehloCommand), 0);

    // Gửi lệnh MAIL FROM
    char mailFromCommand[MAX_BUFFER_SIZE];
    sprintf(mailFromCommand, "MAIL FROM:<%s>\r\n", sender);
    send(smtpSocket, mailFromCommand, strlen(mailFromCommand), 0);
    recv(smtpSocket, buffer, sizeof(buffer), 0);

    // Gửi lệnh RCPT TO
    stringstream ss1(recipient);
    char Mail_address[30];
    while (ss1 >> Mail_address)
    {
        char rcptToCommand[MAX_BUFFER_SIZE];
        sprintf(rcptToCommand, "RCPT TO:<%s>\r\n", Mail_address);
        send(smtpSocket, rcptToCommand, strlen(rcptToCommand), 0);
        recv(smtpSocket, buffer, sizeof(buffer), 0);
    }

    if (CC != "")
    {
        stringstream ss2(CC);
        char CC_address[30];
        while (ss2 >> CC_address)
        {
            char rcptToCommand[MAX_BUFFER_SIZE];
            sprintf(rcptToCommand, "RCPT TO:<%s>\r\n", CC_address);
            send(smtpSocket, rcptToCommand, strlen(rcptToCommand), 0);
            recv(smtpSocket, buffer, sizeof(buffer), 0);
        }
    }

    if (BCC != "")
    {
        stringstream ss3(BCC);
        char BCC_address[30];
        while (ss3 >> BCC_address)
        {
            char rcptToCommand[MAX_BUFFER_SIZE];
            sprintf(rcptToCommand, "RCPT TO:<%s>\r\n", BCC_address);
            send(smtpSocket, rcptToCommand, strlen(rcptToCommand), 0);
            recv(smtpSocket, buffer, sizeof(buffer), 0);
        }
    }

    // Gửi lệnh DATA
    const char* dataCommand = "DATA\r\n";
    send(smtpSocket, dataCommand, strlen(dataCommand), 0);
    recv(smtpSocket, buffer, sizeof(buffer), 0);

    // Gửi nội dung email
    char emailContent[MAX_BUFFER_SIZE];

    sprintf(emailContent, "From: %s <%s>\n", username, sender);
    send(smtpSocket, emailContent, strlen(emailContent), 0);

    sprintf(emailContent, "To: %s\n", recipient);
    send(smtpSocket, emailContent, strlen(emailContent), 0);

    sprintf(emailContent, "CC: %s\n", CC);
    send(smtpSocket, emailContent, strlen(emailContent), 0);

    sprintf(emailContent, "Subject: %s\n", subject);
    send(smtpSocket, emailContent, strlen(emailContent), 0);

    const char* Command_1 = "Content-Type: text/plain; charset=UTF-8;format=flowed\r\n";
    send(smtpSocket, Command_1, strlen(Command_1), 0);

    const char* Command_2 = "Content-Transfer-Encoding:7bit\r\n";
    send(smtpSocket, Command_2, strlen(Command_2), 0);

    sprintf(emailContent, "\r\n%s", body);
    send(smtpSocket, emailContent, strlen(emailContent), 0);

    int count = 0;
    while (count!=count_file)
    {
        char Command_3[MAX_BUFFER_SIZE];
        const char* Command_4 = "\r\nContent-Transfer-Encoding: base64\r\n";
        send(smtpSocket, Command_4, strlen(Command_4), 0);
        int pos=0;
        char file_name[100];
        for (int i = 0; i < strlen(L[count].link); i++)
        {
            if (L[count].link[i] == '/')
                pos = i;
        }
        strcpy(file_name, L[count].link + pos + 1);
        sprintf(Command_3, "Content-Disposition: attachment; filename=\"%s\"\r\n\r\n", file_name);
        send(smtpSocket, Command_3, strlen(Command_3), 0);

        string Input_Data = read_binary_file(L[count].link);
        string encoded_Data = base64_encode(Input_Data);
        int run = 0, start = 0, end = 0;
        string result;
        int do_dai = strlen(encoded_Data.c_str());
        while (end != strlen(encoded_Data.c_str())-1)
        {
            for (run; (run != start + 71) && (run != strlen(encoded_Data.c_str())-1); run++);
            end = run;
            result = encoded_Data.substr(start, end - start + 1);
            sprintf(Command_3, "%s\r\n", result.c_str());
            send(smtpSocket, Command_3, strlen(Command_3), 0);
            start = run + 1;
        }
        count++;
    }

    const char* Command_5 = "\r\n.\r\n";
    send(smtpSocket, Command_5, strlen(Command_5), 0);

    recv(smtpSocket, buffer, sizeof(buffer), 0);
    // Gửi lệnh QUIT
    const char* quitCommand = "QUIT\r\n";
    send(smtpSocket, quitCommand, strlen(quitCommand), 0);

    // Đóng kết nối
    closesocket(smtpSocket);

    // Clean up Winsock
    WSACleanup();
}
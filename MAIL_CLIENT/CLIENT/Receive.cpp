#include"Receive.h"
#include"Filter_Mail.h"
#include"Send.h"

string decode7bit(const string& input) {
    string decodedData;

    // Giải mã 8 bit thành 7 bit (loại bỏ bit kiểm tra)
    for (char c : input) {
        char decodedChar = c & 0x7F;  // Giữ 7 bit thấp
        decodedData += decodedChar;
    }

    return decodedData;
}

void Return_Folder_Adrress(const char* sender, char file_name[], string result)
{
    if (result == "Inbox")
    {
        strcat(file_name, sender);
        strcat(file_name, "\\");
        strcat(file_name, "Inbox");
        strcat(file_name, "\\");
    }
    else if (result == "Important")
    {
        strcat(file_name, sender);
        strcat(file_name, "\\");
        strcat(file_name, "Important");
        strcat(file_name, "\\");
    }
    else if (result == "Work")
    {
        strcat(file_name, sender);
        strcat(file_name, "\\");
        strcat(file_name, "Work");
        strcat(file_name, "\\");
    }
    else if (result == "Project")
    {
        strcat(file_name, sender);
        strcat(file_name, "\\");
        strcat(file_name, "Project");
        strcat(file_name, "\\");
    }
    else if (result == "Spam")
    {
        strcat(file_name, sender);
        strcat(file_name, "\\");
        strcat(file_name, "Spam");
        strcat(file_name, "\\");
    }
}

void Process_List_Response(char* response, int result[], int& m,const char* sender)
{
    // Phân tích và lấy số thứ tự của mỗi email
    const char* token = strtok(response, "\r\n");
    int emailNumber;

    int Start = 0;
    ifstream File_input;
    ofstream File_output;
    char file_name[100] = "";
    strcat(file_name, sender);
    strcat(file_name, "\\");
    strcat(file_name, sender);
    strcat(file_name, "_received_number.txt");
    File_input.open(file_name);
    if (!File_input.is_open())
    {
        File_input.close();
        File_output.open(file_name);
        File_output.close();
        File_input.open(file_name);
    }
    while (!File_input.eof())
    {
        File_input >> Start;
    }
    while (token != nullptr)
    {
        sscanf(token, "%d", &emailNumber);
        if (emailNumber > Start)
        {
            result[m++] = emailNumber;
        }
        token = strtok(nullptr, "\r\n");
    }
    File_input.close();
    if (m!=0)
    {
        ofstream File_output;
        File_output.open(file_name, ios::app);
        int count = 0;
        while (count != m - 1)
        {
            File_output << result[count++] << " ";
        }
        File_output.close();
    }
}

void Put_Content_In_To_File_demo_txt(ofstream& File_output, string content)
{
    int bien_chay = 0, bien_dau = 0, bien_cuoi = 0;
    string fromResult, toResult, CCResult, subjectResult, bodyResult;
    int i_from = 0, i_to = 0, i_CC = 0, i_subject = 0, i_body = 0;
    for (bien_chay = 0; content[bien_chay] != '\r'; bien_chay++);
    bien_chay += 2; bien_dau = bien_chay;
    for (bien_chay; content[bien_chay] != '\r'; bien_chay++);
    bien_cuoi = bien_chay;
    fromResult = content.substr(bien_dau, bien_cuoi - bien_dau);
    File_output << fromResult << endl;

    bien_chay += 2; bien_dau = bien_chay;
    for (bien_chay; content[bien_chay] != '\r'; bien_chay++);
    bien_cuoi = bien_chay;
    toResult = content.substr(bien_dau, bien_cuoi - bien_dau);
    File_output << toResult << endl;

    bien_chay += 2; bien_dau = bien_chay;
    for (bien_chay; content[bien_chay] != '\r'; bien_chay++);
    bien_cuoi = bien_chay;
    CCResult = content.substr(bien_dau, bien_cuoi - bien_dau);
    File_output << CCResult << endl;

    bien_chay += 2; bien_dau = bien_chay;
    for (bien_chay; content[bien_chay] != '\r'; bien_chay++);
    bien_cuoi = bien_chay;
    subjectResult = content.substr(bien_dau, bien_cuoi - bien_dau);
    File_output << subjectResult << endl;

    bien_chay += 2; bien_dau = bien_chay;
    for (bien_chay; content[bien_chay] != '\r'; bien_chay++);
    bien_cuoi = bien_chay;

    bien_chay += 2; bien_dau = bien_chay;
    for (bien_chay; content[bien_chay] != '\r'; bien_chay++);
    bien_cuoi = bien_chay;
    while (true)
    {
        bien_chay += 2; bien_dau = bien_chay;
        for (bien_chay; content[bien_chay] != '\r'; bien_chay++);
        bien_cuoi = bien_chay;
        bodyResult = content.substr(bien_dau, bien_cuoi - bien_dau);
        if (bodyResult == "Content-Transfer-Encoding: base64")
        {
            break;
        }
        if (bodyResult == ".")
        {
            break;
        }
        File_output << bodyResult << endl;
    }
}

void Put_Content_In_To_File_txt(ofstream& File_output, string content)
{
    int bien_chay = 0, bien_dau = 0, bien_cuoi = 0;
    string fromResult, toResult, CCResult, subjectResult, bodyResult;
    int i_from = 0, i_to = 0, i_CC = 0, i_subject = 0, i_body = 0;
    for (bien_chay = 0; content[bien_chay] != '\r'; bien_chay++);
    bien_chay += 2; bien_dau = bien_chay;
    for (bien_chay; content[bien_chay] != '\r'; bien_chay++);
    bien_cuoi = bien_chay;
    fromResult = content.substr(bien_dau, bien_cuoi - bien_dau);
    File_output << fromResult << endl;

    bien_chay += 2; bien_dau = bien_chay;
    for (bien_chay; content[bien_chay] != '\r'; bien_chay++);
    bien_cuoi = bien_chay;
    toResult = content.substr(bien_dau, bien_cuoi - bien_dau);
    File_output << toResult << endl;

    bien_chay += 2; bien_dau = bien_chay;
    for (bien_chay; content[bien_chay] != '\r'; bien_chay++);
    bien_cuoi = bien_chay;
    CCResult = content.substr(bien_dau, bien_cuoi - bien_dau);
    File_output << CCResult << endl;

    bien_chay += 2; bien_dau = bien_chay;
    for (bien_chay; content[bien_chay] != '\r'; bien_chay++);
    bien_cuoi = bien_chay;
    subjectResult = content.substr(bien_dau, bien_cuoi - bien_dau);
    File_output << subjectResult << endl;

    while (true)
    {
        bien_chay += 2; bien_dau = bien_chay;
        for (bien_chay; content[bien_chay] != '\r'; bien_chay++);
        bien_cuoi = bien_chay;
        bodyResult = content.substr(bien_dau, bien_cuoi - bien_dau);
        if (bodyResult == ".")
        {
            break;
        }
        File_output << bodyResult << endl;
    }
}

void Create_File_Contain_Content_Received_Mail(char* buffer, const char sender[], string content, int number, string result_destination)
{
    char temp[100];
    sprintf(temp, "%d.", number);
    ofstream File_output;
    char file_name[100] = "";
    Return_Folder_Adrress(sender, file_name, result_destination);
    strcat(file_name, temp);
    strcat(file_name, buffer);
    strcat(file_name, ".txt");
    File_output.open(file_name, ios::app);
    Put_Content_In_To_File_txt(File_output, content);
    File_output << "NO";
    File_output.close();
}

char* extractEmail(const char* input) {
    // Tìm vị trí của ký tự '<'
    const char* start = strchr(input, '<');

    // Lấy phần tử sau ký tự '<'
    char temp[256];  // Độ dài cố định
    sscanf(start + 1, "%[^>]", temp);

    // Cấp phát bộ nhớ động và sao chép chuỗi
    char* result = new char[strlen(temp) + 1];
    strcpy(result, temp);

    // Trả về con trỏ tới chuỗi đã cấp phát
    return result;
    
}

void Add_Downloaded_Mail_Adrress_To_File(char* buffer, const char sender[], char* buffer2, string result_destination)
{
    string s = buffer2;
    char* fromStart = strstr(buffer, "From:");
    char* subjectStart = strstr(buffer2, "Subject:");
    fromStart += strlen("From: ");

    char* fromString = strtok(fromStart, "\r");
    char* subjectString = strtok(subjectStart, "\r");
    ofstream File_output;
    ifstream File_input;
    char file_name[100] = "";
    Return_Folder_Adrress(sender, file_name, result_destination);
    strcat(file_name, sender);
    strcat(file_name, "_received_username_mail.txt");
    File_input.open(file_name);
    if (!File_input.is_open())
    {
        File_input.close();
        File_output.open(file_name);
        File_output.close();
        File_input.open(file_name);
    }
    int count = 1;
    string Get;
    while (getline(File_input, Get))
    {
        if (Get == fromString)
            count++;
    }
    char* file_number_name_txt = extractEmail(fromString);
    File_output.open(file_name, ios::app);
    File_output << fromString << endl;
    Create_File_Contain_Content_Received_Mail(file_number_name_txt, sender, s, count, result_destination);
    File_output << subjectString << endl;
    File_output << count << endl;
    
    File_output.close();
}


// Function to receive email using POP3
void Receive_Email(const char* server, int port, const char* username, const char* password) {
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return;
    }

    // Create a socket for POP3
    SOCKET pop3Socket = socket(AF_INET, SOCK_STREAM, 0);
    if (pop3Socket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << std::endl;
        WSACleanup();
        return;
    }

    // Connect to the POP3 server
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(server);

    if (connect(pop3Socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect to POP3 server." << std::endl;
        closesocket(pop3Socket);
        WSACleanup();
        return;
    }

    //Đọc phản hồi từ máy chủ POP3
    char buffer[MAX_BUFFER_SIZE];
    recv(pop3Socket, buffer, sizeof(buffer), 0);

    // Receive email commands (e.g., USER, PASS, LIST, RETR, etc.)
    // Gửi lệnh CAPA
    const char* ehloCommand = "CAPA\r\n";
    send(pop3Socket, ehloCommand, strlen(ehloCommand), 0);
    recv(pop3Socket, buffer, sizeof(buffer), 0);

    // Gửi lệnh USER
    char USERCommand[MAX_BUFFER_SIZE];
    sprintf(USERCommand, "USER %s\r\n", username);
    send(pop3Socket, USERCommand, strlen(USERCommand), 0);
    recv(pop3Socket, buffer, sizeof(buffer), 0);

    // Gửi lệnh PASS
    char PASSCommand[MAX_BUFFER_SIZE];
    sprintf(PASSCommand, "PASS %s\r\n", password);
    send(pop3Socket, PASSCommand, strlen(PASSCommand), 0);
    recv(pop3Socket, buffer, sizeof(buffer), 0);

    //Gửi lệnh STAT
    const char* STATCommand = "STAT\r\n";
    send(pop3Socket, STATCommand, strlen(STATCommand), 0);
    recv(pop3Socket, buffer, sizeof(buffer), 0);

    //Gửi lệnh LIST
    const char* LISTCommand = "LIST\r\n";
    send(pop3Socket, LISTCommand, strlen(LISTCommand), 0);

    int bytesRead = recv(pop3Socket, buffer, sizeof(buffer), 0);
    buffer[bytesRead] = '\0';
    int RETR_number[10]; int m = 0;
    Process_List_Response(buffer, RETR_number, m, username);

    //m!=0 tức  là tồn tại mail chưa tải xuống
    if (m != 0)
    {
        //Gửi lệnh UIDL
        PlaySound(TEXT("Tieng-ting-www_tiengdong_com.wav"), NULL, SND_FILENAME | SND_ASYNC);
        const char* UIDLCommand = "UIDL\r\n";
        send(pop3Socket, UIDLCommand, strlen(UIDLCommand), 0);
        recv(pop3Socket, buffer, sizeof(buffer), 0);
        //Gửi lệnh RETR 
        char RETRCommand[MAX_BUFFER_SIZE];
        int count = 0;
        char* s_buffer = new char[1000000000];
        while (count != m - 1)
        {
            sprintf(RETRCommand, "RETR %d\r\n", RETR_number[count++]);
            send(pop3Socket, RETRCommand, strlen(RETRCommand), 0);
            int bytesRead = recv(pop3Socket, s_buffer, 1000000000, 0);
            s_buffer[bytesRead] = '\0';
            ofstream demo_ouput;
            demo_ouput.open("demo.txt");
            Put_Content_In_To_File_demo_txt(demo_ouput,s_buffer);
            demo_ouput.close();
            string result_destination = Filer_Folder("demo.txt");;
            Add_Downloaded_Mail_Adrress_To_File(s_buffer, username, s_buffer, result_destination);
        }
        delete[] s_buffer;
    }
    // Gửi lệnh QUIT
    const char* QUITCommand = "QUIT\r\n";
    send(pop3Socket, QUITCommand, strlen(QUITCommand), 0);
    recv(pop3Socket, buffer, sizeof(buffer), 0);

    // Close the connection
    closesocket(pop3Socket);

    // Clean up Winsock
    WSACleanup();
}

void thread_Auto_Download_Mail(const char* server, int port, const char* username, const char* password, int AutoLoad)
{
    while (true)
    {
        Sleep(AutoLoad*1000);
        Receive_Email(server, port, username, password);
    }
}
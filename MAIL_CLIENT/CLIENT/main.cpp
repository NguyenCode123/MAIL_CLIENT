#include"Menu.h"
#include"Receive.h"
int main() {
    char recipient[200]=""; char subject[100]=""; char body[1000] = ""; char CC[200]; char BCC[200]; link_file L[10]; int count_file = 0;
    char username[50]; char password[50]; char sender[50]; char MailServer[20]; 
    int portSMTP; int portPOP3;
    int AutoLoad; char address_downloaded_file[100];
    Menu(username, password, sender, MailServer, portSMTP, portPOP3, AutoLoad, address_downloaded_file, recipient, subject, body, CC, BCC, L, count_file);
    return 0;
}
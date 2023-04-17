#include <stdio.h>
#include <string.h>

int MAX_LENGTH=256;

void send_mail(const char* email, const char* subject, const char* message){
    char command[MAX_LENGTH];
    sprintf(command, "mail -s \"%s\" %s", subject, email);
    FILE* mail_input= popen(command,"w");
    if (mail_input == NULL) {
        perror("popen error");
        return ;
    }
    fputs(message,mail_input);
    pclose(mail_input);

}
void print_mails(char* command){
    FILE* mail_input= popen(command,"r");
    if (mail_input == NULL) {
        perror("popen error");
        return ;
    }
    char buff[MAX_LENGTH];
    while (fgets(buff, MAX_LENGTH, mail_input) != NULL) {
        printf("%s\n", buff);
    }

    pclose(mail_input);

}

int main(int argc, char* argv[]){

    if(argc==2){
        char command[MAX_LENGTH];
        if (strcmp(argv[1], "nadawca") == 0)
        {
            sprintf(command, "mail -H | sort -k 2");
        }
        else if (strcmp(argv[1], "data") == 0)
        {
            sprintf(command, "mail -H | sort -k 4");
        }
        else
        {
            fprintf(stderr, "Unsupported sorting key: '%s'\n", argv[1]);
            return 1;
        }
        print_mails(command);

    }
    else if(argc==4){
        const char* email = argv[1];
        const char* subject = argv[2];
        const char* message = argv[3];
        send_mail(email, subject, message);

    }else
    {
        fprintf(stderr,"Wrong number of arguments.\n");
        return 1;
    }

    return 0;
}
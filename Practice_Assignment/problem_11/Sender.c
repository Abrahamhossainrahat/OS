#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/msg.h>
#include<sys/ipc.h>

struct msg_structure
{
    long msg_type;
    char msg_text[100];
};

int main()
{
    key_t key;
    int msgid;

    key = ftok("msgfile", 65);

    msgid = msgget(key, 0666 | IPC_CREAT);
    if(msgid < 0){
        perror("msgid generate failed.\n");
        exit(1);
    }

    struct msg_structure message;
    message.msg_type = 1;
    strcpy(message.msg_text, "Hello from Sender");

    msgsnd(msgid, &message, sizeof(message.msg_text), 0);
    printf("Sender Message : %s\n", message.msg_text);

    return 0;
}

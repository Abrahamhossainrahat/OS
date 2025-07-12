#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>

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

    msgrcv(msgid,&message, sizeof(message.msg_text), 1, 0 );
    printf("Revceiver received : %s\n", message.msg_text);
    
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
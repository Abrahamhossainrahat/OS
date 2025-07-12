#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/wait.h>

struct msg_structure
{
    long msg_type;
    char msg_text[100];
}; 

int main()
{
    key_t key;
    int msgid;
    struct msg_structure message;

    key = ftok("msgfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    if(msgid<0){
        perror("msgid generate failed.\n");
        exit(1);
    }

    pid_t pid = fork(); // child Process
    if(pid<0){
        perror("fork failed.\n");
        exit(1);
    }

    if(pid == 0){
        msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);
        printf("Child Receive : %s\n", message.msg_text);
        exit(0);
    }
    else{
        message.msg_type = 1;
        strcpy(message.msg_text, "Hello from Parent");
        msgsnd(msgid, &message, sizeof(message.msg_text), 0);
        printf("Parent Send : %s\n", message.msg_text);

        wait(NULL);
        msgctl(msgid, IPC_RMID, NULL);
    }
    return 0;
}

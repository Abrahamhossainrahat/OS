#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// message structure
struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key;
    int msgid;

    // Generate unique key
    key = ftok("msgfile", 65);

    // Create message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid < 0) {
        perror("msgget");
        exit(1);
    }

    struct msg_buffer message;
    message.msg_type = 1;

    strcpy(message.msg_text, "Hello from sender process!");

    // Send message
    msgsnd(msgid, &message, sizeof(message.msg_text), 0);
    printf("Sender: Message sent: %s\n", message.msg_text);

    return 0;
}

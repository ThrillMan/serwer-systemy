#include<stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

int main(){
    int mid = msgget(0x123, 0600 | IPC_CREAT);
    struct msgbuf
    {
    long type;
    char text[1024];
    } my_msg;
    strcpy(my_msg.text, "Hello world");
    my_msg.type =1; 
    msgsnd(mid, &my_msg, strlen(my_msg.text)+1, 0);
    //msgrcv(mid, &my_msg, 1024, 5, 0);
}

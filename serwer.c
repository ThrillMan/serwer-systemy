#include<stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <ctype.h>
#include <string.h>
int main(){
    int mid = msgget(0x123, 0600 | IPC_CREAT);
    struct msgbuf
    {
    int id;
    char text[1024];
    } my_msg;    my_msg.id =0;
//     strcpy(my_msg.text, "Hello world");
//     my_msg.type =2;
//     msgsnd(mid, &my_msg, strlen(my_msg.text)+1, 0);
    while(1){
    msgrcv(mid, &my_msg, sizeof(my_msg), 0, 0);
    printf("dostalem od klienta:%s\n",my_msg.text);
    my_msg.id=my_msg.id;
    msgsnd(mid, &my_msg, sizeof(my_msg), 0);
   }

}

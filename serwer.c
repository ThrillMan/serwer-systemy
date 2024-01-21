#include<stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <ctype.h>
#include <string.h>
int main(){
    int mid = msgget(0x123, 0600 | IPC_CREAT);

    int clientsIdSubject[5][5];//every clients writes what subject they are interested in
    int subjects[5];
    int numOfsubjects=0;

    struct msgbuf
    {
    int subject;
    int id;
    char name[20];
    char text[1024];
    } my_msg;




    while(1){
    msgrcv(mid, &my_msg, sizeof(my_msg), 0, 0);
    printf("dostalem od klienta o id:%d, imieniu:%s wiadomosc:%s\n",my_msg.id,my_msg.name,my_msg.text);

    msgsnd(my_msg.id, &my_msg, sizeof(my_msg), 0);



   }

}

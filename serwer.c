#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
int main(){
    int idOfServer = msgget(0x123, 0666 | IPC_CREAT);

    int clientsId[5]={0,0,0,0,0};
    int clientsChatroom[5]={0,0,0,0,0};
    int numOfclients=0;

    struct msgbuf
    {
    long mtype;
    int id;
    int subject;
    char name[20];
    char text[1024];
    } my_msg;

    my_msg.mtype =1;


    while(1){
    msgrcv(idOfServer, &my_msg, sizeof(my_msg), 10, 0);
    printf("dostalem od klienta o typie:%d, imieniu:%s wiadomosc:%s\n",my_msg.subject,my_msg.name,my_msg.text);

    int notThere = 1;
    for(int i = 0; i<=numOfclients;i++){
        if(my_msg.id!=clientsId[i]){
            notThere =1;
        }
        else{
            notThere = 0;
            break;
        }
    }

    if(notThere){
        clientsId[numOfclients]=my_msg.id;
        clientsChatroom[numOfclients]=my_msg.subject;
        numOfclients++;
    }

    for(int i=0;i<numOfclients;i++){
        if(clientsChatroom[i]==my_msg.subject){
            my_msg.mtype =my_msg.subject;
            msgsnd(idOfServer, &my_msg, sizeof(my_msg), 0);
        }


    }


   }

}

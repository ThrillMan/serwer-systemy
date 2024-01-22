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
    int numOfclients=0;

    struct msgbuf
    {
    long mtype;
    int id;
    char name[20];
    char text[1024];
    } my_msg;

    my_msg.mtype =1;


    while(1){
    msgrcv(idOfServer, &my_msg, sizeof(my_msg), 2, 0);
    printf("dostalem od klienta o id:%d, imieniu:%s wiadomosc:%s\n",my_msg.id,my_msg.name,my_msg.text);

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
        numOfclients++;
    }
//     for(int i = 0; i<numOfclients;i++){
//         printf("klient id:%d\n",clientsId[i]);
//         my_msg.id=clientsId[i];
//         my_msg.mtype =1;
//         msgsnd(msgget(clientsId[i], 0666 | IPC_CREAT), &my_msg, sizeof(my_msg), 0);
//     }

    for(int i=0;i<numOfclients;i++){
        my_msg.mtype =1;
        msgsnd(idOfServer, &my_msg, sizeof(my_msg), 0);

    }


   }

}

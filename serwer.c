#include<stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <ctype.h>
#include <string.h>
int main(){
    int mid = msgget(0x123, 0600 | IPC_CREAT);

    int clientsId[5]={0,0,0,0,0};
    int numOfclients=0;

    struct msgbuf
    {
    int id;
    char name[20];
    char text[1024];
    } my_msg;




    while(1){
    msgrcv(mid, &my_msg, sizeof(my_msg), 0, 0);
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
    for(int i = 0; i<numOfclients;i++){
        printf("klient id:%d\n",clientsId[i]);
        printf("in\n");
        my_msg.id=clientsId[i];
        msgsnd(clientsId[i], &my_msg, sizeof(my_msg), 0);
    }
    //msgsnd(my_msg.id, &my_msg, sizeof(my_msg), 0);



   }

}

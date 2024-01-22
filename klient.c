#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
int main(){
    int idOfServer = msgget(0x123, 0666 | IPC_CREAT);
    key_t clientKey = ftok(".",getpid());
    int mid = msgget(clientKey, 0666 | IPC_CREAT);
    printf("kluczem jest%d\n",mid);

     struct msgbuf
    {
    int id;
    char name[20];
    char text[1024];
    } my_msg;
    my_msg.id =clientKey;
    //name
    printf("Podaj imie:");
    fgets(my_msg.name,20,stdin);


    while(1){
            /*if(fork()==0){
                printf("\npodaj wiadomosc do serwera:");
                fgets(my_msg.text,1024,stdin);
                printf("\nwiad do serwera:%s\n",my_msg.text);
                msgsnd(idOfServer, &my_msg, sizeof(my_msg), 0);
            }
            else{
                if(msgrcv(mid, &my_msg, 1024, 0, 0)!=-1){
                printf("wiadomosc od serwera:%s\n",my_msg.text);
            }
            }*/
        printf("\npodaj wiadomosc do serwera:");
        fgets(my_msg.text,1024,stdin);
        printf("\nwiad do serwera:%s\n",my_msg.text);
        msgsnd(idOfServer, &my_msg, sizeof(my_msg), 0);
        if(msgrcv(idOfServer, &my_msg, 1024, 0, 0)!=-1){
            printf("wiadomosc od serwera:%s\n",my_msg.text);
        }

    }
}

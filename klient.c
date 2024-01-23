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
    //int mid = msgget(clientKey, 0666 | IPC_CREAT);
    //printf("kluczem jest%d\n",mid);


     struct msgbuf
    {
    long mtype;
    int id;
    int subject;
    char name[20];
    char text[1024];
    } my_msg;
    my_msg.id =clientKey;

    printf("Podaj imie:");
    fgets(my_msg.name,20,stdin);
    printf("\n");
    printf("Podaj o ktorym temacie chcesz podyskutowac?\n");
    printf("1.Ogolny\n");
    printf("2.Muzyka\n");
    printf("3.Gry\n");
    printf("4.Sport\n");
    char temp[20];
    fgets(temp,20,stdin);
    printf("\n");
    my_msg.subject=atoi(temp);

    long clientmtype = my_msg.mtype;
    int clientSubject = my_msg.subject;
    char clientName[20];
    strcpy(clientName, my_msg.name);
    //strcpy(clientText, text);

if(fork()==0){
        while(1){
            my_msg.mtype=clientSubject;
            if(msgrcv(idOfServer, &my_msg, sizeof(my_msg), clientSubject, 0)!=-1){
                my_msg.name[strcspn(my_msg.name,"\n")]=0;
                if(my_msg.id!=clientKey){
                printf("%s:%s\n",my_msg.name,my_msg.text);
                }
            }
        }
    }
else{
        while(1){
             strcpy(my_msg.name,clientName);
             my_msg.id = clientKey;
             my_msg.subject = clientSubject;
            fgets(my_msg.text,1024,stdin);
            printf("\n");
            my_msg.mtype =10;
            msgsnd(idOfServer, &my_msg, sizeof(my_msg), 0);
        }

        }


}

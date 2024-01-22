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
    long mtype;
    int id;
    int subject;
    char name[20];
    char text[1024];
    } my_msg;
    my_msg.id =clientKey;
    //my_msg.mtype =2;
    //name
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

if(fork()==0){
        while(1){
            my_msg.mtype=my_msg.subject;
            if(msgrcv(idOfServer, &my_msg, sizeof(my_msg), my_msg.subject, 0)!=-1){
                my_msg.name[strcspn(my_msg.name,"\n")]=0;
                if(my_msg.id!=clientKey){
                printf("%s:%s\n",my_msg.name,my_msg.text);
                }
            }
        }
    }
else{
        while(1){
            //printf("\npodaj wiadomosc do serwera:\n");
//             my_msg.name[strcspn(my_msg.name,"\n")]=0;
//             printf("%s:",my_msg.name);
            fgets(my_msg.text,1024,stdin);

            printf("\n");
            //printf("\nwiad do serwera:%s\n",my_msg.text);
            my_msg.mtype =10;
            msgsnd(idOfServer, &my_msg, sizeof(my_msg), 0);
        }

        }

//         printf("\npodaj wiadomosc do serwera:");
//         fgets(my_msg.text,1024,stdin);
//         printf("\nwiad do serwera:%s\n",my_msg.text);
//         msgsnd(idOfServer, &my_msg, sizeof(my_msg), 0);
//         my_msg.mtype =1;
//         if(msgrcv(idOfServer, &my_msg, 1024, 1, 0)!=-1){
//             printf("wiadomosc od serwera:%s\n",my_msg.text);
//         }




}

#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
int main(){
    int idOfServer = msgget(0x123, 0600 | IPC_CREAT);

    int mid = msgget(ftok(".",getpid()), 0600 | IPC_CREAT);
    printf("kluczem jest%d\n",mid);
     struct msgbuf
    {
    int subject;
    int id;
    char name[20];
    char text[1024];
    } my_msg;
    my_msg.id =mid;
    //name
    printf("Podaj imie:");
    fgets(my_msg.name,20,stdin);
    printf("Podaj id temat <0,4>:");
    //scanf("%d\n",&my_msg.subject);
    char temp[20];
    fgets(temp,20,stdin);
    my_msg.subject=atoi(temp);
    printf("Wybrany subject:%d",my_msg.subject);
    //subject
        while(1){
    printf("\npodaj wiadomosc do serwera:");
    fgets(my_msg.text,1024,stdin);
    printf("\nwiad do serwera:%s\n",my_msg.text);
    msgsnd(idOfServer, &my_msg, sizeof(my_msg), 0);
    printf("koniec wiadomosci\n");
    msgrcv(mid, &my_msg, 1024, 0, 0);
    printf("wiadomosc od serwera:%s\n",my_msg.text);
    }
}

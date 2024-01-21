#include<stdio.h>
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
    int id;
    char text[1024];
    } my_msg;
    //strcpy(my_msg.text, "Hello world");
    my_msg.id =mid;
    //msgsnd(0x123, &my_msg, sizeof(my_msg), 0);
        while(1){
    printf("podaj wiadomosc do serwera:\n");
    fgets(my_msg.text,1024,stdin);
    printf("wiad do serwera:%s\n",my_msg.text);
    msgsnd(idOfServer, &my_msg, sizeof(my_msg), 0);
    printf("koniec wiadomosci\n");
    //msgrcv(mid, &my_msg, 1024, 0, 0);
    //printf("wiadomosc od serwera:%s\n",my_msg.text);

    }
    //msgrcv(mid, &my_msg, 1024, 5, 0);
}

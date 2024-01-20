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
    long type;
    char text[1024];
    } my_msg;
    //strcpy(my_msg.text, "Hello world");
    //my_msg.type =2;
    //msgsnd(mid, &my_msg, strlen(my_msg.text)+1, 0);
//zad 2 jego wyglad
   /*while(1){
    msgrcv(mid, &my_msg, 1024, -5, 0);
    printf("odebrano id:%d\n",my_msg.type);
    printf("wiadomosc:%s\n",my_msg.text);
    
   }*/
    msgrcv(mid, &my_msg, 1024, 1, 0);
    char ch;
    int j = 0;
    char przejsciowy[30];
    strcpy(przejsciowy[30], strupr);
    while (my_msg.text[j]) {
        ch = my_msg.text[j];
        putchar(toupper(ch));
        j++;
    }
 
   
    printf("wieksze:%s",my_msg.text);
}

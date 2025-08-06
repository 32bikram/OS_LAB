#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void myfun(int sig){
    printf("Ha Ha, Not Stopping \n");
}
int main(){

    if(signal(SIGINT, myfun) == SIG_ERR){
        perror("signal failure");
    }
    while(1){
        printf("press cntrl+c to stop \n");
        sleep(1);
    }

    return 0;
}
~                                                                               
~                                                                               
~            

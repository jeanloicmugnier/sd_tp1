/* 
 * File:   main.c
 * Author: Jean-Loïc Mugnier <mugnier at polytech.unice.fr>
 *
 * Created on April 18, 2016, 7:10 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*
 1) 1o programa

send_signal_to(pid,sig)
if(pid doesnt exist)
    return error
else
    send sig to process(with pid)

 */
int send_signal_to(int pid, int sig) {
    int i = kill(sig, pid);
    if (i) { // error -> i=-1 = true
        perror("thread doesn't exist. pid : ");
        printf("pid is %d", pid);
        return -1;
    }
    return 0;
}

/*
2o programa
signal_receiver
recebe e trata 3 ou mais sinais (sigkill tem que terminar a execução do programa)
print diferent message for each signal
busy wait e blocking wait (parametro)*/

void signal_receiver(int sig) {
    switch (sig) {
        case SIGINT: printf("Signal SIGINT capturado");
        case SIGSEGV: printf("Signal SIGSEGV capturado");
        case SIGILL: printf("Signal SIGILL capturado");
        case SIGTERM: printf("Signal SIGTERM capturado");
    }
    printf("didnt enter the switch");
}

/*
 * 
 */
int main(int argc, char** argv) {
    printf("main");
    if (fork() == 0) { /* processus fils */
        printf("child process");
        int sun = getpid();
        send_signal_to(sun, SIGINT);

    }
    printf("main process");

    signal(SIGINT, signal_receiver);
    //    signal_receiver(SIGINT);
    return (EXIT_SUCCESS);
}


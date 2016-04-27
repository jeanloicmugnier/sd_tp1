/* 
 * File:   ex1.c
 * Author: Jean-Loïc Mugnier <mugnier at polytech.unice.fr>
 *
 * Created on April 26, 2016, 11:28 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>



/*
 1) 1o programa
send_signal_to(pid,sig)
if(pid doesnt exist)
    return error
else
    send sig to process(with pid)
 */

/*
2o programa
signal_receiver
recebe e trata 3 ou mais sinais (sigkill tem que terminar a execução do programa)
print diferent message for each signal
busy wait e blocking wait (parametro)*/
//
//void signal_receiver(int sig) {
//    switch (sig) {
//        case SIGINT: printf("Signal SIGINT capturado\n");
//        case SIGSEGV: printf("Signal SIGSEGV capturado");
//        case SIGILL: printf("Signal SIGILL capturado");
//        case SIGTERM: printf("Signal SIGTERM capturado");
//    }
//    printf("didnt enter the switch");
//}

int send_signal_to(long pid, int sig) {
    int i = kill(pid, sig);
    if (i) { // error -> i=-1 = true
        printf("process doesn't exist. pid : %lu ", pid);
        perror("end of process!\nbye bye");
        exit(1);
    }
    printf("Signal %d sent to process wich pid is : %lu ",sig ,pid);
    return 0;
}

void sigint_handler(int sig) {
    signal(SIGINT, SIG_IGN); //ctrl + c    
    printf("Signal SIGINT capturado\n");
    signal(SIGINT, sigint_handler); //ctrl + c    

}

/*
 * argv[1] = mode
 * argv[2] = pid of the process 
 * argv[3] = signal to send
 */
int main(int argc, char** argv) {
    char *p;
    long arg1 = strtol(argv[1], &p, 10);
    if (arg1 == 1) {//sender
        printf("SENDING MODE");
        long arg2 = strtol(argv[2], &p, 10);
        long arg3 = strtol(argv[3], &p, 10);
        printf("%d\n\n", arg1);
        send_signal_to(arg2, (int) arg3);


    } else if (!arg1) {//receiver
        printf("RECEIVING MODE\n\n");
        printf("process is waiting for signal!!!\n");
        printf("pid: %lu \n", (long) getpid());
        signal(SIGINT, sigint_handler); //ctrl + c

        while (1) {
            sleep(1);
        }

    }
    //    signal(SIGSEGV, SIG_IGN);
    //    signal(SIGILL, SIG_IGN);
    //    signal(SIGTERM, SIG_IGN);

    return (EXIT_SUCCESS);
}


/* 
 * File:   ex1.c
 * Author: Jean-Loïc Mugnier <mugnier at polytech.unice.fr>
 *
 * Created on April 18, 2016, 11:28 PM
 */
#define _POSIX_SOURC
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

int send_signal_to(long pid, int sig) {
    int i = kill(pid, sig);
    if (i) { // error -> i=-1 = true
        printf("process doesn't exist. pid : %lu ", pid);
        perror("end of process!\nbye bye");
        exit(1);
    }
    printf("Signal %d sent to process wich pid is : %lu ", sig, pid);
    return 0;
}

void sigint_handler(int sig) {
    signal(SIGINT, SIG_IGN); //ctrl + c    
    printf("Signal SIGINT capturado\n");

}

void sigill_handler(int sig) {
    signal(SIGILL, SIG_IGN); //ctrl + c    
    printf("Signal SIGILL capturado\n");

}

void sigterm_handler(int sig) {
    signal(SIGTERM, SIG_IGN); //ctrl + c    
    printf("Signal SIGTERM capturado\n");

}

/*
 * argv[1] = mode
 * argv[2] = pid of the process 
 * argv[3] = signal to send
 */
int main(int argc, char** argv) {
    char *p;
    int i = 1;
    long arg1 = strtol(argv[1], &p, 10);
    if (arg1 == 1) {//sender
        printf("SENDING MODE\n\n");
        long arg2 = strtol(argv[2], &p, 10);
        long arg3 = strtol(argv[3], &p, 10);
        send_signal_to(arg2, (int) arg3);


    } else if (!arg1) {//receiver
        printf("RECEIVING MODE\n\n");
        printf("process is waiting for signal!!!\n");
        printf("Waiting: pid: %lu \n", (long) getpid());
        signal(SIGINT, sigint_handler); //ctrl + c
        signal(SIGILL, sigill_handler);
        signal(SIGTERM, sigterm_handler);
        if (!strcmp(argv[2], "blocking")) {
            while (1) {
                sleep(1);
            }
        } else if (!strcmp(argv[2], "busy")) {
            while (i > 0) {
                i++;
                sleep(1);
            }
        }

    }

    return (EXIT_SUCCESS);
}


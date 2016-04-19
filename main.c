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
#include <stdlib.h>

/*
 * QUESTÂO 1
 1) 1o programa

send_signal_to(pid,sig)
if(pid doesnt exist)
    return error
else
    send sig to process(with pid)

 */
int send_signal_to(int pid, int sig) {
    int i = kill(sig, pid); //send the signal sig to the process of pid pid.
    if (i) { // error -> i=-1 = true
        perror("thread doesn't exist. pid : ");
        printf("pid is %d", pid);
        return -1; // convention in posix when error appears
    }
    return 0;
}

/*
 * QUESTÂO 1
2o programa
signal_receiver
recebe e trata 3 ou mais sinais (sigkill tem que terminar a execução do programa)
print diferent message for each signal
busy wait e blocking wait (parametro)
 */

void signal_receiver(int sig) {
    switch (sig) {
        case SIGINT: printf("Signal SIGINT capturado");
            break;
        case SIGSEGV: printf("Signal SIGSEGV capturado");
            break;
        case SIGILL: printf("Signal SIGILL capturado");
            break;
        case SIGTERM: printf("Signal SIGTERM capturado");
            break;
        default:printf("signal default");
    }
    printf("didnt enter the switch");
}

/*
 QUESTÃO 2
 
 */
int prime(int nb) {
    int i, flag = 0;
    for (i = 2; i <= nb / 2; ++i) {
        if (nb % i == 0) {
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        printf("%d is a prime number.", nb);
    else
        printf("%d is not a prime number.", nb);
    return 0;
}

int consumidor(int nb) {
    char* is_p = " false";
    if (prime(nb)) {
        is_p = " true";
    }
    printf("%d is %s", nb, is_p);
    return 0;
}

/*
 * deve gerar numeros inteiros aleat ́orios e crescentes
 * enviar qt numeros antes de enviar um 0
 * termina apos enviar 0
 * 
 */
int produtor(int qt) {
    int next_nb = 0;
    while (qt--) {// qt -> 0 and exits the loop
        next_nb = rand() + next_nb; // to be sure that next_nb is bigger than the previous
        //write in the pipe next_nb to the consumidor function
    }
    //write a 0 in the pipe
    exit(1); // end the program

}

/**
 * Criar um pipe 
 * fazer um fork
 * produtor escreve
 * consumidor le
 */
void questao2() {
    //fazer
}

/*
 * 
 */
int main(int argc, char** argv) {
    printf("main\n");
    if (fork() == 0) { // into the children process
        printf("child process\n"); //however, this message isn't printed. why it is not executing this part of the code?
        int child = getpid(); // gets the pid of this children process
        send_signal_to(child, SIGINT); // call the signal sending function

    }
    printf("main process\n ");

    signal(SIGINT, signal_receiver); // send the signal SIGINT to signal_receiver. however, nothing happens.
    //    signal_receiver(SIGINT);
    return (EXIT_SUCCESS);
}


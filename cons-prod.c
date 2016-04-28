/* 
 * File:   cons-prod.c
 * Author: Jean-Loïc Mugnier <mugnier at polytech.unice.fr>
 *
 * Created on April 18, 2016, 8:39 PM
 */
#define _POSIX_SOURCE
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int size = 20;
char buff[20];
int p[2];

int prime(int nb) {
    int i, flag = 1;
    for (i = 2; i <= nb / 2; ++i) {
        if (nb % i == 0) {
            flag = 0;
        }
    }
    return flag;
}
/**
 * read numbers in the pipe
 * tell if they are prime or not
 * must die after receiving a 0.
 * @return 
 */
int consumidor() {
    int integer;
    read(p[0], buff, sizeof (buff));
    sscanf(buff, "%d", &integer);
    if (!integer) {
        close(p[0]);
        return 1;
    }
    char * true = (prime(integer)) ? "prime" : "not prime";
    printf("Consumidor: %d  is %s\n", integer, true);
    return 0;

}

/*
 * must generate random and growing number
 * write nb numbers before sending a 0;
 * ends after sending a 0.
 * 
 */
int produtor(int nb) {
    int rand_nb = 1;
    char word[size];
    while (--nb) {
        rand_nb = rand_nb + (rand() % 100 ); // to be sure that rand_nb is bigger than the previous rand()%100>=0
        sprintf(word, "%d", rand_nb);
        write(p[1], word, sizeof (buff)); 
        printf("\nProdutor: sending new number: %d\n ", rand_nb);
    }
    write(p[1], 0, sizeof (buff)); 
    close(p[1]);
    return 1;
}

/*
 * 
 */
int main(int argc, char** argv) {
    srand(time(NULL)); // generator
    char* args;
    long nb = strtol(argv[1], &args, 10);
    if (!pipe(p)) {
        if (!fork()) {
            //filho
            close(p[0]);
            produtor(nb);
            printf("Produtor: sending 0.\nClosing produtor.\n");
            kill(getpid(), SIGKILL);

        } else {
            close(p[1]);
            while (--nb) {
                consumidor();
            }
            printf("Consumidor received: 0 \nClosing consumidor\n");
            kill(getpid(), SIGKILL);
        }
    }
    return 0;
}



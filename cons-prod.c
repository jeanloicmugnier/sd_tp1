/* 
 * File:   cons-prod.c
 * Author: Jean-Loïc Mugnier <mugnier at polytech.unice.fr>
 *
 * Created on April 25, 2016, 8:39 PM
 */

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/*
 QUESTÃO 2
 
 */
int prime(int nb) {
    int i, flag = 1;
    for (i = 2; i <= nb / 2; ++i) {
        if (nb % i == 0) {
            flag = 0;
        }   
    }
    return flag;
}

int consumidor(int nb) {
    printf("Consumidor received: %d\n", nb);
    if (!nb) {
        printf("%d was sent\nEnding program...\n", nb);
        exit(0);
    }
    char * true = (prime(nb)) ? "prime" : "not prime";
    printf("%d  is %s\n", nb, true);
    return 0;
}

/*
 * deve gerar numeros inteiros aleatorios e crescentes
 * enviar qt numeros antes de enviar um 0
 * termina apos enviar 0
 * 
 */
void produtor(int *rand_nb) {
    if (!(*rand_nb)) {
        printf("Produtor: sending 0.\nclosing process.\n");
        exit(0);
    }
    *rand_nb = *rand_nb + (rand() % 100); // to be sure that next_nb is bigger than the previous and 
    printf("\nProdutor: sending new number: %d\n ", *rand_nb);


}

/*
 * supondo um tamanho maximo do numero aleatorio criado
 */
int main(int argc, char** argv) {
    srand(time(NULL)); // generator
    int p[2], integer;
    int size = 3, nb = 10;
    int rand_nb = 1;
    int *ptr_rand = &rand_nb;
    char buff[size], word[size];
    if (!pipe(p)) {
        if (!fork()) {
            printf("Sun with pid %lu\n", (long) getpid());
            //filho
            /*  Fermer p[0] (sinon le fils est un lecteur potentiel => Pb de eof */
            close(p[0]);

            while (--nb) {
                produtor(ptr_rand);
                sprintf(word, "%d", *ptr_rand);
                write(p[1], word, sizeof (buff)); //write in the pipe next_nb to the consumidor function
            }
            close(p[1]);
            *ptr_rand = 0;
            produtor(ptr_rand);

        } else {
            printf("Father with pid %lu\n", (long) getpid());
            close(p[1]);
            while (--nb) {
                read(p[0], buff, sizeof (buff));
//                printf("\n\nDEBUG\nstring: %s\n", buff);
                //                printf("\n\nDEBUG\ninteger: %d\n", integer);
                sscanf(buff, "%d", &integer);
                consumidor(integer);
            }
        }
    }
    return 0;
}



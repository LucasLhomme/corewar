/*
** EPITECH PROJECT, 2024
** my.h
** File description:
** my.h BOOTCAMP
*/

#ifndef PROJECT_H
    #define PROJECT_H
    #include "my.h"
    #include "op.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <unistd.h>
    #include <signal.h>
    #include <stdint.h>
    #include <fcntl.h>
    #include <sys/wait.h>
    #include <limits.h>
    #include <string.h>
    #include <limits.h>
    #include <pwd.h>
    #include <sys/types.h>

/*Struct*/

typedef struct vm_s {
    int nb_cycles;
    char *player1;
    char *player2;
    int nb_player1;
    int nb_player2;
    char *ad_player1;
    char *ad_player2;
}vm_t;

/*Function*/

/* memory */

void free_vm(vm_t *vm);

#endif /* !PROJECT_H_ */

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

typedef struct player_s {
    char *player_name;
    int nb_player;
    char *ad_player;
}player_t;

typedef struct vm_s {
    int nb_cycles;
    player_t *player1;
    player_t *player2;
    player_t *player3;
    player_t *player4;
}vm_t;

/*Function*/

/* memory */

void free_vm(vm_t *vm);

/* parsing */

vm_t *parse_argument(char **av);

player_t *find_player_name(vm_t *vm, char *name);

/* error handling */

int handle_vm(vm_t *vm, int argc);

#endif /* !PROJECT_H_ */

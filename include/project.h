/*
** EPITECH PROJECT, 2024
** my.h
** File description:
** my.h BOOTCAMP
*/

#ifndef PROJECT_H
    #define PROJECT_H
    #define PROG_NAME_LENGTH 128
    #define CHAMP_MAX_SIZE   682
    #define COREWAR_EXEC_MAGIC 0xea83f3
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


typedef struct robot_s {
    char name[PROG_NAME_LENGTH + 1];
    char comment[COMMENT_LENGTH + 1];
    uint8_t code[CHAMP_MAX_SIZE];
    uint32_t code_size;
} robot_t;

typedef struct player_s {
    char *player_name;
    int nb_player;
    char *ad_player;
}player_t;

typedef struct vm_s {
    int nb_cycles;
    int nb_player;
    uint8_t memory[MEM_SIZE];
    player_t *player1;
    player_t *player2;
    player_t *player3;
    player_t *player4;
}vm_t;

typedef struct champions_s {
    robot_t *champion1;
    robot_t *champion2;
    robot_t *champion3;
    robot_t *champion4;
} champions_t;

/*Function*/

/* memory */

void free_vm(vm_t *vm);

void load_champions(vm_t *vm, champions_t *champions);

/* parsing */

vm_t *parse_argument(char **av);

player_t *find_player_name(vm_t *vm, char *name);

int parse_cor_file(const char *filename, robot_t *robot);

/* error handling */

int handle_vm(vm_t *vm, int argc);

#endif /* !PROJECT_H_ */

/*
** EPITECH PROJECT, 2024
** my.h
** File description:
** my.h BOOTCAMP
*/

#ifndef PROJECT_H
    #define PROJECT_H
    #define MAX_CHECKS 10
    #define PROG_NAME_LENGTH 128
    #define CHAMP_MAX_SIZE   682
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

typedef struct process_s {
    int player_id;
    int pc;
    int registers[REG_NUMBER];
    int carry;
    int wait_cycles;
    int alive;
    int last_live_cycle;
    struct process_s *next;
} process_t;

typedef struct battle_s {
    int cycle_count;
    int cycle_to_die;
    int check_count;
    int live_count;
    int last_live_player;
    process_t *processes;
} battle_t;

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

void free_struct(vm_t *vm, champions_t *champions);

void load_champions(vm_t *vm, champions_t *champions);

/* parsing */

vm_t *parse_argument(char **av);

player_t *find_player_name(vm_t *vm, char *name);

int parse_cor_file(const char *filename, robot_t *robot);

/* error handling */

int handle_vm(vm_t *vm, int argc);

/* battle */

int run_battle(vm_t *vm);

void execute_cycle(vm_t *vm, battle_t *battle);

void check_cycle_die(battle_t *battle, int *cycles_since_check);

int check_dump_condition(vm_t *vm, battle_t *battle);

#endif /* !PROJECT_H_ */

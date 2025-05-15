/*
** EPITECH PROJECT, 2025
** wirewar
** File description:
** load champions in the arena
*/

#include "project.h"

static int calculate_load_address(player_t *player, int current_index,
    int segment_size)
{
    int load_address = 0;

    if (player->ad_player == NULL)
        load_address = current_index * segment_size;
    else
        load_address = (int)my_strtol(player->ad_player);
    return load_address;
}

static void load_champion_memory(vm_t *vm, robot_t *robot, int load_address)
{
    int pos = 0;

    if (load_address < 0 || load_address >= MEM_SIZE)
        return;
    if (robot->code_size > MEM_SIZE)
        return;
    for (uint32_t j = 0; j < robot->code_size; j++) {
        pos = (load_address + j) % MEM_SIZE;
        vm->memory[pos] = robot->code[j];
    }
}

static void initialize_structure(vm_t *vm, champions_t *champions,
    player_t **players, robot_t **robots)
{
    if (!vm || !champions)
        return;
    players[0] = vm->player1;
    players[1] = vm->player2;
    players[2] = vm->player3;
    players[3] = vm->player4;
    robots[0] = champions->champion1;
    robots[1] = champions->champion2;
    robots[2] = champions->champion3;
    robots[3] = champions->champion4;
}

void load_champions(vm_t *vm, champions_t *champions)
{
    player_t *players[4] = {NULL, NULL, NULL, NULL};
    robot_t *robots[4] = {NULL, NULL, NULL, NULL};
    int num_players = 0;
    int current_player_index = 0;
    int segment_size = 0;
    int load_address = 0;

    initialize_structure(vm, champions, players, robots);
    num_players = vm->nb_player;
    if (num_players == 0)
        return;
    segment_size = MEM_SIZE / num_players;
    for (int i = 0; i < 4; i++) {
        if (!players[i] || !robots[i])
            continue;
        load_address = calculate_load_address(players[i], current_player_index,
            segment_size);
        load_champion_memory(vm, robots[i], load_address);
        current_player_index++;
    }
}

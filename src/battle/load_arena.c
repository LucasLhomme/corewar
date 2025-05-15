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

void load_champions(vm_t *vm, champions_t *champions)
{
    if (!vm || !champions)
        return;
    player_t *players[4] = { vm->player1, vm->player2, vm->player3,
        vm->player4 };
    robot_t *robots[4] = { champions->champion1, champions->champion2,
        champions->champion3, champions->champion4 };
    int num_players = vm->nb_player;
    int current_player_index = 0;
    int segment_size = 0;
    int load_address = 0;

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

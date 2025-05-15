/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** utils functions
*/

#include "project.h"

static void free_player(player_t *player)
{
    if (!player)
        return;
    if (player->player_name)
        free(player->player_name);
    if (player->ad_player)
        free(player->ad_player);
    free(player);
}

void free_vm(vm_t *vm)
{
    if (!vm)
        return;
    free_player(vm->player1);
    free_player(vm->player2);
    free_player(vm->player3);
    free_player(vm->player4);
    free(vm);
}

static void free_champions(champions_t *champions)
{
    if (champions->champion1)
        free(champions->champion1);
    if (champions->champion2)
        free(champions->champion2);
    if (champions->champion3)
        free(champions->champion3);
    if (champions->champion4)
        free(champions->champion4);
    free(champions);
}

void free_struct(vm_t *vm, champions_t *champions)
{
    if (vm)
        free_vm(vm);
    if (champions)
        free_champions(champions);
}

player_t *find_player_name(vm_t *vm, char *name)
{
    if (vm->player1 && vm->player1->player_name &&
        my_strcmp(vm->player1->player_name, name) == 0)
        return vm->player1;
    if (vm->player2 && vm->player2->player_name &&
        my_strcmp(vm->player2->player_name, name) == 0)
        return vm->player2;
    if (vm->player3 && vm->player3->player_name &&
        my_strcmp(vm->player3->player_name, name) == 0)
        return vm->player3;
    if (vm->player4 && vm->player4->player_name &&
        my_strcmp(vm->player4->player_name, name) == 0)
        return vm->player4;
    return NULL;
}

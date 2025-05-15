/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** handle error
*/

#include "project.h"

static int handle_player(player_t *player)
{
    if (!player || !player->player_name)
        return 84;        
    if (my_strncmp("roc.", my_revstr(player->player_name), 4)) {
        my_revstr(player->player_name);
        return 84;
    }
    my_revstr(player->player_name);
    return 0;
}

static int check_bonus_player(vm_t *vm)
{
    if (vm->player2 && vm->player3 &&
        vm->player2->nb_player == vm->player3->nb_player &&
        vm->player2->nb_player != 0)
        return 84;
    if (vm->player2 && vm->player4 &&
        vm->player2->nb_player == vm->player4->nb_player &&
        vm->player2->nb_player != 0)
        return 84;
    if (vm->player3 && vm->player4 &&
        vm->player3->nb_player == vm->player4->nb_player &&
        vm->player3->nb_player != 0)
        return 84;
    return 0;
}

static int check_player_number(vm_t *vm)
{
    if (vm->player1 && vm->player2 &&
        vm->player1->nb_player == vm->player2->nb_player &&
        vm->player1->nb_player != 0)
        return 84;
    if (vm->player1 && vm->player3 &&
        vm->player1->nb_player == vm->player3->nb_player &&
        vm->player1->nb_player != 0)
        return 84;
    if (vm->player1 && vm->player4 &&
        vm->player1->nb_player == vm->player4->nb_player &&
        vm->player1->nb_player != 0)
        return 84;
    if (check_bonus_player(vm) == 84)
        return 84;
    return 0;
}

int handle_vm(vm_t *vm, int argc)
{
    if (argc < 3)
        return 84;
    if (handle_player(vm->player1) == 84 || handle_player(vm->player2) == 84)
        return 84;
    if (vm->player3 && handle_player(vm->player3) == 84)
        return 84;
    if (vm->player4 && handle_player(vm->player4) == 84)
        return 84;
    if (check_player_number(vm) == 84)
        return 84;
    return 0;
}

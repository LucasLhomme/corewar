/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** parse the arguments for set the vm
*/

#include "project.h"

static int attribute_playera(vm_t *vm, char **av, int i)
{
    player_t *player = NULL;

    for (int j = i + 2; av[j] != NULL; j++) {
        player = find_player_name(vm, av[j]);
        if (player) {
            player->ad_player = my_strdup(av[i + 1]);
            return 0;
        }
    }
    return 84;
}

static int attribute_playern(vm_t *vm, char **av, int i)
{
    player_t *player = NULL;

    for (int j = i + 2; av[j] != NULL; j++) {
        player = find_player_name(vm, av[j]);
        if (player) {
            player->nb_player = my_atoi(av[i + 1]);
            return 0;
        }
    }
    return 84;
}

static int parse_flag(vm_t *vm, char **av, int i)
{
    if (my_strcmp(av[i], "-n") == 0) {
        if (attribute_playern(vm, av, i) == 84)
            return 84;
        else
            return 0;
    }
    if (my_strcmp(av[i], "-a") == 0) {
        if (attribute_playera(vm, av, i) == 84)
            return 84;
        else
            return 0;
    }
    return 0;
}

static int find_flag(char **av, vm_t *vm, int i)
{
    if (my_strcmp(av[i], "-dump") == 0) {
        vm->nb_cycles = my_atoi(av[i + 1]);
        return 0;
    }
    if (my_strcmp(av[i], "-a") == 0 || my_strcmp(av[i], "-n") == 0) {
        if (parse_flag(vm, av, i) == 84)
            return 84;
    }
    return 0;
}

static player_t *create_player(char *name)
{
    player_t *player = malloc(sizeof(player_t));

    if (!player)
        return NULL;
    player->player_name = my_strdup(name);
    player->nb_player = 0;
    player->ad_player = NULL;
    return player;
}

static int add_more_player(vm_t *vm, char *player_name)
{
    if (!vm->player3) {
        vm->player3 = create_player(player_name);
        return 1;
    } else if (!vm->player4) {
        vm->player4 = create_player(player_name);
        return 1;
    } else
        return 84;
}

static int add_player(vm_t *vm, char *player_name)
{
    if (!vm->player1) {
        vm->player1 = create_player(player_name);
        return 1;
    } else if (!vm->player2) {
        vm->player2 = create_player(player_name);
        return 1;
    }
    if (add_more_player(vm, player_name) == 1)
        return 1;
    else
        return 84;
}

static int check_args(vm_t *vm, char **av, int i)
{
    if ((my_strcmp("-dump", av[i]) == 0) || (my_strcmp("-a", av[i]) == 0) ||
    (my_strcmp("-n", av[i]) == 0)) {
        return 2;
    } else
        return add_player(vm, av[i]);
}

static int find_player(vm_t *vm, char **av)
{
    int i = 1;
    int ret = 0;

    while (av[i] != NULL) {
        ret = check_args(vm, av, i);
        if (ret == 84)
            return 84;
        i += ret;
    }
    if (vm->player1 && vm->player2)
        return 0;
    else
        return 84;
}

vm_t *parse_argument(char **av)
{
    vm_t *vm = calloc(1, sizeof(vm_t));

    if (!vm)
        return NULL;
    vm->nb_cycles = 0;
    if (find_player(vm, av) == 84) {
        free_vm(vm);
        return NULL;
    }
    for (int i = 0; av[i] != NULL; i++) {
        if (find_flag(av, vm, i) == 84) {
            free_vm(vm);
            return NULL;
        }
    }
    return vm;
}

/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** utils functions
*/

#include "project.h"

void free_vm(vm_t *vm)
{
    if (vm->ad_player1)
        free(vm->ad_player1);
    if (vm->ad_player1)
        free(vm->ad_player2);
    if (vm->ad_player1)
        free(vm->player1);
    if (vm->ad_player1)
        free(vm->player2);
    free(vm);
}

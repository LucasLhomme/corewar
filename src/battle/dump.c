/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** dump
*/

#include "my.h"
#include "project.h"

static void dump_memory(vm_t *vm)
{
    const int BYTES_PER_LINE = 32;

    for (int i = 0; i < MEM_SIZE; i += BYTES_PER_LINE) {
        print_address_hex(i);
        for (int j = 0; j < BYTES_PER_LINE && (i + j) < MEM_SIZE; j++) {
            print_mem8(vm->memory[i + j]);
        }
        my_putchar('\n');
    }
}

int check_dump_condition(vm_t *vm, battle_t *battle)
{
    if (vm->nb_cycles > 0 && battle->cycle_count > 0 &&
        (battle->cycle_count % vm->nb_cycles) == 0) {
        dump_memory(vm);
        my_printf("\n\n");
        return 0;
    }
    return 0;
}

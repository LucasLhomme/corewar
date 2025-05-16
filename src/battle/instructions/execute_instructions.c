/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** execute the instructions cycle
*/

#include "project.h"

static const instruction_handler_t instruction_handlers[17] = {
    NULL,
    execute_live,
    execute_st,
    execute_add,
    execute_sub,
    execute_zjmp,
    NULL
};

static void execute_instruction(vm_t *vm, process_t *process, battle_t *battle)
{
    uint8_t opcode = vm->memory[process->pc];

    if (opcode == 0 || opcode > 16) {
        process->pc = (process->pc + 1) % MEM_SIZE;
        return;
    }
    if (instruction_handlers[opcode] != NULL) {
        instruction_handlers[opcode](vm, process, battle);
    } else {
        process->pc = (process->pc + 1) % MEM_SIZE;
    }
}

static void check_opcode(vm_t *vm, process_t *process)
{
    uint8_t opcode = vm->memory[process->pc];

    if (opcode >= 1 && opcode <= 16) {
        process->wait_cycles = op_tab[opcode - 1].nbr_cycles - 1;
    } else {
        process->pc = (process->pc + 1) % MEM_SIZE;
        process->wait_cycles = 0;
    }
}

static void process_instruction(vm_t *vm, process_t *process,
    battle_t *battle)
{
    if (!process->alive)
        return;
    if (process->wait_cycles > 0) {
        process->wait_cycles--;
        return;
    }
    execute_instruction(vm, process, battle);
    check_opcode(vm, process);
}

void execute_cycle(vm_t *vm, battle_t *battle)
{
    process_t *current = battle->processes;

    while (current) {
        if (current->alive)
            process_instruction(vm, current, battle);
        current = current->next;
    }
    battle->cycle_count++;
}

/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** instructions
*/

#include "project.h"

void execute_zjmp(vm_t *vm, process_t *process)
{
    int index = (vm->memory[(process->pc + 1) % MEM_SIZE] << 8) |
        (vm->memory[(process->pc + 2) % MEM_SIZE]);

    if (process->carry == 1)
        process->pc = (process->pc + (index % IDX_MOD)) % MEM_SIZE;
    else
        process->pc = (process->pc + 3) % MEM_SIZE;
}

void execute_add(vm_t *vm, process_t *process)
{
    int reg1 = vm->memory[(process->pc + 2) % MEM_SIZE];
    int reg2 = vm->memory[(process->pc + 3) % MEM_SIZE];
    int reg3 = vm->memory[(process->pc + 4) % MEM_SIZE];

    if (reg1 >= 1 && reg1 <= REG_NUMBER &&
        reg2 >= 1 && reg2 <= REG_NUMBER &&
        reg3 >= 1 && reg3 <= REG_NUMBER) {
        process->registers[reg3 - 1] = process->registers[reg1 - 1] + process->registers[reg2 - 1];
        process->carry = (process->registers[reg3 - 1] == 0) ? 1 : 0;
    }
    process->pc = (process->pc + 5) % MEM_SIZE;
}

void execute_sub(vm_t *vm, process_t *process)
{
    int reg1 = vm->memory[(process->pc + 2) % MEM_SIZE];
    int reg2 = vm->memory[(process->pc + 3) % MEM_SIZE];
    int reg3 = vm->memory[(process->pc + 4) % MEM_SIZE];

    if (reg1 >= 1 && reg1 <= REG_NUMBER &&
        reg2 >= 1 && reg2 <= REG_NUMBER &&
        reg3 >= 1 && reg3 <= REG_NUMBER) {
        process->registers[reg3 - 1] = process->registers[reg1 - 1] - process->registers[reg2 - 1];
        process->carry = (process->registers[reg3 - 1] == 0) ? 1 : 0;
    }
    process->pc = (process->pc + 5) % MEM_SIZE;
}

void execute_st(vm_t *vm, process_t *process)
{
    int reg_src, param2;
    int address = 0;
    int ind_value = 0;

    reg_src = vm->memory[(process->pc + 2) % MEM_SIZE];
    if (reg_src < 1 || reg_src > REG_NUMBER) {
        process->pc = (process->pc + 4) % MEM_SIZE;
        return;
    }
    param2 = vm->memory[(process->pc + 3) % MEM_SIZE];
    if ((vm->memory[(process->pc + 1) % MEM_SIZE] >> 4 & 0x03) == 1) {
        if (param2 >= 1 && param2 <= REG_NUMBER)
            process->registers[param2 - 1] = process->registers[reg_src - 1];
        process->pc = (process->pc + 4) % MEM_SIZE;
    } else if ((vm->memory[(process->pc + 1) % MEM_SIZE] >> 4 & 0x03) == 3) {
        ind_value = (vm->memory[(process->pc + 3) % MEM_SIZE] << 8) |
            (vm->memory[(process->pc + 4) % MEM_SIZE]);
        address = (process->pc + (ind_value % IDX_MOD)) % MEM_SIZE;
        vm->memory[address] = (process->registers[reg_src - 1] >> 24) & 0xFF;
        vm->memory[(address + 1) % MEM_SIZE] = (process->registers[reg_src - 1] >> 16) & 0xFF;
        vm->memory[(address + 2) % MEM_SIZE] = (process->registers[reg_src - 1] >> 8) & 0xFF;
        vm->memory[(address + 3) % MEM_SIZE] = process->registers[reg_src - 1] & 0xFF;
        process->pc = (process->pc + 5) % MEM_SIZE;
    } else
        process->pc = (process->pc + 5) % MEM_SIZE;
}

static void display_live_message(vm_t *vm, int player_id)
{
    player_t *players[4] = {vm->player1, vm->player2, vm->player3,
        vm->player4};
    char *player_name = NULL;

    for (int i = 0; i < 4; i++) {
        if (!players[i])
            continue;
        if ((players[i]->nb_player == 0 && i + 1 == player_id) ||
            players[i]->nb_player == player_id) {
            player_name = players[i]->player_name;
            break;
        }
    }
    if (player_name)
        my_printf("The player %d(%s) is alive.\n", player_id, player_name);
}

static void update_values(vm_t *vm, int player_id, battle_t *battle,
    process_t *process)
{
    display_live_message(vm, player_id);
    battle->live_count++;
    battle->last_live_player = player_id;
    process->last_live_cycle = battle->cycle_count;
}

void execute_live(vm_t *vm, process_t *process, battle_t *battle)
{
    int player_id = (vm->memory[(process->pc + 1) % MEM_SIZE] << 24) |
                (vm->memory[(process->pc + 2) % MEM_SIZE] << 16) |
                (vm->memory[(process->pc + 3) % MEM_SIZE] << 8) |
                (vm->memory[(process->pc + 4) % MEM_SIZE]);
    int valid_id = 0;
    player_t *players[4] = {vm->player1, vm->player2,
        vm->player3, vm->player4};

    for (int i = 0; i < 4; i++) {
        if (!players[i])
            continue;
        if ((players[i]->nb_player == 0 && i + 1 == player_id) ||
            players[i]->nb_player == player_id) {
            valid_id = 1;
            break;
        }
    }
    if (valid_id)
        update_values(vm, player_id, battle, process);
    process->pc = (process->pc + 5) % MEM_SIZE;
}
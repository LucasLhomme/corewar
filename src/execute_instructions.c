/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** execute the instructions cycle
*/

#include "project.h"

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
        printf("The player %d(%s) is alive.\n", player_id, player_name);
}

static void execute_live(vm_t *vm, process_t *process, battle_t *battle)
{
    int player_id;

    player_id = (vm->memory[(process->pc + 1) % MEM_SIZE] << 24) |
                (vm->memory[(process->pc + 2) % MEM_SIZE] << 16) |
                (vm->memory[(process->pc + 3) % MEM_SIZE] << 8) |
                (vm->memory[(process->pc + 4) % MEM_SIZE]);
    
    // Find if this is a valid player ID
    int valid_id = 0;
    player_t *players[4] = {vm->player1, vm->player2, vm->player3, vm->player4};
    
    for (int i = 0; i < 4; i++) {
        if (!players[i])
            continue;
        if ((players[i]->nb_player == 0 && i + 1 == player_id) ||
            players[i]->nb_player == player_id) {
            valid_id = 1;
            break;
        }
    }
    
    if (valid_id) {
        display_live_message(vm, player_id);
        battle->live_count++;
        battle->last_live_player = player_id;
        process->last_live_cycle = battle->cycle_count;
    }
    
    process->pc = (process->pc + 5) % MEM_SIZE;
}

static void execute_instruction(vm_t *vm, process_t *process, battle_t *battle)
{
    uint8_t opcode = vm->memory[process->pc];

    if (opcode == 0) {
        process->pc = (process->pc + 1) % MEM_SIZE;
        return;
    }

    if (opcode >= 1 && opcode <= 16) {
        switch (opcode) {
            case 1: // live
                execute_live(vm, process, battle);
                break;
            // Implement other opcodes as needed
            default:
                process->pc = (process->pc + 1) % MEM_SIZE;
                break;
        }
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

/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** handle battle loop
*/

#include "project.h"

static void init_registers(process_t *process)
{
    for (int j = 0; j < REG_NUMBER; j++)
        process->registers[j] = 0;
    process->registers[0] = process->player_id;
}

static int calculate_laddress(player_t *player, int index,
    int segment_size)
{
    int load_address = 0;

    if (!player->ad_player)
        load_address = (index * segment_size) % MEM_SIZE;
    else
        load_address = (int)my_strtol(player->ad_player) % MEM_SIZE;
    return load_address;
}

static process_t *create_process(player_t *player, int index, int segment_size)
{
    process_t *new_process = malloc(sizeof(process_t));

    if (!new_process)
        return NULL;
    new_process->player_id = player->nb_player == 0 ?
    index + 1 : player->nb_player;
    new_process->pc = calculate_laddress(player, index, segment_size);
    new_process->carry = 0;
    new_process->wait_cycles = 0;
    new_process->alive = 1;
    new_process->last_live_cycle = 0;
    init_registers(new_process);
    return new_process;
}

static process_t *initialize_processes(vm_t *vm)
{
    process_t *head = NULL;
    process_t *new_process = NULL;
    player_t *players[4] = {vm->player1, vm->player2,
        vm->player3, vm->player4};
    int segment_size = 0;

    if (vm->nb_player <= 0)
        return NULL;
    segment_size = MEM_SIZE / vm->nb_player;
    for (int i = 0; i < 4; i++) {
        if (!players[i])
            continue;
        new_process = create_process(players[i], i, segment_size);
        if (!new_process)
            return NULL;
        new_process->next = head;
        head = new_process;
    }
    return head;
}

static int is_battle_over(battle_t *battle)
{
    process_t *current = battle->processes;
    int alive_processes = 0;

    while (current) {
        if (current->alive)
            alive_processes++;
        current = current->next;
    }
    return alive_processes == 0;
}

static void display_winner(vm_t *vm, battle_t *battle)
{
    player_t *players[4] = {vm->player1, vm->player2, vm->player3,
        vm->player4};
    char *player_name = NULL;
    int winner_id = battle->last_live_player;

    for (int i = 0; i < 4; i++) {
        if (!players[i])
            continue;
        if ((players[i]->nb_player == 0 && i + 1 == winner_id) ||
            players[i]->nb_player == winner_id) {
            player_name = players[i]->player_name;
            break;
        }
    }
    if (player_name)
        my_printf("The player %d(%s) has won.\n", winner_id, player_name);
    else
        my_printf("No winner\n");
}

static void free_processes(process_t *processes)
{
    process_t *current = processes;
    process_t *next;

    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
}

static battle_t *initialize_battle(vm_t *vm)
{
    battle_t *battle = malloc(sizeof(battle_t));

    if (!battle)
        return NULL;
    battle->cycle_count = 0;
    battle->cycle_to_die = CYCLE_TO_DIE;
    battle->check_count = 0;
    battle->live_count = 0;
    battle->last_live_player = 0;
    battle->processes = initialize_processes(vm);
    return battle;
}

static void finalize_battle(vm_t *vm, battle_t *battle)
{
    display_winner(vm, battle);
    free_processes(battle->processes);
    free(battle);
}

int run_battle(vm_t *vm)
{
    battle_t *battle = initialize_battle(vm);
    int cycles_since_check = 0;

    if (!battle || !battle->processes) {
        free(battle);
        return 84;
    }
    while (!is_battle_over(battle)) {
        execute_cycle(vm, battle);
        check_cycle_die(battle, &cycles_since_check);
        if (check_dump_condition(vm, battle))
            break;
    }
    finalize_battle(vm, battle);
    return 0;
}

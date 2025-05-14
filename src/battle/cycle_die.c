/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** handle cycle to die
*/

#include "project.h"

static void update_live(battle_t *battle)
{
    process_t *current = battle->processes;

    while (current) {
        if (current->alive && (battle->cycle_count - current->last_live_cycle)
        >= battle->cycle_to_die) {
            current->alive = 0;
        }
        current = current->next;
    }
}

static void update_linked(battle_t *battle, process_t *next, process_t *prev)
{
    if (prev)
        prev->next = next;
    else
        battle->processes = next;
}

static void check_processes(battle_t *battle)
{
    process_t *current = battle->processes;
    process_t *prev = NULL;
    process_t *next = NULL;

    while (current) {
        next = current->next;
        if (current->alive == 0) {
            update_linked(battle, next, prev);
            free(current);
        } else
            prev = current;
        current = next;
    }
}

static void handle_cycle_die(battle_t *battle)
{
    if (battle->cycle_to_die < 0)
        battle->cycle_to_die = 0;
}

void check_cycle_die(battle_t *battle, int *cycles_since_check)
{
    (*cycles_since_check)++;
    if (*cycles_since_check >= battle->cycle_to_die) {
        *cycles_since_check = 0;
        update_live(battle);
        battle->check_count++;
        if (battle->live_count >= NBR_LIVE ||
            battle->check_count >= MAX_CHECKS) {
            battle->cycle_to_die -= CYCLE_DELTA;
            handle_cycle_die(battle);
            battle->check_count = 0;
        }
        battle->live_count = 0;
        check_processes(battle);
    }
}

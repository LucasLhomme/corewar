/*
** EPITECH PROJECT, 2025
** mini_shell 1
** File description:
** main file
*/

#include "project.h"

void handle_flagh(void)
{
    my_printf("USAGE:\n./corewar [-dump nbr_cycle] [[-n prog_number] [-a loa");
    my_printf("d_address] prog_name] ...\nDESCRIPTION\n-dump nbr_cycle dumps");
    my_printf(" the memory after the nbr_cycle execution (if the round isn't");
    my_printf("\nalready over) with the following format: 32 bytes/line in");
    my_printf(" hexadecimal (A0BCDEFE1DD3...)\n-n prog_number sets the next ");
    my_printf("program's number. By default, the first free number in the\n");
    my_printf("parameter order\n-a load_address sets the next program's ");
    my_printf("loading address. When no address is specified,\n optimize the");
    my_printf(" addresses so that the processes are as far away from each ");
    my_printf("other as\npossible. The addresses are MEM_SIZE modulo.");
}

static void display_player_info(player_t *player, int num)
{
    if (!player)
        return;
    my_printf("P%d: name:%s, num:%d, addr:%s\n", num,
        player->player_name ? player->player_name : "NULL",
        player->nb_player,
        player->ad_player ? player->ad_player : "NULL");
}

int main(int argc, char **argv)
{
    vm_t *vm = NULL;

    if (argc > 1 && my_strcmp(argv[1], "-h") == 0 && argc == 2) {
        handle_flagh();
        return 0;
    }
    vm = parse_argument(argv);
    if (vm == NULL)
        return 84;
    if (handle_vm(vm, argc) == 84)
        return 84;
    display_player_info(vm->player1, 1);
    display_player_info(vm->player2, 2);
    display_player_info(vm->player3, 3);
    display_player_info(vm->player4, 4);
    my_printf("Dump cycle: %d\n", vm->nb_cycles);
    free_vm(vm);
    return 0;
}

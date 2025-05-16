/*
** EPITECH PROJECT, 2025
** mini_shell 1
** File description:
** main file
*/

#include "my.h"
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
    my_printf("P%d: name: %s, num:%d, addr:%s\n", num,
        player->player_name ? player->player_name : "NULL",
        player->nb_player,
        player->ad_player ? player->ad_player : "NULL");
}

static void display_robot(robot_t *robot, int num)
{
    my_printf("\nPlayer %d:\nName: %s\n", num, robot->name);
    for (uint32_t i = 0; i < robot->code_size; i++) {
        if (i % 16 == 0)
            print_address_hex(i);
        print_mem8(robot->code[i]);
        if ((i + 1) % 16 == 0)
            my_putchar('\n');
    }
    if (robot->code_size % 16 != 0)
        my_putchar('\n');
}

static void display_info(vm_t *vm, champions_t *champions, int val)
{
    if (val == 0) {
        display_player_info(vm->player1, 1);
        display_player_info(vm->player2, 2);
        if (vm->player3)
            display_player_info(vm->player3, 3);
        if (vm->player4)
            display_player_info(vm->player4, 4);
        my_printf("Dump cycle: %d", vm->nb_cycles);
    }
    if (val == 1 && champions) {
        if (champions->champion1)
            display_robot(champions->champion1, 1);
        if (champions->champion2)
            display_robot(champions->champion2, 2);
        if (vm->player3 && champions->champion3)
            display_robot(champions->champion3, 3);
        if (vm->player4 && champions->champion4)
            display_robot(champions->champion4, 4);
    }
    my_printf("\n");
}

static void initialize_champion(champions_t *champions, vm_t *vm)
{
    if (vm->player1)
        champions->champion1 = malloc(sizeof(robot_t));
    else
        champions->champion1 = NULL;
    if (vm->player2)
        champions->champion2 = malloc(sizeof(robot_t));
    else
        champions->champion2 = NULL;
    if (vm->player3)
        champions->champion3 = malloc(sizeof(robot_t));
    else
        champions->champion3 = NULL;
    if (vm->player4)
        champions->champion4 = malloc(sizeof(robot_t));
    else
        champions->champion4 = NULL;
}

static int parse_champion(player_t *player, robot_t *champion,
    vm_t *vm, champions_t *champions)
{
    if (!player || !champion)
        return 0;
    if (parse_cor_file(player->player_name, champion) == 84) {
        free_struct(vm, champions);
        return 84;
    }
    return 0;
}

static champions_t *parse_champions(vm_t *vm)
{
    champions_t *champions = malloc(sizeof(champions_t));

    if (!champions)
        return NULL;
    initialize_champion(champions, vm);
    if (parse_champion(vm->player1, champions->champion1, vm,
        champions) == 84)
        return NULL;
    if (parse_champion(vm->player2, champions->champion2,
        vm, champions) == 84)
        return NULL;
    if (parse_champion(vm->player3, champions->champion3, vm,
        champions) == 84)
        return NULL;
    if (parse_champion(vm->player4, champions->champion4, vm,
        champions) == 84)
        return NULL;
    return champions;
}

static int count_player(vm_t *vm, champions_t *champions)
{
    int count = 0;

    if (!champions)
        return 0;
    if (vm->player1 && champions->champion1)
        count++;
    if (vm->player2 && champions->champion2)
        count++;
    if (vm->player3 && champions->champion3)
        count++;
    if (vm->player4 && champions->champion4)
        count++;
    return count > 0 ? count : 0;
}

int main(int argc, char **argv)
{
    vm_t *vm = NULL;
    champions_t *champions = NULL;

    if (argc > 1 && my_strcmp(argv[1], "-h") == 0 && argc == 2) {
        handle_flagh();
        return 0;
    }
    vm = parse_argument(argv);
    if (vm == NULL || handle_vm(vm, argc) == 84)
        return 84;
    display_info(vm, champions, 0);
    champions = parse_champions(vm);
    display_info(vm, champions, 1);
    vm->nb_player = count_player(vm, champions);
    load_champions(vm, champions);
    if (run_battle(vm))
        return 84;
    free_struct(vm, champions);
    return 0;
}

/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** parse .cor files
*/

#include <stdio.h>
#include <stdint.h>
#include "project.h"

uint32_t swap_uint32(uint32_t val)
{
    return ((val >> 24) & 0x000000FF) |
        ((val >> 8) & 0x0000FF00) |
        ((val << 8) & 0x00FF0000) |
        ((val << 24) & 0xFF000000);
}

static int check_magic_number(FILE *file)
{
    uint32_t magic;

    if (fread(&magic, sizeof(uint32_t), 1, file) != 1)
        return 84;
    magic = swap_uint32(magic);
    if (magic != COREWAR_EXEC_MAGIC)
        return 84;
    return 0;
}

static int read_champion(FILE *file, robot_t *robot)
{
    uint32_t size = 0;

    if (fread(robot->name, 1, PROG_NAME_LENGTH, file) != PROG_NAME_LENGTH)
        return 84;
    robot->name[PROG_NAME_LENGTH] = '\0';
    if (fseek(file, 4, SEEK_CUR) != 0)
        return 84;
    if (fread(&size, sizeof(uint32_t), 1, file) != 1)
        return 84;
    robot->code_size = swap_uint32(size);
    if (robot->code_size > CHAMP_MAX_SIZE)
        return 84;
    if (fread(robot->comment, 1, COMMENT_LENGTH, file) != COMMENT_LENGTH)
        return 84;
    robot->comment[COMMENT_LENGTH] = '\0';
    if (fseek(file, 4, SEEK_CUR) != 0)
        return 84;
    if (fread(robot->code, 1, robot->code_size, file) != robot->code_size)
        return 84;
    return 0;
}

int parse_cor_file(const char *filename, robot_t *robot)
{
    FILE *file = fopen(filename, "rb");

    if (!file)
        return 84;
    if (check_magic_number(file) == 84 ||
        read_champion(file, robot) == 84) {
        fclose(file);
        return 84;
    }
    fclose(file);
    return 0;
}

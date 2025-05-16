/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-corewar-lucas.lhomme
** File description:
** printf_off_set
*/

#include <stdarg.h>
#include "project.h"

void print_mem16(int value)
{
    char *base = "0123456789abcdef";
    char result[3];

    result[0] = base[(value / 16) % 16];
    result[1] = base[value % 16];
    result[2] = '\0';
    my_putstr(result);
    my_putchar(' ');
}

void print_memory_hex_16(unsigned char *data, size_t size)
{
    const size_t BYTES_PER_LINE = 16;

    for (size_t i = 0; i < size; i += BYTES_PER_LINE) {
        print_address_hex(i);
        for (size_t j = 0; j < BYTES_PER_LINE && (i + j) < size; j++) {
            print_mem16(data[i + j]);
        }
        my_putchar('\n');
    }
}
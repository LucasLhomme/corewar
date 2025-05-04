/*
** EPITECH PROJECT, 2024
** flag_s
** File description:
** display string
*/

#include "my.h"

void flag_s(va_list list)
{
    char *str = va_arg(list, char *);

    my_putstr(str);
}

/*
** EPITECH PROJECT, 2025
** lib
** File description:
** my_strchr
*/

#include "my.h"

char *my_strchr(const char *str, char c)
{
    while (*str) {
        if (*str == c) {
            return (char *)str;
        }
        str++;
    }
    return NULL;
}

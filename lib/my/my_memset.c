/*
** EPITECH PROJECT, 2024
** B-CPE-200-LIL-2-1-amazed-jawed.lahrouri
** File description:
** my_memset.c
*/

#include <string.h>

void *my_memset(void *s, int c, size_t n)
{
    size_t i = 0;
    unsigned char *ptr = s;

    while (i < n) {
        ptr[i] = (unsigned char)c;
        i++;
    }
    return s;
}

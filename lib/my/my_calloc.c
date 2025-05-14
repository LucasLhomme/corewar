/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-corewar-lucas.lhomme
** File description:
** my_calloc
*/

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "my.h"

void *my_calloc(size_t nitems, size_t size)
{
    void *ptr = malloc(nitems * size);

    if (size > 0 && nitems > SIZE_MAX / size)
        return NULL;
    if (ptr == NULL)
        return NULL;
    my_memset(ptr, 0, nitems * size);
    return ptr;
}

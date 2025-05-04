/*
** EPITECH PROJECT, 2025
** lib
** File description:
** free_array
*/

#include "my.h"

void free_array(char **tab)
{
    for (int i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
}

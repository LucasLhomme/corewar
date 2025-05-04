/*
** EPITECH PROJECT, 2025
** lib
** File description:
** my copy word in array
*/

#include "my.h"

char **my_copy_word_in_array(char **tab)
{
    int len = 0;
    char **new_tab = NULL;
    int i = 0;

    if (!tab)
        return NULL;
    for (int j = 0; tab[j] != NULL; j++)
        len++;
    new_tab = malloc(sizeof(char *) * (len + 1));
    if (!new_tab)
        return NULL;
    for (; i != len; i++)
        new_tab[i] = my_strdup(tab[i]);
    new_tab[i] = NULL;
    return new_tab;
}

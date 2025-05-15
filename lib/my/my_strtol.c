/*
** EPITECH PROJECT, 2025
** lib
** File description:
** strtol lib c function
*/

long int my_strtol(char *str)
{
    long int result = 0;
    int sign = 1;

    while (*str == ' ' || *str == '\t' || *str == '\n' ||
        *str == '\v' || *str == '\f' || *str == '\r')
        str++;
    if (*str == '-' || *str == '+') {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return (result * sign);
}

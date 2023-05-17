/*
** EPITECH PROJECT, 2023
** theplazza
** File description:
** main
*/

#include "restaurant.hpp"

int main(int ac, char const *av[])
{
    Restaurant client;

    if (client.plazza_restaurant(av) == 84)
        return 84;
    return 0;
}

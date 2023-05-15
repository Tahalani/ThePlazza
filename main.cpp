/*
** EPITECH PROJECT, 2023
** theplazza
** File description:
** main
*/

#include "parsing/parsing.hpp"
#include "client/client.hpp"

int main(int ac, char **av)
{
    Parsing input;
    Client client;

    if (input.getArguments(ac, av) == -1)
        return 84;
    client.takeOrder();

    return 0;
}

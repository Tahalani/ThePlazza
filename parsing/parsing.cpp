/*
** EPITECH PROJECT, 2023
** theplazza
** File description:
** Parsing
*/

#include "parsing.hpp"
#include <csignal>

int Parsing::getArguments(int ac, char **av)
{
    if (ac != 4) {
        std::cerr << "Usage: ./plazza [multiplier] [cooks] [time]" << std::endl;
        return (-1);
    }
    if (std::stoi(av[1]) <= 0 || std::stoi(av[2]) <= 0 || std::stoi(av[3]) <= 0) {
        std::cerr << "Error: arguments must be positive" << std::endl;
        return (-1);
    }
    _cocking_time = std::stoi(av[1]);
    _nb_cooks = std::stoi(av[2]);
    _time = std::stoi(av[3]);
    return (0);
}

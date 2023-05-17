/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-taha.alani
** File description:
** restaurant
*/

#include "Restaurant.hpp"
#include "client/client.hpp"

int Restaurant::getArguments(int ac, const char *av[])
{
    if (ac != 4) {
        std::cerr << "Usage: ./plazza [multiplier] [cooks] [time]" << std::endl;
        return -1;
    }
    if (std::stoi(av[1]) <= 0 || std::stoi(av[2]) <= 0 || std::stoi(av[3]) <= 0) {
        std::cerr << "Error: arguments must be positive" << std::endl;
        return -1;
    }
    _cocking_time = std::stoi(av[1]);
    _nb_cooks = std::stoi(av[2]);
    _time = std::stoi(av[3]);
    return (0);
}

int Restaurant::plazza_restaurant(const char *av[])
{
    if (getArguments(4, av) == -1)
        return 84;
    return 0;
}

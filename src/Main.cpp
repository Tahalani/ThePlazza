/*
** EPITECH PROJECT, 2023
** theplazza
** File description:
** main
*/

#include <iostream>
#include "Configuration.hpp"
#include "Reception.hpp"

int main(int argc, char const *argv[])
{
    try {
        plazza::Configuration config(argc, argv);
        plazza::Reception reception(config);
        reception.run();
    } catch (plazza::ConfigurationException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}

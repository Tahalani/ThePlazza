/*
** EPITECH PROJECT, 2023
** theplazza
** File description:
** main
*/

#include "Configuration.hpp"
#include "kitchen/Kitchen.hpp"

#include <iostream>
#include <thread>

int main(int argc, char const *argv[])
{
    try {
        plazza::Configuration config(argc, argv);
        Kitchen kitchen(config);
    } catch (plazza::ConfigurationException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}

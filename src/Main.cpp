/*
** EPITECH PROJECT, 2023
** theplazza
** File description:
** main
*/

#include <iostream>
#include "Configuration.hpp"
#include "kitchen/Kitchen.hpp"
#include "Reception.hpp"


int main(int argc, char const *argv[])
{
    try {
        plazza::Configuration config(argc, argv);
        plazza::Reception reception;
        plazza::Kitchen kitchen(config);
        kitchen.algorithmKitchen(nullptr);
        for (auto &thread : kitchen._threads) {
            thread.join();
        }
        // reception.run();
    } catch (plazza::ConfigurationException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}

/*
** EPITECH PROJECT, 2023
** theplazza
** File description:
** main
*/

#include <iostream>
#include "Configuration.hpp"
#include "Reception.hpp"

int main(int argc, char const *argv[]) {
    try {
        plazza::Configuration config(argc, argv);
        plazza::Reception reception(config);
        reception.run();
    } catch (plazza::ConfigurationException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (plazza::LoggerException &e) {
        std::cerr << "Logging is unavailable" << std::endl;
        return 84;
    }
    return 0;
}

bool operator ==(const plazza::Pizza &a, const plazza::Pizza &b) {
    return (a.type == b.type && a.size == b.size);
}

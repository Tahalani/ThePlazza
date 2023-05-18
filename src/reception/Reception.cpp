/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** Reception.cpp
*/

#include "Reception.hpp"

plazza::Reception::Reception(): _shell() {

}

void plazza::Reception::run() {
    bool exit = false;

    while (!exit) {
        try {
            std::vector<PizzaCommand> command = this->_shell.getNextOrder();
            this->executeOrder(command);
        } catch (plazza::InputException &e) {
            exit = true;
        }
    }
}

void plazza::Reception::executeOrder(const std::vector<PizzaCommand> &order) {

}

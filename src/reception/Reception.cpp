/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** Reception.cpp
*/

#include <iostream>
#include <unistd.h>
#include "Communication.hpp"
#include "Kitchen.hpp"
#include "Reception.hpp"

plazza::Reception::Reception(const Configuration &config): _config(config) {

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

void plazza::Reception::createKitchen() {
    pid_t pid = fork();

    if (pid == -1) {
        throw CommunicationException("Error while creating kitchen: fork() failed");
    } else if (pid == 0) {
        new Kitchen(this->_config);
    } else {
        this->_kitchens.push_back(pid);
    }
}

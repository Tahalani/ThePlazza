/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** Reception.cpp
*/

#include <iostream>
#include <unistd.h>
#include "util/Communication.hpp"
#include "Kitchen.hpp"
#include "Reception.hpp"

plazza::Reception::Reception(const Configuration &config): _shell(config.getPizzaRecipes()), _config(config), _ipc(getpid()), _receptionIPC(config, this->_ipc), _nextOrderId(1) {
    std::cout << "Reception ctor" << std::endl;
}

plazza::Reception::~Reception() {
    std::cout << "Reception dtor" << std::endl;
}

void plazza::Reception::run() {
    bool exit = false;

    while (!exit) {
        try {
            std::optional<std::vector<PizzaCommand>> command = this->_shell.getNextOrder();
            if (!command.has_value()) {
                // TODO: status
                continue;
            }
            PizzaOrder &order = this->registerOrder(command.value());
            //this->logOrderReceived(order.getId());
            this->executeOrder(order);
        } catch (plazza::InputException &e) {
            exit = true;
        } catch (plazza::CommandException &e) {
            std::cerr << e.what() << std::endl;
        } catch (plazza::CommunicationException &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

plazza::PizzaOrder &plazza::Reception::registerOrder(const std::vector<PizzaCommand> &command) {
    PizzaOrder &order = this->_orders.emplace_back(command, this->_nextOrderId);
    this->_nextOrderId++;
    return order;
}

void plazza::Reception::executeOrder(const PizzaOrder &order) {
    for (auto &pizza : order.getPizzasToDeliver()) {
        this->_ipc << getpid() << pizza;
    }
}

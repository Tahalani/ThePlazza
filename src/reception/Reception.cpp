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

plazza::Reception::Reception(const Configuration &config): _config(config), _nextId(1) {

}

void plazza::Reception::run() {
    bool exit = false;
    char exitType = static_cast<char>(plazza::MessageType::EXIT);

    while (!exit) {
        try {
            std::vector<PizzaCommand> command = this->_shell.getNextOrder();
            PizzaOrder &order = this->registerOrder(command);
            this->logOrderReceived(order.getId());
            this->executeOrder(order);
        } catch (plazza::InputException &e) {
            exit = true;
        }
    }
    for (auto &kitchen : this->_kitchens) {
        this->sendMessage<char>(exitType, kitchen);
    }
}

plazza::PizzaOrder &plazza::Reception::registerOrder(const std::vector<PizzaCommand> &command) {
    PizzaOrder &order = this->_orders.emplace_back(command, this->_nextId);
    this->_nextId++;
    return order;
}

void plazza::Reception::executeOrder(const PizzaOrder &order) {
    bool taken = false;

    for (auto &pizza : order.getPizzasToDeliver()) {
        taken = false;
        for (auto &kitchen : this->_kitchens) {
            if (taken)
                break;
            this->sendMessage(pizza, kitchen);
            taken = this->waitForKitchenResponse(kitchen);
        }
        if (!taken) {
            this->createKitchen();
            this->sendMessage(pizza, this->_kitchens.back());
            this->waitForKitchenResponse(this->_kitchens.back());
        }
    }
}

void plazza::Reception::messageHandler(plazza::MessageType type) {
    pid_t pid = 0;
    Pizza pizza{};

    switch (type) {
        case plazza::MessageType::EXIT:
            pid = this->receiveMessage<pid_t>();
            for (auto it = this->_kitchens.begin(); it != this->_kitchens.end(); ++it) {
                if (*it == pid) {
                    this->_kitchens.erase(it);
                    break;
                }
            }
            this->_logger.log("Kitchen with pid " + std::to_string(pid) + " closed");
            break;

        case plazza::MessageType::PIZZA:
            pizza = this->receiveMessage<Pizza>();
            // TODO: Pizza received
            break;

        default:
            throw CommunicationException("Unknown message type");
    }
}


bool plazza::Reception::waitForKitchenResponse(pid_t pid) {
    char message = this->receiveMessage<char>();
    auto type = static_cast<plazza::MessageType>(message);

    if (type == plazza::MessageType::PIZZA_RESPONSE) {
        return this->receiveMessage<bool>();
    } else {
        this->messageHandler(type);
        return this->waitForKitchenResponse(pid);
    }
}

void plazza::Reception::createKitchen() {
    pid_t pid = fork();

    if (pid == -1) {
        throw CommunicationException("Error while creating kitchen: fork() failed");
    }
    if (pid == 0) {
        new Kitchen(this->_config);
    } else {
        this->_logger.log("New kitchen opened with pid " + std::to_string(pid));
        this->_kitchens.push_back(pid);
    }
}

void plazza::Reception::logOrderReceived(size_t id) {
    std::cout << "Order #" << id << " started!" << std::endl;
    this->_logger.log("Order #" + std::to_string(id) + " started!");
}

void plazza::Reception::logOrderReady(size_t id) {
    std::cout << "Order #" << id << " is ready!" << std::endl;
    this->_logger.log("Order #" + std::to_string(id) + " is ready!");
}

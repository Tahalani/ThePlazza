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

plazza::Reception::Reception(const Configuration &config): _config(config), _nextOrderId(1), _nextKitchenId(1) {

}

void plazza::Reception::run() {
    bool exit = false;

    while (!exit) {
        try {
            std::vector<PizzaCommand> command = this->_shell.getNextOrder();
            PizzaOrder &order = this->registerOrder(command);
            this->logOrderReceived(order.getId());
            this->executeOrder(order);
        } catch (plazza::InputException &e) {
            exit = true;
        } catch (plazza::CommandException &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    for (auto &kitchen : this->_kitchens) {
        this->_ipc.sendMessageRaw(MessageType::EXIT, kitchen);
    }
}

plazza::PizzaOrder &plazza::Reception::registerOrder(const std::vector<PizzaCommand> &command) {
    PizzaOrder &order = this->_orders.emplace_back(command, this->_nextOrderId);
    this->_nextOrderId++;
    return order;
}

void plazza::Reception::executeOrder(const PizzaOrder &order) {
    bool taken = false;

    for (auto &pizza : order.getPizzasToDeliver()) {
        taken = false;
        for (auto &kitchen : this->_kitchens) {
            if (taken)
                break;
            this->_ipc.sendMessage(pizza, kitchen);
            taken = this->waitForKitchenResponse(kitchen);
        }
        if (!taken) {
            this->createKitchen(pizza);
        }
    }
}

void plazza::Reception::messageHandler(plazza::MessageType type) {
    pid_t pid = 0;
    Pizza pizza{};

    switch (type) {
        case plazza::MessageType::EXIT:
            pid = this->_ipc.receiveMessage<pid_t>();
            for (auto it = this->_kitchens.begin(); it != this->_kitchens.end(); ++it) {
                if (*it == pid) {
                    this->_kitchens.erase(it);
                    break;
                }
            }
            this->_logger.log("Kitchen with pid " + std::to_string(pid) + " closed");
            break;

        case plazza::MessageType::PIZZA:
            pizza = this->_ipc.receiveMessage<Pizza>();
            for (auto &order : this->_orders) {
                if (order.pizzaReceived(pizza)) {
                    if (order.isOrderReady()) {
                        this->logOrderReady(order.getId());
                    }
                    break;
                }
            }
            break;

        default:
            throw CommunicationException("Unknown message type");
    }
}


bool plazza::Reception::waitForKitchenResponse(pid_t pid) {
    auto message = this->_ipc.receiveMessage<MessageType>();

    if (message == plazza::MessageType::PIZZA_RESPONSE) {
        return this->_ipc.receiveMessage<bool>();
    } else {
        this->messageHandler(message);
        return this->waitForKitchenResponse(pid);
    }
}

void plazza::Reception::createKitchen(const Pizza &pizza) {
    pid_t pid = fork();

    if (pid == -1) {
        throw CommunicationException("Error while creating kitchen: fork() failed");
    }
    if (pid == 0) {
        Kitchen(this->_nextKitchenId, this->_config, this->_ipc, pizza);
    } else {
        this->_logger.log("New kitchen opened with pid " + std::to_string(pid));
        this->_kitchens.push_back(pid);
        this->_nextKitchenId++;
    }
}

void plazza::Reception::logOrderReceived(size_t id) {
    std::cout << "Reception: Order #" << id << " started!" << std::endl;
    this->_logger.log("Order #" + std::to_string(id) + " started!");
}

void plazza::Reception::logOrderReady(size_t id) {
    std::cout << "Reception: Order #" << id << " is ready!" << std::endl;
    this->_logger.log("Order #" + std::to_string(id) + " is ready!");
}

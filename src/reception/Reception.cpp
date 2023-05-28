/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** Reception.cpp
*/

#include <iostream>
#include <unistd.h>
#include "Reception.hpp"

plazza::Reception::Reception(const Configuration &config): _shell(config.getPizzaRecipes()), _config(config), _ipc(getpid()), _nextOrderId(1), _nextKitchenId(1),  _thread(std::thread(&Reception::ipcRoutine, this, getpid())) {
    this->_logger >> "Reception is now open";
}

plazza::Reception::~Reception() {
    this->_ipc << getpid() << MessageType::EXIT;
    if (this->_thread.joinable()) {
        this->_thread.join();
    }
    this->_logger >> "Reception is now closed";
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
            this->_logger << "Order #" + std::to_string(order.getId()) + " registered";
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

void plazza::Reception::ipcRoutine(pid_t parentPid) {
    bool exit = false;

    while (!exit) {
        Message<MessageType> type = this->_ipc.getNextMessage();

        switch (type.data) {
            case MessageType::EXIT:
                exit = this->exitHandler(parentPid, type.sender);
                break;
            case MessageType::STATUS:
                // TODO: Status
                break;
            case MessageType::PIZZA:
                this->pizzaHandler(parentPid, type.sender);
                break;
        }
    }
}

bool plazza::Reception::exitHandler(pid_t parentPid, pid_t senderPid) {
    if (senderPid == parentPid) {
        return true;
    }
    for (auto it = this->_kitchens.begin(); it != this->_kitchens.end(); it++) {
        if (it->getKitchenPid() == senderPid) {
            this->_kitchens.erase(it);
            return false;
        }
    }
    return false;
}

void plazza::Reception::pizzaHandler(pid_t parentPid, pid_t senderPid) {
    Pizza pizza;
    this->_ipc >> pizza;

    if (senderPid == parentPid) {
        if (this->_kitchens.empty()) {
            this->createKitchen(pizza);
        } else {
            this->_ipc << this->_kitchens[0].getKitchenPid() << pizza;
        }
        return;
    } else if (pizza.cooked) {
        for (auto it = this->_orders.begin(); it != this->_orders.end(); it++) {
            if (it->pizzaReceived(pizza)) {
                if (it->isOrderReady()) {
                    this->_logger << "Order #" + std::to_string(it->getId()) + " is ready";
                    this->_orders.erase(it);
                }
                return;
            }
        }
        return;
    }
    for (auto it = this->_kitchens.begin(); it != this->_kitchens.end(); it++) {
        if (it->getKitchenPid() == senderPid) {
            auto next = ++it;
            if (next == this->_kitchens.end()) {
                this->createKitchen(pizza);
            } else {
                this->_ipc << next->getKitchenPid() << pizza;
            }
            return;
        }
    }
}

void plazza::Reception::createKitchen(const plazza::Pizza &firstPizza) {
    this->_kitchens.emplace_back(this->_nextKitchenId, this->_config, this->_ipc);
    this->_kitchens[this->_kitchens.size() - 1].openKitchen(firstPizza);
    this->_nextKitchenId++;

    size_t id = this->_kitchens[this->_kitchens.size() - 1].getId();
    this->_logger << "Kitchen #" + std::to_string(id) + " created";
}

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

plazza::Reception::Reception(const Configuration &config): _config(config), _ipc(config), _nextOrderId(1) {

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
            this->logOrderReceived(order.getId());
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
        this->_ipc.sendPizza(pizza, getpid());
    }
}

void plazza::Reception::messageHandler(plazza::MessageType type) {
    Pizza pizza{};

    switch (type) {
        case plazza::MessageType::PIZZA:
            //pizza = this->_ipc.receiveMessage<Pizza>();
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
    /*auto message = this->_ipc.receiveMessage<MessageType>();

    if (message == plazza::MessageType::PIZZA_RESPONSE) {
        return this->_ipc.receiveMessage<bool>();
    } else {
        this->messageHandler(message);
        return this->waitForKitchenResponse(pid);
    }*/
    return true;
}

void plazza::Reception::createKitchen(const Pizza &pizza) {
    pid_t pid = fork();

    if (pid == -1) {
        throw CommunicationException("Error while creating kitchen: fork() failed");
    }
    if (pid == 0) {
        //Kitchen(this->_nextKitchenId, this->_config, this->_ipc, pizza);
    } else {
        this->_logger.log("New kitchen opened with pid " + std::to_string(pid));
        //this->_nextKitchenId++;
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

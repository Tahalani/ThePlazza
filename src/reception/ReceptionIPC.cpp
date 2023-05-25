/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** ReceptionIPC.cpp
*/

#include <iostream>
#include "PizzaData.hpp"
#include "ReceptionIPC.hpp"

plazza::ReceptionIPC::ReceptionIPC(const Configuration &config) : _thread(std::thread(&ReceptionIPC::ipcRoutine, this, getpid())), _config(config), _nextKitchenId(1) {

}

plazza::ReceptionIPC::~ReceptionIPC() {
    this->sendMessage(MessageType::EXIT, getpid());
    if (this->_thread.joinable()) {
        this->_thread.join();
    }
}

void plazza::ReceptionIPC::sendPizza(const Pizza &pizza, long target) {
    this->sendMessage(MessageType::PIZZA, target);
    this->sendMessage(pizza, target);
}

void plazza::ReceptionIPC::ipcRoutine(pid_t parentPid) {
    bool exit = false;

    while (!exit) {
        Message<MessageType> type = this->receiveMessage<MessageType>();

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

bool plazza::ReceptionIPC::exitHandler(pid_t parentPid, pid_t senderPid) {
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

void plazza::ReceptionIPC::pizzaHandler(pid_t parentPid, pid_t senderPid) {
    Message<Pizza> pizza = this->receiveMessage<Pizza>();

    if (senderPid == parentPid) {
        if (this->_kitchens.empty()) {
            this->createKitchen(pizza.data);
        } else {
            this->sendPizza(pizza.data, this->_kitchens[0].getKitchenPid());
        }
        return;
    }
    for (auto it = this->_kitchens.begin(); it != this->_kitchens.end(); it++) {
        if (it->getKitchenPid() == senderPid) {
            auto next = ++it;
            if (next == this->_kitchens.end()) {
                this->createKitchen(pizza.data);
            } else {
                this->sendPizza(pizza.data, next->getKitchenPid());
            }
            return;
        }
    }
}

void plazza::ReceptionIPC::createKitchen(const plazza::Pizza &firstPizza) {
    Kitchen kitchen = this->_kitchens.emplace_back(this->_nextKitchenId,this->_config,*static_cast<Communication *>(this));
    kitchen.openKitchen(firstPizza);
    this->_nextKitchenId++;
    // TODO: Log kitchen creation
}

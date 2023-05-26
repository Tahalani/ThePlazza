/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** ReceptionIPC.cpp
*/

#include <iostream>
#include "PizzaData.hpp"
#include "ReceptionIPC.hpp"

plazza::ReceptionIPC::ReceptionIPC(const Configuration &config, const PlazzaIPC &ipc) : _config(config), _ipc(ipc), _thread(std::thread(&ReceptionIPC::ipcRoutine, this, getpid())), _nextKitchenId(1) {
    std::cout << "ReceptionIPC ctor" << std::endl;
}

plazza::ReceptionIPC::~ReceptionIPC() {
    this->_ipc << getpid() << MessageType::EXIT;
    if (this->_thread.joinable()) {
        this->_thread.join();
    }
    std::cout << "ReceptionIPC dtor" << std::endl;
}

void plazza::ReceptionIPC::ipcRoutine(pid_t parentPid) {
    std::cout << "ReceptionIPC thread start" << std::endl;
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
    std::cout << "ReceptionIPC thread end" << std::endl;
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
    Pizza pizza;
    this->_ipc >> pizza;

    if (senderPid == parentPid) {
        if (this->_kitchens.empty()) {
            this->createKitchen(pizza);
        } else {
            this->_ipc << this->_kitchens[0].getKitchenPid() << MessageType::PIZZA;
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

void plazza::ReceptionIPC::createKitchen(const plazza::Pizza &firstPizza) {
    this->_kitchens.emplace_back(this->_nextKitchenId, this->_config, this->_ipc);
    this->_kitchens[this->_kitchens.size() - 1].openKitchen(firstPizza);
    this->_nextKitchenId++;
    // TODO: Log kitchen creation
}

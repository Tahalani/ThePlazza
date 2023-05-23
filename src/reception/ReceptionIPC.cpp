/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** ReceptionIPC.cpp
*/

#include <iostream>
#include "PizzaData.hpp"
#include "ReceptionIPC.hpp"

plazza::ReceptionIPC::ReceptionIPC() : _thread(std::thread(&ReceptionIPC::ipcRoutine, this, getpid())) {

}

plazza::ReceptionIPC::~ReceptionIPC() {
    this->sendMessage(MessageType::EXIT, getpid());
    this->_thread.join();
}

void plazza::ReceptionIPC::ipcRoutine(pid_t parentPid) {
    bool exit = false;

    while (!exit) {
        Message<MessageType> type = this->receiveMessage<MessageType>();

        switch (type.data) {
            case MessageType::EXIT:
                exit = this->exitHandler(parentPid, type.sender);
                break;
            case MessageType::PIZZA:
                this->pizzaHandler();
                break;
            case MessageType::PIZZA_RESPONSE:

                break;
        }
    }
}

bool plazza::ReceptionIPC::exitHandler(pid_t parentPid, pid_t senderPid) {
    if (senderPid == parentPid) {
        return true;
    }
    for (auto it = this->_kitchens.begin(); it != this->_kitchens.end(); it++) {
        
    }
    return false;
}

void plazza::ReceptionIPC::pizzaHandler() {

}

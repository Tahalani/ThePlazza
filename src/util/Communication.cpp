/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** Communication.cpp
*/

#include <sys/ipc.h>
#include <sys/msg.h>
#include "Communication.hpp"

plazza::CommunicationException::CommunicationException(std::string message): _message(std::move(message)) {

}

const char *plazza::CommunicationException::what() const noexcept {
    return this->_message.c_str();
}

plazza::Communication::Communication() {
    this->_key = IPC_PRIVATE;
    this->_queue_id = msgget(this->_key, IPC_CREAT | 0666);
    if (this->_queue_id == -1) {
        throw CommunicationException("msgget failed");
    }
}

plazza::Communication::~Communication() {
    std::cout << "rmid" << std::endl;
    msgctl(this->_queue_id, IPC_RMID, nullptr);
}

/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** PlazzaIPC.cpp
*/

#include <cstring>
#include "PlazzaIPC.hpp"

plazza::PlazzaIPC::PlazzaIPC(pid_t receiver): _receiver(receiver) {

}

plazza::PlazzaIPC &plazza::PlazzaIPC::operator<<(pid_t receiver) {
    this->_receiver = receiver;
    return *this;
}

plazza::PlazzaIPC &plazza::PlazzaIPC::operator<<(const plazza::MessageType &type) {
    this->sendMessage(type, this->_receiver);
    return *this;
}

plazza::PlazzaIPC &plazza::PlazzaIPC::operator<<(const plazza::Pizza &pizza) {
    this->sendMessage(MessageType::PIZZA, this->_receiver);
    this->sendMessage(this->pack(pizza), this->_receiver);
    return *this;
}

void plazza::PlazzaIPC::operator>>(plazza::Pizza &pizza) {
    Message<ParsedPizza> message = this->receiveMessage<ParsedPizza>();
    Pizza tmp = this->unpack(message.data);

    pizza.type = std::move(tmp.type);
    pizza.size = tmp.size;
    pizza.cooked = tmp.cooked;
}

plazza::Message<plazza::MessageType> plazza::PlazzaIPC::getNextMessage() {
    return this->receiveMessage<MessageType>();
}

#include <iostream>
plazza::ParsedPizza plazza::PlazzaIPC::pack(const plazza::Pizza &pizza) {
    ParsedPizza packed{};

    std::cout << "Pizza is " << pizza.type << "/" << (int) pizza.size << "/" << pizza.cooked << std::endl;
    strcpy(packed.type, pizza.type.c_str());
    packed.size = pizza.size;
    packed.cooked = pizza.cooked;
    return packed;
}

plazza::Pizza plazza::PlazzaIPC::unpack(const plazza::ParsedPizza &pizza) {
    Pizza unpacked{};

    unpacked.type = pizza.type;
    unpacked.size = pizza.size;
    unpacked.cooked = pizza.cooked;
    return unpacked;
}

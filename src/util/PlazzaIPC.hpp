/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** PlazzaIPC.hpp
<*/

#ifndef PLAZZAIPC_HPP
#define PLAZZAIPC_HPP

#include "Communication.hpp"
#include "PizzaData.hpp"

namespace plazza {
    struct MessageContent {
        MessageType messageType;
        char type[PIZZA_SIZE];
        PizzaSize size;
        bool cooked;
    };

    class PlazzaIPC : Communication {
        public:
            explicit PlazzaIPC(pid_t receiver);

            PlazzaIPC &operator<<(pid_t receiver);
            PlazzaIPC &operator<<(const MessageType &type);
            PlazzaIPC &operator<<(const Pizza &pizza);
            void operator>>(Pizza &pizza);

            Message<MessageContent> getNextMessage();
            Pizza unpack(const MessageContent &pizza);

        private:
            MessageContent pack(const Pizza &pizza);
            pid_t _receiver;
    };
}

#endif

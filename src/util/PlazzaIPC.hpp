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
    struct ParsedPizza {
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

            Message<MessageType> getNextMessage();

        private:
            ParsedPizza pack(const Pizza &pizza);
            Pizza unpack(const ParsedPizza &pizza);

            pid_t _receiver;
    };
}

#endif

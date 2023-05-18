/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** Reception.hpp
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include "Shell.hpp"

namespace plazza {
    class Reception {
        public:
            Reception();
            ~Reception() = default;

            void run();

        private:
            void executeOrder(const std::vector<PizzaCommand> &order);
            Shell _shell;
    };
}

#endif
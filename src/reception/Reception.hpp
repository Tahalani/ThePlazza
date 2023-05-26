/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** Reception.hpp
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include "Communication.hpp"
#include "Logger.hpp"
#include "PizzaOrder.hpp"
#include "ReceptionIPC.hpp"
#include "Shell.hpp"

namespace plazza {
    class Reception {
        public:
            explicit Reception(const Configuration &config);

            void run();

        private:
            PizzaOrder &registerOrder(const std::vector<PizzaCommand> &command);
            void executeOrder(const PizzaOrder &order);

            Shell _shell;
            Configuration _config;
            PlazzaIPC _ipc;
            ReceptionIPC _receptionIPC;
            Logger _logger;
            std::vector<PizzaOrder> _orders;
            size_t _nextOrderId;
    };
}

#endif
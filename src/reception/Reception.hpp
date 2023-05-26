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
            void createKitchen(const Pizza &pizza);
            void logOrderReceived(size_t id);
            void logOrderReady(size_t id);
            void messageHandler(MessageType type);
            bool waitForKitchenResponse(pid_t pid);

            Shell _shell;
            Configuration _config;
            ReceptionIPC _ipc;
            Logger _logger;
            std::vector<PizzaOrder> _orders;
            size_t _nextOrderId;
    };
}

#endif
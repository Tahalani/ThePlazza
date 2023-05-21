/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** Reception.hpp
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include "Configuration.hpp"
#include "util/Communication.hpp"
#include "util/Logger.hpp"
#include "PizzaOrder.hpp"
#include "Shell.hpp"

namespace plazza {
    class Reception : Communication {
        public:
            explicit Reception(const Configuration &config);

            void run();

        private:
            PizzaOrder &registerOrder(const std::vector<PizzaCommand> &command);
            void executeOrder(const PizzaOrder &order);
            void createKitchen();
            void logOrderReceived(size_t id);
            void logOrderReady(size_t id);
            void messageHandler(MessageType type);
            bool waitForKitchenResponse(pid_t pid);

            Shell _shell;
            Configuration _config;
            Logger _logger;
            std::vector<PizzaOrder> _orders;
            std::vector<pid_t> _kitchens;
            size_t _nextId;
    };
}

#endif
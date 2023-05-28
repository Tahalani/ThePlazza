/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** Reception.hpp
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include <thread>
#include "Kitchen.hpp"
#include "Logger.hpp"
#include "PizzaOrder.hpp"
#include "PlazzaIPC.hpp"
#include "Shell.hpp"

namespace plazza {
    class Reception {
        public:
            explicit Reception(const Configuration &config);
            ~Reception();

            void run();

        private:
            PizzaOrder &registerOrder(const std::vector<PizzaCommand> &command);
            void executeOrder(const PizzaOrder &order);
            void ipcRoutine(pid_t parentPid);
            bool exitHandler(pid_t parentPid, pid_t senderPid);
            void pizzaHandler(pid_t parentPid, pid_t senderPid);
            void createKitchen(const Pizza &firstPizza);
            void showStatus();

            Configuration _config;
            std::shared_ptr<PlazzaIPC> _ipc;
            std::shared_ptr<Logger> _logger;
            Shell _shell;
            std::vector<PizzaOrder> _orders;
            std::vector<std::shared_ptr<Kitchen>> _kitchens;
            size_t _nextOrderId;
            size_t _nextKitchenId;
            std::thread _thread;
    };
}

#endif
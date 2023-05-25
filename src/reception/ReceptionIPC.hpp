/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** ReceptionIPC.hpp
*/

#ifndef RECEPTION_IPC_HPP_
#define RECEPTION_IPC_HPP_

#include <thread>
#include <vector>
#include "Communication.hpp"
#include "Kitchen.hpp"

namespace plazza {
    class ReceptionIPC : Communication {
        public:
            explicit ReceptionIPC(const Configuration &config);
            ~ReceptionIPC();

            void sendPizza(const Pizza &pizza, long target);

        private:
            void ipcRoutine(pid_t parentPid);
            bool exitHandler(pid_t parentPid, pid_t senderPid);
            void pizzaHandler(pid_t parentPid, pid_t senderPid);
            void createKitchen(const Pizza &firstPizza);

            std::thread _thread;
            std::vector<Kitchen> _kitchens;
            Configuration _config;
            size_t _nextKitchenId;
    };
}

#endif

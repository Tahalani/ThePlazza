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
#include "PlazzaIPC.hpp"

namespace plazza {
    class ReceptionIPC {
        public:
            explicit ReceptionIPC(const Configuration &config, const PlazzaIPC &ipc);
            ~ReceptionIPC();

        private:
            void ipcRoutine(pid_t parentPid);
            bool exitHandler(pid_t parentPid, pid_t senderPid);
            void pizzaHandler(pid_t parentPid, pid_t senderPid);
            void createKitchen(const Pizza &firstPizza);

            Configuration _config;
            PlazzaIPC _ipc;
            std::thread _thread;
            std::vector<Kitchen> _kitchens;
            size_t _nextKitchenId;
    };
}

#endif

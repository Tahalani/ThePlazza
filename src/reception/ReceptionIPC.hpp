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
            ReceptionIPC();
            ~ReceptionIPC();

        private:
            void ipcRoutine(pid_t parentPid);
            bool exitHandler(pid_t parentPid, pid_t senderPid);
            void pizzaHandler();

            std::thread _thread;
            std::vector<plazza::Kitchen> _kitchens;
    };
}

#endif

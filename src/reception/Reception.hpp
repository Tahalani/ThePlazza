/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** Reception.hpp
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include "Configuration.hpp"
#include "Communication.hpp"
#include "Shell.hpp"

namespace plazza {
    class Reception {
        public:
            explicit Reception(const Configuration &config);
            ~Reception() = default;

            void run();

        private:
            void executeOrder(const std::vector<PizzaCommand> &order);
            void createKitchen();

            Shell _shell;
            Communication _ipc;
            Configuration _config;
            std::vector<pid_t> _kitchens;
    };
}

#endif
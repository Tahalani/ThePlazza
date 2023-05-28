/*
** EPITECH PROJECT, 2023
** theplazza
** File description:
** kitchen
*/

#ifndef KITCHEN_HPP_
#define KITCHEN_HPP_

#include <memory>
#include "Configuration.hpp"
#include "Logger.hpp"
#include "PizzaData.hpp"
#include "PlazzaIPC.hpp"

namespace plazza {
    class Kitchen {
        public:
            Kitchen(size_t id, plazza::Configuration &config, std::shared_ptr<PlazzaIPC> ipc, std::shared_ptr<Logger> logger);
            ~Kitchen();

            [[nodiscard]] size_t getId() const;
            [[nodiscard]] pid_t getKitchenPid() const;

            void openKitchen(const Pizza &firstPizza);

        private:
            void run(const Pizza &firstPizza);
            void log(const std::string &message);

            size_t _id;
            plazza::Configuration _config;
            std::shared_ptr<PlazzaIPC> _ipc;
            std::shared_ptr<Logger> _logger;
            pid_t _parent_pid;
            pid_t _kitchen_pid;
    };
}

#endif

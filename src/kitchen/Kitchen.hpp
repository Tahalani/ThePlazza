/*
** EPITECH PROJECT, 2023
** theplazza
** File description:
** kitchen
*/

#ifndef KITCHEN_HPP_
#define KITCHEN_HPP_

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <condition_variable>
#include <thread>
#include <queue>
#include "Configuration.hpp"
#include "PizzaData.hpp"
#include "PlazzaIPC.hpp"

namespace plazza {
    class Kitchen {
        public:
            Kitchen(size_t id, plazza::Configuration &config, const PlazzaIPC &ipc);

            pid_t getKitchenPid() const;

            void openKitchen(const Pizza &firstPizza);

        private:
            void run(const Pizza &firstPizza);

            size_t _id;
            plazza::Configuration _config;
            plazza::PlazzaIPC _ipc;
            std::vector<int> _ingredients;
            pid_t _parent_pid;
            pid_t _kitchen_pid;
    };
}

#endif

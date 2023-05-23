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
#include "Communication.hpp"
#include "Configuration.hpp"
#include "PizzaData.hpp"

namespace plazza {
    class Kitchen {
        public:
            Kitchen(size_t id, plazza::Configuration &config, const Communication &ipc);
            void openKitchen(const Pizza &firstPizza);

        private:
            void run(const Pizza &firstPizza);

            size_t _id;
            plazza::Configuration _config;
            plazza::Communication _ipc;
            std::vector<int> _ingredients;
            std::unordered_map<plazza::PizzaType, std::pair<std::unordered_map<plazza::Ingredients, int>, int>> _ingredients_per_pizza;
            std::queue<plazza::Pizza> _pizzaQueue;
            std::unique_lock<std::mutex> _kitchenLock;
            std::condition_variable _cookCondVar;
            pid_t _parent_pid;
    };
}

#endif

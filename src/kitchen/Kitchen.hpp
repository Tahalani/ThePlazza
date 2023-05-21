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
            Kitchen(size_t id, plazza::Configuration &config, const Communication &ipc, const Pizza &firstPizza);
            void kitchenRoutine(float timeMultiplier);
            void refillRoutine(int refillTime);

        private:
            void log(const std::string &message) const;

            size_t _id;
            plazza::Communication _ipc;
            std::vector<int> _ingredients;
            std::unordered_map<plazza::PizzaType, std::pair<std::unordered_map<plazza::Ingredients, int>, int>> _ingredients_per_pizza;
            std::queue<plazza::Pizza> _pizzaQueue;
            std::mutex _kitchenMutex;
            std::unique_lock<std::mutex> _kitchenLock;
            std::condition_variable _cookCondVar;
            std::vector<std::thread> _cooks;
            std::thread _refill;
            pid_t _parent_pid;
    };
}

#endif

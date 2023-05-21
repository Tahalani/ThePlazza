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

namespace plazza {
    class Kitchen {
        public:
            Kitchen(plazza::Configuration &config, const Pizza &firstPizza, size_t id);
            void kitchenRoutine(int nbr);
            void refillRoutine(plazza::Configuration conf);

        private:
            void log(const std::string &message) const;

            size_t _id;
            plazza::Configuration _config;
            std::vector<int> _ingredients;
            std::unordered_map<plazza::PizzaType, std::pair<std::unordered_map<plazza::Ingredients, int>, int>> _ingredients_per_pizza;
            std::queue<plazza::Pizza> _pizzaQueue;
            std::mutex _kitchenMutex;
            std::unique_lock<std::mutex> _kitchenLock;
            std::condition_variable _cookCondVar;
            std::vector<std::thread> _cooks;
            std::thread _refill;
    };
}

#endif

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
#include <thread>
#include <unordered_map>
#include <vector>
#include <condition_variable>

#include "Configuration.hpp"
#include "PizzaData.hpp"

namespace plazza {
    class Kitchen {
        public:
            Kitchen(plazza::Configuration &conf);
            ~Kitchen() {};
            void kitchenRoutine(int nbr);
            bool checkIngredients(plazza::PizzaCommand &command);
            void *algorithmKitchen(void *arg);

        private:
            std::vector<int> _ingredients;
            std::unordered_map<plazza::PizzaType, std::pair<std::unordered_map<plazza::Ingredients, int>, int>> _ingredients_per_pizza;
            std::vector<std::thread> _threads;
            // std::condition_variable _cond_furnace;
            // std::unique_lock<std::mutex> _mutex_reception;
            std::mutex _mutex_reception;
            std::condition_variable _cond_furnace;
            std::unique_lock<std::mutex> _lock_reception;
    };
}

#endif

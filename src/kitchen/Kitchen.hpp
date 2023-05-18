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
#include "Configuration.hpp"
#include "PizzaData.hpp"

namespace plazza {
    class Kitchen {
        public:
            Kitchen(plazza::Configuration &conf);
            ~Kitchen() {};
            void kitchenRoutine(std::string message);
            bool checkIngredients(plazza::PizzaCommand &command);
            void *algorithmKitchen(void *arg);

        private:
            std::vector<int> _ingredients;
            std::unordered_map<plazza::PizzaType, std::pair<std::unordered_map<plazza::Ingredients, int>, int>> _ingredients_per_pizza;
            std::vector<std::thread> _threads;
    };
}

#endif

/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** PizzaOrder.hpp
*/

#ifndef PIZZAORDER_HPP_
#define PIZZAORDER_HPP_

#include <vector>
#include "Logger.hpp"
#include "PizzaData.hpp"

namespace plazza {
    class PizzaOrder {
        public:
            PizzaOrder(const std::vector<PizzaCommand> &order, size_t id);

            [[nodiscard]] const std::vector<Pizza> &getPizzasToDeliver() const;
            [[nodiscard]] size_t getId() const;


            bool pizzaReceived(const Pizza &pizza);
            bool isOrderReady();
            void logOrder(Logger &logger);

        private:
            size_t getAmountReady(PizzaCommand &pizza);

            size_t _id;
            std::vector<PizzaCommand> _pizzas;
            std::vector<Pizza> _pizzasToDeliver;
    };
}

#endif
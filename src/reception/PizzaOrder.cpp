/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** PizzaOrder.cpp
*/

#include "PizzaOrder.hpp"

plazza::PizzaOrder::PizzaOrder(const std::vector<PizzaCommand> &order, size_t id): _id(id) {
    for (auto &pizza : order) {
        for (int i = 0; i < pizza.quantity; i++) {
            this->_pizzasToDeliver.emplace_back(Pizza { pizza.type, pizza.size });
        }
    }
}

const std::vector<plazza::Pizza> &plazza::PizzaOrder::getPizzasToDeliver() const {
    return this->_pizzasToDeliver;
}

size_t plazza::PizzaOrder::getId() const {
    return this->_id;
}

bool plazza::PizzaOrder::pizzaReceived(const Pizza &pizza) {
    for (auto it = this->_pizzasToDeliver.begin(); it != this->_pizzasToDeliver.end(); ++it) {
        if (pizza == *it) {
            this->_pizzasToDeliver.erase(it);
            return true;
        }
    }
    return false;
}

bool plazza::PizzaOrder::isOrderReady() {
    return this->_pizzasToDeliver.empty();
}


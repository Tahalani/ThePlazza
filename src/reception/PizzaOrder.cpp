/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** PizzaOrder.cpp
*/

#include <sstream>
#include "PizzaOrder.hpp"

plazza::PizzaOrder::PizzaOrder(const std::vector<PizzaCommand> &order, size_t id): _id(id), _pizzas(order) {
    for (auto &pizza : order) {
        for (int i = 0; i < pizza.quantity; i++) {
            this->_pizzasToDeliver.emplace_back(Pizza { pizza.type, pizza.size, false });
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

void plazza::PizzaOrder::logOrder(plazza::Logger &logger) {
    std::stringstream stream;
    stream << "Order #" << this->_id << ":" << std::endl;
    for (auto &pizza : this->_pizzas) {
        size_t left = this->getAmountReady(pizza);

        stream << "  - " <<  pizza.type << " " << *pizza.size << " x" << pizza.quantity << " (" << left << "/" << pizza.quantity << ")" << std::endl;
    }
    logger << stream.str();
}

size_t plazza::PizzaOrder::getAmountReady(plazza::PizzaCommand &pizza) {
    int left = pizza.quantity;

    for (auto &pizzaToDeliver : this->_pizzasToDeliver) {
        if (pizzaToDeliver.type == pizza.type && pizzaToDeliver.size == pizza.size) {
            left--;
        }
    }
    return left;
}

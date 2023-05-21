/*
** EPITECH PROJECT, 2023
** theplazza
** File description:
** kitchen
*/

#include <thread>
#include <mutex>
#include "Kitchen.hpp"

plazza::Kitchen::Kitchen(size_t id, Configuration &config, const Communication &ipc, const Pizza &firstPizza) : _id(id), _config(config)
{
    std::unordered_map<Ingredients, int> ReginaIngr = {
            {Ingredients::Dough, 1},
            {Ingredients::Tomato, 1},
            {Ingredients::Gruyere, 1},
            {Ingredients::Ham, 1},
            {Ingredients::Mushrooms, 1},
    };
    std::unordered_map<Ingredients, int> MargaritaIngr = {
            {Ingredients::Dough, 1},
            {Ingredients::Tomato, 1},
            {Ingredients::Gruyere, 1},
    };
    std::unordered_map<Ingredients, int> AmericanaIngr = {
            {Ingredients::Dough, 1},
            {Ingredients::Tomato, 1},
            {Ingredients::Gruyere, 1},
            {Ingredients::Steak, 1},
    };
    std::unordered_map<Ingredients, int> FantasiaIngr = {
            {Ingredients::Dough, 1},
            {Ingredients::Tomato, 1},
            {Ingredients::Eggplant, 1},
            {Ingredients::GoatCheese, 1},
            {Ingredients::ChiefLove, 1},
    };

    this->_ingredients = {5, 5, 5, 5, 5, 5, 5, 5, 5};
    this->_ingredients_per_pizza = {
            {PizzaType::Regina, {ReginaIngr, 2 * 1000}},
            {PizzaType::Margarita, {MargaritaIngr, 1 * 1000}},
            {PizzaType::Americana, {AmericanaIngr, 2 * 1000}},
            {PizzaType::Fantasia, {FantasiaIngr, 4 * 1000}},
    };

    for (int i = 0; i <= config.getCooksPerKitchen(); i++) {
        this->_cooks.emplace_back(&Kitchen::kitchenRoutine, this, i);
    }
    this->_refill = std::thread(&Kitchen::refillRoutine, this, config);
    this->_pizzaQueue.push(firstPizza);
    this->_cookCondVar.notify_one();

    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void plazza::Kitchen::kitchenRoutine(int nbr)
{
    this->log("Cook " + std::to_string(nbr) + " is ready to cook");
    std::unique_lock<std::mutex> lock(this->_kitchenMutex);

    while (true) {
        this->_cookCondVar.wait(lock);
        if (this->_pizzaQueue.empty()) {
            lock.unlock();
            return;
        }
        Pizza pizza = this->_pizzaQueue.front();
        this->_pizzaQueue.pop();
        lock.unlock();
        std::cout << "I'll cook this pizza for " << "2 seconds" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Pizza cooked" << std::endl;
    }
}

void plazza::Kitchen::refillRoutine(Configuration conf)
{
    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(conf.getRefillTime()));
        for (size_t i = 0; i < _ingredients.size(); i += 1) {
            if (_ingredients[i] < 5) {
                _ingredients[i] += 1;
                std::cout << "Refill ingredient " << std::endl;
            }
        }
    }
}

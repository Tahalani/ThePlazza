/*
** EPITECH PROJECT, 2023
** theplazza
** File description:
** kitchen
*/

#include "Kitchen.hpp"

plazza::Kitchen::Kitchen(Configuration &conf)
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

    for (int i = 0; i <= conf.getCooksPerKitchen(); i++) {
        _threads_furnace.emplace_back(&Kitchen::kitchenRoutine, this, i);
    }
    _thread_refill = std::thread(&Kitchen::refillRoutine, this, conf);
}

void plazza::Kitchen::refillRoutine(Configuration conf)
{
    std::cout << "Refill ready !" << std::endl;
    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(conf.getRefillTime()));
        for (int i = 0; i < 9; i++) {
            if (_ingredients[i] < 5) {
                _ingredients[i] += 1;
                std::cout << "Refill ingredient " << std::endl;
            }
        }
    }
}

void plazza::Kitchen::kitchenRoutine(int nbr)
{
    std::unique_lock<std::mutex> lock(_mutex_reception);
    std::cout << "Furnace number: " << nbr << " ready to cook" << std::endl;

    while (1) {
        _cond_furnace.wait(lock);
        lock.unlock();
        std::cout << "I'll cook this pizza for " << "2 seconds" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Pizza cooked" << std::endl;
    }
}

bool plazza::Kitchen::checkIngredients([[maybe_unused]] PizzaCommand &command)
{
    return true;
}

void *plazza::Kitchen::algorithmKitchen([[maybe_unused]] void *arg) {
    _cond_furnace.notify_all();
    return nullptr;
}

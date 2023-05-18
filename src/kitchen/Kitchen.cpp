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

    for (int i = 0; i < conf.getCooksPerKitchen(); i++) {
        _threads.emplace_back(&Kitchen::kitchenRoutine, this, "Kitchen");
    }
    for (auto &thread : _threads) {
        thread.join();
    }
}

void plazza::Kitchen::kitchenRoutine(std::string message)
{
    std::cout << message << std::endl;
}

bool plazza::Kitchen::checkIngredients(PizzaCommand &command)
{
    return true;
}

void *plazza::Kitchen::algorithmKitchen([[maybe_unused]] void *arg) {
    return nullptr;
}

/*
** EPITECH PROJECT, 2023
** theplazza
** File description:
** kitchen
*/

#include <thread>
#include <mutex>
#include "Kitchen.hpp"

Kitchen::Kitchen(plazza::Configuration &conf)
{
    std::unordered_map<Ingredients, int> ReginaIngr = {{Dough, 1}, {Tomato, 1}, {Gruyere, 1}, {Ham, 1}, {Mushrooms, 1}};
    std::unordered_map<Ingredients, int> MargaritaIngr = {{Dough, 1}, {Tomato, 1}, {Gruyere, 1}};
    std::unordered_map<Ingredients, int> AmericanaIngr = {{Dough, 1}, {Tomato, 1}, {Gruyere, 1}, {Steak, 1}};
    std::unordered_map<Ingredients, int> FantasiaIngr = {{Dough, 1}, {Tomato, 1}, {Eggplant, 1}, {GoatCheese, 1}, {ChiefLove, 1}};

    _ingredients = {5, 5, 5, 5, 5, 5, 5, 5, 5};
    _ingredients_per_pizza = {{Regina, {ReginaIngr, 2 * 1000}},
                            {Margarita, {MargaritaIngr, 1 * 1000}},
                            {Americana, {AmericanaIngr, 2 * 1000}},
                            {Fantasia, {FantasiaIngr, 4 * 1000}}};

    for (int i = 0; i < conf.getCooksPerKitchen(); i++)
        _threads.emplace_back(&Kitchen::kitchenRoutine, this, "Kitchen");
    for (auto &thread : _threads)
        thread.join();
}

void Kitchen::kitchenRoutine(std::string message)
{
    std::cout << message << std::endl;
}

bool Kitchen::checkIngredients(const PizzaCommand &command)
{
    for (auto &i : _ingredients_per_pizza[command.type].first) {
        if (i.second > _ingredients[i.first])
            return false;
    }
    return true;
}

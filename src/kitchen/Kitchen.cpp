/*
** EPITECH PROJECT, 2023
** theplazza
** File description:
** kitchen
*/

#include <mutex>
#include "Kitchen.hpp"
#include "ThreadPool.hpp"

plazza::Kitchen::Kitchen(size_t id, Configuration &config, const Communication &ipc) : _id(id), _config(config), _ipc(ipc), _parent_pid(getpid()) {
    std::unordered_map<Ingredients, int> ReginaIngr = {
            {Ingredients::Dough,     1},
            {Ingredients::Tomato,    1},
            {Ingredients::Gruyere,   1},
            {Ingredients::Ham,       1},
            {Ingredients::Mushrooms, 1},
    };
    std::unordered_map<Ingredients, int> MargaritaIngr = {
            {Ingredients::Dough,   1},
            {Ingredients::Tomato,  1},
            {Ingredients::Gruyere, 1},
    };
    std::unordered_map<Ingredients, int> AmericanaIngr = {
            {Ingredients::Dough,   1},
            {Ingredients::Tomato,  1},
            {Ingredients::Gruyere, 1},
            {Ingredients::Steak,   1},
    };
    std::unordered_map<Ingredients, int> FantasiaIngr = {
            {Ingredients::Dough,      1},
            {Ingredients::Tomato,     1},
            {Ingredients::Eggplant,   1},
            {Ingredients::GoatCheese, 1},
            {Ingredients::ChiefLove,  1},
    };

    this->_ingredients = {5, 5, 5, 5, 5, 5, 5, 5, 5};
    this->_ingredients_per_pizza = {
            {PizzaType::Regina,    {ReginaIngr,    2}},
            {PizzaType::Margarita, {MargaritaIngr, 1}},
            {PizzaType::Americana, {AmericanaIngr, 2}},
            {PizzaType::Fantasia,  {FantasiaIngr,  4}},
    };
}

void plazza::Kitchen::openKitchen(const Pizza &firstPizza) {
    pid_t pid = fork();

    if (pid == -1) {
        throw CommunicationException("fork failed");
    } else if (pid == 0) {
        this->run(firstPizza);
        exit(0);
    }
}

void plazza::Kitchen::run(const Pizza &firstPizza) {
    ThreadPool pool(this->_parent_pid, this->_config);

    pool.run(firstPizza);
}

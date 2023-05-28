/*
** EPITECH PROJECT, 2023
** theplazza
** File description:
** main
*/

#include "Configuration.hpp"
#include "Reception.hpp"
#include "PizzaRecipe.hpp"

int main(int argc, char const *argv[]) {
    try {
        plazza::Configuration config(argc, argv, CONFIG_FOLDER);
        plazza::Reception reception(config);
        reception.run();
    } catch (plazza::ConfigurationException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (plazza::LoggerException &e) {
        std::cerr << "Logging is unavailable" << std::endl;
        return 84;
    }
    return 0;
}

bool operator ==(const plazza::Pizza &a, const plazza::Pizza &b) {
    return (a.type == b.type && a.size == b.size);
}

std::string operator*(const plazza::PizzaSize &size) {
    std::string types[5] = { "S", "M", "L", "XL", "XXL" };

    return types[static_cast<int>(size)];
}

std::string operator*(const plazza::Ingredients &ingredient) {
    std::string types[9] = { "Dough", "Tomato", "Gruyere", "Ham", "Mushrooms", "Steak", "Eggplant", "GoatCheese", "ChiefLove" };

    return types[static_cast<int>(ingredient)];
}

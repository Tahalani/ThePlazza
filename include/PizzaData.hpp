/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-taha.alani
** File description:
** PizzaData.hpp
*/

#ifndef PIZZADATA_HPP_
#define PIZZADATA_HPP_

#define CONFIG_FOLDER "config/"
#define PIZZA_SIZE 16

#include <string>

namespace plazza {
    enum class MessageType {
        EXIT,
        STATUS,
        PIZZA,
    };

    enum class PizzaSize {
        S,
        M,
        L,
        XL,
        XXL
    };

    enum class Ingredients {
        Dough,
        Tomato,
        Gruyere,
        Ham,
        Mushrooms,
        Steak,
        Eggplant,
        GoatCheese,
        ChiefLove
    };

    struct Pizza {
        std::string type;
        PizzaSize size;
        bool cooked;
    };

    struct PizzaCommand {
        std::string type;
        PizzaSize size;
        int quantity;
    };
}

bool operator ==(const plazza::Pizza &a, const plazza::Pizza &b);

std::string operator*(const plazza::PizzaSize &size);
std::string operator*(const plazza::Ingredients &ingredient);

#endif

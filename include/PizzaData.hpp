/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-taha.alani
** File description:
** PizzaData.hpp
*/

#ifndef PIZZADATA_HPP_
#define PIZZADATA_HPP_

namespace plazza {
    enum class MessageType {
        EXIT,
        PIZZA,
        PIZZA_RESPONSE,
    };

    enum class PizzaType {
        Regina,
        Margarita,
        Americana,
        Fantasia
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
        PizzaType type;
        PizzaSize size;
    };

    struct PizzaCommand : Pizza {
        int quantity;
    };
}

bool operator ==(const plazza::Pizza &a, const plazza::Pizza &b);

#endif

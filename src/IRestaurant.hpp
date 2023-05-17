/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-taha.alani
** File description:
** Irestaurant
*/

#ifndef IRESTAURANT_HPP_
    #define IRESTAURANT_HPP_

enum PizzaType {
        Regina,
        Margarita,
        Americana,
        Fantasia
    };

enum PizzaSize {
    S,
    M,
    L,
    XL,
    XXL
};

class IRestaurant {
    public:
        IRestaurant() = default;
        ~IRestaurant() = default;

    struct PizzaCommand {
        PizzaType type;
        PizzaSize size;
        int quantity;
    };
};

#endif

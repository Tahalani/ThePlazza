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

class Irestaurant {
    public:
        Irestaurant() = default;
        ~Irestaurant() = default;

    struct PizzaCommand {
        PizzaType type;
        PizzaSize size;
        int quantity;
    };

    protected:
    private:
};

#endif /* !IRESTAURANT_HPP_ */

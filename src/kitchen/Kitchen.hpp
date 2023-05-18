/*
** EPITECH PROJECT, 2023
** theplazza
** File description:
** kitchen
*/

#ifndef KITCHEN_HPP_
    #define KITCHEN_HPP_

    #include <iostream>
    #include <vector>
    #include <map>
    #include <unordered_map>
    #include "../../include/PizzaData.hpp"

    class Kitchen : public IRestaurant {
        public:
            Kitchen() { _ingredients = {Dough, Tomato, Gruyere, Ham, Mushrooms, Steak, Eggplant, GoatCheese, ChiefLove}; };
            ~Kitchen() {};
            bool checkIngredients(int quantity, PizzaType type, PizzaSize size);
            void *algorithmKitchen(void *arg) { return nullptr; };
        protected:
            std::vector<Ingredients> _ingredients;
            std::unordered_map<PizzaType, std::unordered_map<Ingredients, int>> _ingredients_per_pizza;
        private:
    };

#endif /* !KITCHEN_HPP_ */

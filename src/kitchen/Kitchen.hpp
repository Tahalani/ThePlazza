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
    #include <thread>
    #include <unordered_map>
    #include "../IRestaurant.hpp"
    #include "../Configuration.hpp"

enum Ingredients {
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

    class Kitchen : public IRestaurant {
        public:
            Kitchen(plazza::Configuration &conf);
            ~Kitchen() {};
            void kitchenRoutine(std::string message);
            bool checkIngredients(PizzaCommand &command);
            void *algorithmKitchen(void *arg) { return nullptr; };
        protected:
            std::vector<int> _ingredients;
            std::unordered_map<PizzaType, std::pair<std::unordered_map<Ingredients, int>, int>> _ingredients_per_pizza;
            std::vector<std::thread> _threads;
        private:
    };

#endif /* !KITCHEN_HPP_ */

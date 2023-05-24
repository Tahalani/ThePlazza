/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-taha.alani
** File description:
** pizzaRecipe>
*/

#ifndef PIZZARECIPE__HPP_
    #define PIZZARECIPE__HPP_

    #include <unordered_map>
    #include <string>
    #include <iostream>
    #include <fstream>
    #include "../include/PizzaData.hpp"

    namespace plazza {

        static std::unordered_map<std::string, Ingredients> ingredients_array = {
            {"Doe", Ingredients::Dough},
            {"Tomato", Ingredients::Tomato},
            {"Gruyere", Ingredients::Gruyere},
            {"Ham", Ingredients::Ham},
            {"Mushrooms", Ingredients::Mushrooms},
            {"Steak", Ingredients::Steak},
            {"Eggplant", Ingredients::Eggplant},
            {"GoatCheese", Ingredients::GoatCheese},
            {"ChiefLove", Ingredients::ChiefLove}
        };

        class RecipeException : std::exception {
            public:
                explicit RecipeException(std::string message);
                ~RecipeException() override = default;

                [[nodiscard]] const char *what() const noexcept override;

            private:
                std::string _message;
    };

        class PizzaRecipe {
            public:
                PizzaRecipe(std::string filepath);
                ~PizzaRecipe();
                std::string getName() const { return _name;};
                int getTime() const { return _time;};
                std::unordered_map<Ingredients, int> getIngredients() const { return _ingredients;};

            private:
                std::string _name;
                size_t _time;
                std::unordered_map<Ingredients, int> _ingredients;
        };
    }



#endif /* !PIZZARECIPE__HPP_ */

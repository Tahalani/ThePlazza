/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-taha.alani
** File description:
** pizzaRecipe>
*/

#ifndef PIZZA_RECIPE_HPP_
#define PIZZA_RECIPE_HPP_

#define MAX_INGREDIENTS 5

#include <string>
#include <unordered_map>
#include <vector>
#include "PizzaData.hpp"

namespace plazza {
    static std::unordered_map<std::string, Ingredients> name_to_ingredient = {
        {"Dough", Ingredients::Dough},
        {"Tomato", Ingredients::Tomato},
        {"Gruyere", Ingredients::Gruyere},
        {"Ham", Ingredients::Ham},
        {"Mushrooms", Ingredients::Mushrooms},
        {"Steak", Ingredients::Steak},
        {"Eggplant", Ingredients::Eggplant},
        {"GoatCheese", Ingredients::GoatCheese},
        {"ChiefLove", Ingredients::ChiefLove}
    };

    static std::unordered_map<Ingredients, std::string> ingredient_to_name = {
            {Ingredients::Dough, "Dough" },
            {Ingredients::Tomato, "Tomato" },
            {Ingredients::Gruyere, "Gruyere" },
            {Ingredients::Ham, "Ham" },
            {Ingredients::Mushrooms, "Mushrooms" },
            {Ingredients::Steak, "Steak" },
            {Ingredients::Eggplant, "Eggplant" },
            {Ingredients::GoatCheese, "GoatCheese" },
            {Ingredients::ChiefLove, "ChiefLove" }
    };

    class RecipeException : std::exception {
        public:
            explicit RecipeException(std::string message);

            [[nodiscard]] const char *what() const noexcept override;

        private:
            std::string _message;
    };

    class PizzaRecipe {
        public:
            PizzaRecipe();
            explicit PizzaRecipe(const std::string& filepath);

            std::string getName() const;
            size_t getTime() const;
            const std::unordered_map<Ingredients, int> &getIngredients() const;

        private:
            std::string _name;
            size_t _time;
            std::unordered_map<Ingredients, int> _ingredients;
    };
}

#endif

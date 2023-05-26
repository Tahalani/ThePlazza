/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-taha.alani
** File description:
** Pizza_Recipe
*/

#include "PizzaRecipe.hpp"
#include <sstream>
#include <utility>
#include <string>

plazza::RecipeException::RecipeException(std::string message): _message(std::move(message))
{

}

const char *plazza::RecipeException::what() const noexcept
{
    return _message.c_str();
}

plazza::PizzaRecipe::PizzaRecipe(std::string filepath, std::vector<PizzaRecipe> const &_pizzaRecipes)
{
    std::string token;
    std::ifstream file;
    Ingredients tmp;

    file.open(filepath);
    if (!file.is_open())
        throw RecipeException("Cannot open file");

    file >> _name;
    file >> _time;

    if (_name.empty())
        throw RecipeException("Invalid name");
    if (_time <= 0)
        throw RecipeException("Invalid time");
    for (auto &pizza: _pizzaRecipes) {
        if (pizza.getName() == _name)
            throw RecipeException("Pizza already exists");
    }

    for (size_t i = 0; std::getline(file, token, ':'); i++) {
        if (i == 0)
            token.erase(token.begin());
        if (i % 2 == 0) {
            if (ingredients_array.find(token) == ingredients_array.end())
                throw RecipeException("Unknown ingredient");
            tmp = ingredients_array[token];
        } else {
            if (token[0] < '0' || token[0] > '9')
                throw RecipeException("Invalid quantity");
            _ingredients.insert(std::pair<Ingredients, int>(tmp, std::stoi(token)));
        }
    }
    file.close();
}

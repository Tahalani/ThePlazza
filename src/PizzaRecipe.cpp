/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-taha.alani
** File description:
** Pizza_Recipe
*/

#include "PizzaRecipe.hpp"
#include <sstream>

plazza::RecipeException::RecipeException(std::string message): _message(std::move(message))
{

}

const char *plazza::RecipeException::what() const noexcept
{
    return _message.c_str();
}

plazza::PizzaRecipe::PizzaRecipe(std::string filepath)
{
    std::string token;
    std::ifstream file;
    Ingredients tmp;

    file.open(filepath);
    if (!file.is_open())
        throw RecipeException("Cannot open file");
    file >> _name;
    file >> _time;

    for (size_t i = 0; std::getline(file, token, ':'); i++) {
        if ((i % 2) == 0) {
            tmp = ingredients_array[token];
            std::cout << token << std::endl;
        } else {
            _ingredients.insert(std::pair<Ingredients, int>(tmp, std::stoi(token)));
            std::cout << token << std::endl;
        }
    }
    file.close();
}

plazza::PizzaRecipe::~PizzaRecipe()
{
}

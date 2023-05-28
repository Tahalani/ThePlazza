/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-taha.alani
** File description:
** Pizza_Recipe
*/

#include <fstream>
#include "PizzaRecipe.hpp"
#include <iostream>
#include <regex>
#include <unordered_map>


plazza::RecipeException::RecipeException(std::string message): _message(std::move(message))
{

}

const char *plazza::RecipeException::what() const noexcept
{
    return _message.c_str();
}

plazza::PizzaRecipe::PizzaRecipe(const std::string &filepath, std::vector<PizzaRecipe> const &_pizzaRecipes): _time(0)
{
    std::string token;
    std::ifstream file;
    Ingredients tmp;
    std::regex command_regex(R"(^ *(Dough|Tomato|Gruyere|Ham|Mushrooms|Steak|Eggplant|GoatCheese|ChiefLove):([1-5]+[0-5]*) *$)");
    std::smatch command_match;

    file.open(filepath);
    if (!file.is_open()) {
        throw RecipeException("Cannot open file");
    }
    if (!std::getline(file, token)) {
        throw RecipeException("Invalid file");
    }
    this->_name = token;
    if (this->_name.empty() || this->_name.size() > PIZZA_SIZE) {
        throw RecipeException("Invalid name");
    }
    if (!std::getline(file, token)) {
        throw RecipeException("Invalid file");
    }
    this->_time = std::stoi(token);
    if (this->_time <= 0) {
        throw RecipeException("Invalid time");
    }
    for (auto &pizza: _pizzaRecipes) {
        if (pizza.getName() == this->_name) {
            throw RecipeException("Pizza already exists");
        }
    }
    for (size_t i = 0; std::getline(file, token); i++) {
        if (!std::regex_match(token, command_match, command_regex) || command_match.size() != 3) {
            throw RecipeException("Invalid ingredient");
        }
        this->_ingredients.insert(std::pair<Ingredients, int>(ingredients_array[command_match[1]], std::stoi(command_match[2])));
    }
    file.close();
}

/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-taha.alani
** File description:
** Pizza_Recipe
*/

#include <fstream>
#include "PizzaRecipe.hpp"
#include <regex>
#include <unordered_map>


plazza::RecipeException::RecipeException(std::string message): _message(std::move(message)) {

}

const char *plazza::RecipeException::what() const noexcept
{
    return _message.c_str();
}

plazza::PizzaRecipe::PizzaRecipe() {

}

plazza::PizzaRecipe::PizzaRecipe(const std::string &filepath)
{
    std::string token;
    std::ifstream file;
    std::regex command_regex(R"(^ *(Dough|Tomato|Gruyere|Ham|Mushrooms|Steak|Eggplant|GoatCheese|ChiefLove):([1-9]+[0-9]*) *$)");
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
    while (std::getline(file, token)) {
        if (!std::regex_match(token, command_match, command_regex) || command_match.size() != 3) {
            throw RecipeException("Invalid ingredient");
        }
        int num = std::stoi(command_match[2]);
        if (num > MAX_INGREDIENTS) {
            throw RecipeException("Ingredients quantity above max");
        }
        this->_ingredients.insert(std::pair<Ingredients, int>(name_to_ingredient[command_match[1]], std::stoi(command_match[2])));
    }
    if (this->_ingredients.empty()) {
        throw RecipeException("No ingredients");
    }
    file.close();
}

std::string plazza::PizzaRecipe::getName() const {
    return this->_name;
}

size_t plazza::PizzaRecipe::getTime() const {
    return this->_time;
}

const std::unordered_map<plazza::Ingredients, int> &plazza::PizzaRecipe::getIngredients() const {
    return this->_ingredients;
}

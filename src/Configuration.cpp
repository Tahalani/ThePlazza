/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** Configuration.cpp
*/

#include "Configuration.hpp"
#include "PizzaRecipe.hpp"

#include <filesystem>
#include <utility>

plazza::ConfigurationException::ConfigurationException(std::string message): _message(std::move(message)) {

}

const char *plazza::ConfigurationException::what() const noexcept {
    return this->_message.c_str();
}


plazza::Configuration::Configuration(int argc, const char **argv, const std::string &configFolder) {
    if ((argc == 2 && argv[1] == std::string("-h")) || argc != 4) {
        throw plazza::ConfigurationException("USAGE: " + std::string(argv[0]) + " [multiplier] [cooks] [refill]");
    }

    this->_timeMultiplier = parse<float>(argv[1]);
    this->_cooksPerKitchen = parse<int>(argv[2]);
    this->_refillTime = parse<int>(argv[3]);

    if (this->_timeMultiplier <= 0.0) {
        throw plazza::ConfigurationException("Time multiplier must be greater than 0");
    }
    if (this->_cooksPerKitchen <= 0) {
        throw plazza::ConfigurationException("Cooks per kitchen must be greater than 0");
    }
    if (this->_refillTime < 0) {
        throw plazza::ConfigurationException("Refill time must be positive");
    }

    for (auto &entry : std::filesystem::directory_iterator(configFolder)) {
        try {
            PizzaRecipe recipe = PizzaRecipe(entry.path().string());

            if (this->_pizzaRecipes.find(recipe.getName()) != this->_pizzaRecipes.end()) {
                throw ConfigurationException("Multiple pizzas share the same name");
            }
            this->_pizzaRecipes[recipe.getName()] = recipe;
        } catch (RecipeException &e) {
            throw ConfigurationException(e.what());
        }
    }
}

float plazza::Configuration::getTimeMultiplier() const {
    return this->_timeMultiplier;
}

int plazza::Configuration::getCooksPerKitchen() const {
    return this->_cooksPerKitchen;
}

int plazza::Configuration::getRefillTime() const {
    return this->_refillTime;
}

plazza::PizzaRecipe &plazza::Configuration::getRecipe(const std::string &name) {
    if (this->_pizzaRecipes.find(name) == this->_pizzaRecipes.end()) {
        throw ConfigurationException("Unknown pizza: " + name);
    }
    return this->_pizzaRecipes[name];
}

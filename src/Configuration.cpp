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


plazza::Configuration::Configuration(int argc, const char **argv) {
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

void plazza::Configuration::setPizzaRecipes(const std::string &path)
{
    for (auto &entry : std::filesystem::directory_iterator(path)) {
        std::string pathConf = entry.path().string();
        _pizzaRecipes.emplace_back(PizzaRecipe(pathConf));
    }
}

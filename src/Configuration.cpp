/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** Configuration.cpp
*/

#include "Configuration.hpp"

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

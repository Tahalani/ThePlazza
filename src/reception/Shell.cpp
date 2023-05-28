/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** Shell.cpp
*/

#include <iostream>
#include <regex>
#include <utility>
#include "Shell.hpp"

plazza::CommandException::CommandException(std::string message): _message(std::move(message)) {

}

const char *plazza::CommandException::what() const noexcept {
    return this->_message.c_str();
}

plazza::Shell::Shell(Configuration config, std::shared_ptr<Logger> logger): _config(std::move(config)), _logger(std::move(logger)) {
    this->_pizzaSizes["S"] = plazza::PizzaSize::S;
    this->_pizzaSizes["M"] = plazza::PizzaSize::M;
    this->_pizzaSizes["L"] = plazza::PizzaSize::L;
    this->_pizzaSizes["XL"] = plazza::PizzaSize::XL;
    this->_pizzaSizes["XXL"] = plazza::PizzaSize::XXL;
}

std::optional<std::vector<plazza::PizzaCommand>> plazza::Shell::getNextOrder() {
    size_t pos = 0;
    std::string buffer;
    std::string str;
    std::vector<plazza::PizzaCommand> vec = {};

    auto &res = std::getline(std::cin, buffer);

    if (!res) {
        *this->_logger >> "Received EOF, exiting";
        throw plazza::InputException();
    }
    *this->_logger >> ("Received command: '" + buffer.substr(0, buffer.find('\n')) + "'");
    if (buffer == "status") {
        return std::nullopt;
    }
    do {
        pos = buffer.find(';');
        str = buffer.substr(0, pos);
        vec.push_back(this->parseOrder(str));
        buffer.erase(0, pos + 1);
    } while (pos != std::string::npos);
    return vec;
}

plazza::PizzaCommand plazza::Shell::parseOrder(std::string &order) {
    std::regex command_regex(R"(^ *(\w+) (S|M|L|XL|XXL) x([1-9][0-9]*) *$)");
    std::smatch command_match;

    if (!std::regex_match(order, command_match, command_regex) || command_match.size() != 4) {
        throw plazza::CommandException(order + ": Invalid command");
    }
    int quantity = std::stoi(command_match[3]);
    if (quantity <= 0) {
        throw plazza::CommandException(order + ": Invalid quantity");
    }
    try {
        PizzaRecipe recipe = this->_config.getRecipe(command_match[1]);

        return PizzaCommand {
                command_match[1],
                this->_pizzaSizes[command_match[2]],
                quantity,
        };
    } catch (ConfigurationException &e) {
        throw plazza::CommandException(order + ": Invalid pizza type");
    }
}

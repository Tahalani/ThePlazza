/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** Shell.hpp
*/

#ifndef SHELL_HPP_
#define SHELL_HPP_

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>
#include "PizzaData.hpp"

namespace plazza {
    class InputException : std::exception {

    };

    class CommandException : std::exception {
        public:
            explicit CommandException(std::string message);

            [[nodiscard]] const char *what() const noexcept override;

        private:
            std::string _message;
    };

    class Shell {
        public:
            Shell();

            std::optional<std::vector<PizzaCommand>> getNextOrder();

        private:
            PizzaCommand parseOrder(std::string &order);

            std::unordered_map<std::string, PizzaType> _pizzaTypes;
            std::unordered_map<std::string, PizzaSize> _pizzaSizes;
    };
}

#endif

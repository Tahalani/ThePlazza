/*
** EPITECH PROJECT, 2023
** ThePlazza
** File description:
** Shell.hpp
*/

#ifndef SHELL_HPP_
#define SHELL_HPP_

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
            ~CommandException() override = default;

            [[nodiscard]] const char *what() const noexcept override;

        private:
            std::string _message;
    };

    class Shell {
        public:
            Shell();
            ~Shell() = default;

            std::vector<PizzaCommand> getNextOrder();

        private:
            PizzaCommand parseOrder(std::string &order);
            void sendPrompt();

            std::unordered_map<std::string, PizzaType> _pizzaTypes;
            std::unordered_map<std::string, PizzaSize> _pizzaSizes;
    };
}

#endif

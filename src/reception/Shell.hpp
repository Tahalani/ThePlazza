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
#include "Configuration.hpp"
#include "Logger.hpp"
#include "PizzaData.hpp"
#include "PizzaRecipe.hpp"

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
            Shell(Configuration config, std::shared_ptr<Logger> logger);

            std::optional<std::vector<PizzaCommand>> getNextOrder();

        private:
            PizzaCommand parseOrder(std::string &order);

            Configuration _config;
            std::unordered_map<std::string, PizzaSize> _pizzaSizes;
            std::shared_ptr<Logger> _logger;
    };
}

#endif
